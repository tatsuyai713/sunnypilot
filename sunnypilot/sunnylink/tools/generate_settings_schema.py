#!/usr/bin/env python3
"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.

Settings Schema Generator
=========================

Generates a SettingsSchema JSON structure at runtime by reading
settings_ui.json (the declarative definition file) and merging
titles, descriptions, and options from params_metadata.json.

The schema is consumed by the sunnylink frontend to render a fully
data-driven settings UI.

This module is imported by sunnylinkd at startup. The definition
file (settings_ui.json) is committed to git and edited by developers.
"""
from __future__ import annotations

import base64
import copy
import gzip
import json
import os
from collections.abc import Callable
from datetime import datetime, UTC

from openpilot.common.params import Params
from openpilot.common.swaglog import cloudlog
from openpilot.sunnypilot.sunnylink.capabilities import CAPABILITY_FIELDS, generate_capabilities_json

SCHEMA_VERSION = "1.0"
_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
METADATA_PATH = os.path.join(_DIR, "params_metadata.json")
DEFINITION_PATH = os.path.join(_DIR, "settings_ui.json")


# ---------------------------------------------------------------------------
# Definition loading
# ---------------------------------------------------------------------------

def _load_definition() -> dict:
  """Load settings_ui.json — the declarative UI definition file."""
  with open(DEFINITION_PATH) as f:
    return json.load(f)


# ---------------------------------------------------------------------------
# Backward compatibility: generate flat items/sub_panels from sections
# ---------------------------------------------------------------------------

def _flatten_sections(panel: dict) -> None:
  """For panels with sections, generate backward-compat flat items and sub_panels.

  Old frontends expect panel.items (flat list) and panel.sub_panels.
  New frontends use panel.sections. This function populates both from
  the authoritative sections definition.
  """
  sections = panel.get("sections")
  if not sections:
    return

  flat_items: list[dict] = []
  flat_sub_panels: list[dict] = []

  for section in sections:
    for item in section.get("items", []):
      flat_items.append(copy.deepcopy(item))
    for sp in section.get("sub_panels", []):
      flat_sub_panels.append(copy.deepcopy(sp))

  panel["items"] = flat_items
  if flat_sub_panels:
    panel["sub_panels"] = flat_sub_panels


# ---------------------------------------------------------------------------
# Metadata loading from params_metadata.json
#
# Titles, descriptions, options, and numeric constraints live in
# params_metadata.json — a JSON file alongside this module.
# The generator reads it at runtime and merges into schema items.
# ---------------------------------------------------------------------------

def _load_metadata() -> dict:
  """Load params_metadata.json for title/description/options enrichment."""
  if not os.path.exists(METADATA_PATH):
    return {}
  try:
    with open(METADATA_PATH) as f:
      return json.load(f)
  except (json.JSONDecodeError, OSError):
    return {}


def _enrich_item(item_dict: dict, metadata: dict) -> None:
  """Merge metadata into a schema item dict (mutates in place)."""
  key = item_dict.get("key", "")
  meta = metadata.get(key, {})

  # Only fill in fields not already set by the definition
  if "title" not in item_dict and "title" in meta:
    item_dict["title"] = meta["title"]
  if "description" not in item_dict and "description" in meta and meta["description"]:
    item_dict["description"] = meta["description"]
  if "options" not in item_dict and "options" in meta:
    item_dict["options"] = meta["options"]
  if "min" not in item_dict and "min" in meta:
    item_dict["min"] = meta["min"]
  if "max" not in item_dict and "max" in meta:
    item_dict["max"] = meta["max"]
  if "step" not in item_dict and "step" in meta:
    item_dict["step"] = meta["step"]
  if "unit" not in item_dict and "unit" in meta:
    item_dict["unit"] = meta["unit"]

  # Recurse into sub_items
  for sub in item_dict.get("sub_items", []):
    _enrich_item(sub, metadata)


def _enrich_schema(schema: dict, metadata: dict) -> None:
  """Enrich all items in the schema with metadata."""
  for panel in schema.get("panels", []):
    # Enrich section items (V2 path)
    for section in panel.get("sections", []):
      for item in section.get("items", []):
        _enrich_item(item, metadata)
      for sp in section.get("sub_panels", []):
        for item in sp.get("items", []):
          _enrich_item(item, metadata)

    # Enrich flat items (V1 backward-compat path)
    for item in panel.get("items", []):
      _enrich_item(item, metadata)
    for sub_panel in panel.get("sub_panels", []):
      for item in sub_panel.get("items", []):
        _enrich_item(item, metadata)

  for brand_data in schema.get("vehicle_settings", {}).values():
    items = brand_data.get("items", []) if isinstance(brand_data, dict) else brand_data
    for item in items:
      _enrich_item(item, metadata)


# ---------------------------------------------------------------------------
# Public API
# ---------------------------------------------------------------------------

def generate_schema() -> dict:
  """Generate the complete SettingsSchema dict.

  Reads settings_ui.json, generates backward-compat flat items from
  sections, merges metadata, and returns the complete schema.
  """
  definition = _load_definition()

  # Deep copy panels so we don't mutate the loaded definition
  panels = copy.deepcopy(definition.get("panels", []))

  # Generate backward-compat flat items/sub_panels from sections
  for panel in panels:
    _flatten_sections(panel)

  schema = {
    "schema_version": definition.get("schema_version", SCHEMA_VERSION),
    "generated_at": datetime.now(UTC).isoformat(),
    "panels": panels,
    "vehicle_settings": copy.deepcopy(definition.get("vehicle_settings", {})),
    "capability_fields": list(CAPABILITY_FIELDS),
  }

  metadata = _load_metadata()
  _enrich_schema(schema, metadata)

  return schema


def generate_schema_json() -> str:
  """Generate SettingsSchema as a compact JSON string."""
  return json.dumps(generate_schema(), separators=(",", ":"))


def generate_schema_compressed() -> str:
  """Generate SettingsSchema as gzip-compressed, base64-encoded string.

  Compression pipeline (mirrors getParamsMetadata):
    1. JSON serialize (compact, no whitespace)
    2. UTF-8 encode
    3. gzip compress
    4. base64 encode
  """
  raw = json.dumps(generate_schema(), separators=(",", ":")).encode("utf-8")
  return base64.b64encode(gzip.compress(raw)).decode("utf-8")


def update_settings_schema() -> None:
  """Generate and write SettingsSchema + SettingsCapabilities to params.

  Called once at sunnylinkd startup. SettingsSchema is static per git commit.
  SettingsCapabilities is derived from CarParams and may change when a
  different car is detected.
  """
  params = Params()
  try:
    params.put("SettingsSchema", generate_schema_compressed())
    cloudlog.info("update_settings_schema: SettingsSchema written")
  except Exception:
    cloudlog.exception("update_settings_schema: schema failed")

  try:
    params.put("SettingsCapabilities", generate_capabilities_json())
    cloudlog.info("update_settings_schema: SettingsCapabilities written")
  except Exception:
    cloudlog.exception("update_settings_schema: capabilities failed")


# ---------------------------------------------------------------------------
# Schema introspection utilities
# ---------------------------------------------------------------------------

def _walk_rules(rules: list[dict] | None, visitor: Callable[[dict], None]) -> None:
  """Recursively walk all rules, calling visitor on each leaf rule."""
  if not rules:
    return
  for rule in rules:
    visitor(rule)
    if rule.get("type") == "not" and "condition" in rule:
      _walk_rules([rule["condition"]], visitor)
    elif rule.get("type") in ("any", "all") and "conditions" in rule:
      _walk_rules(rule["conditions"], visitor)


def _walk_all_items(schema: dict, visitor: Callable[[dict], None]) -> None:
  """Walk every item in the schema (panels, sections, sub_panels, sub_items, vehicle_settings)."""
  def _visit_item(item: dict) -> None:
    visitor(item)
    for sub in item.get("sub_items", []):
      _visit_item(sub)

  for panel in schema.get("panels", []):
    # Walk section items (V2)
    for section in panel.get("sections", []):
      for item in section.get("items", []):
        _visit_item(item)
      for sp in section.get("sub_panels", []):
        for item in sp.get("items", []):
          _visit_item(item)

    # Walk flat items (V1)
    for item in panel.get("items", []):
      _visit_item(item)
    for sp in panel.get("sub_panels", []):
      for item in sp.get("items", []):
        _visit_item(item)

  for brand_data in schema.get("vehicle_settings", {}).values():
    items = brand_data.get("items", []) if isinstance(brand_data, dict) else brand_data
    for item in items:
      _visit_item(item)


def collect_all_keys(schema: dict) -> set[str]:
  """Collect all param keys referenced in the schema (items + rules)."""
  keys: set[str] = set()

  def _visit_rule(rule: dict) -> None:
    if rule.get("type") in ("param", "param_compare") and "key" in rule:
      keys.add(rule["key"])

  def _visit_item(item: dict) -> None:
    if "key" in item:
      keys.add(item["key"])
    _walk_rules(item.get("visibility"), _visit_rule)
    _walk_rules(item.get("enablement"), _visit_rule)

  _walk_all_items(schema, _visit_item)
  return keys


def collect_capability_refs(schema: dict) -> set[str]:
  """Collect all capability field names referenced in rules."""
  refs: set[str] = set()

  def _visit_rule(rule: dict) -> None:
    if rule.get("type") == "capability" and "field" in rule:
      refs.add(rule["field"])

  def _visit_item(item: dict) -> None:
    _walk_rules(item.get("visibility"), _visit_rule)
    _walk_rules(item.get("enablement"), _visit_rule)

  _walk_all_items(schema, _visit_item)
  return refs


if __name__ == "__main__":
  # CLI: print schema for inspection
  schema = generate_schema()
  print(json.dumps(schema, indent=2))
  print(f"\nTotal panels: {len(schema['panels'])}")
  print(f"Total capability fields: {len(schema['capability_fields'])}")
  print(f"Total vehicle brands: {len(schema['vehicle_settings'])}")
  keys = collect_all_keys(schema)
  print(f"Total unique param keys: {len(keys)}")

  # Show compression stats
  raw_json = json.dumps(schema, separators=(",", ":")).encode("utf-8")
  compressed = gzip.compress(raw_json)
  print(f"\nRaw JSON size: {len(raw_json):,} bytes")
  print(f"Compressed size: {len(compressed):,} bytes")
  print(f"Compression ratio: {len(compressed)/len(raw_json):.1%}")
