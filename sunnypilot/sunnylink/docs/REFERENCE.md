# sunnylink Settings UI Definition Guide

> How to add, change, or update params/settings that appear on the sunnylink frontend — without modifying any frontend code.

## Overview

The sunnylink frontend renders its settings UI entirely from a **device-generated schema**. Two files in the sunnypilot repo control what the frontend displays:

| File | What you control | Examples |
|------|-----------------|---------|
| `sunnypilot/sunnylink/settings_ui.json` | Structure, layout, widget types, visibility/enablement rules | Where a toggle appears, when it's shown/hidden, when it's greyed out |
| `sunnypilot/sunnylink/params_metadata.json` | Display text and value constraints | Titles, descriptions, option labels, min/max/step/unit |

**The frontend renders whatever the device sends.** No frontend PR needed.

---

## Quick Start

### Adding a new toggle (minimum viable change)

**1. Register the param** in `common/params_keys.h`:
```cpp
{"MyNewToggle", {PERSISTENT | BACKUP, BOOL}},
```

**2. Add display metadata** in `sunnypilot/sunnylink/params_metadata.json`:
```json
"MyNewToggle": {
  "title": "My New Feature",
  "description": "Enable the new feature for enhanced driving."
}
```

**3. Place it in the UI** in `sunnypilot/sunnylink/settings_ui.json`:

Find the panel and section where it belongs, then add to the `items` array:
```json
{
  "key": "MyNewToggle",
  "widget": "toggle",
  "enablement": [{"type": "offroad_only"}]
}
```

**4. Validate:**
```bash
python sunnypilot/sunnylink/tools/validate_settings_ui.py
```

**5. Commit.** The frontend will render it on the next device boot.

---

## File Structure

```
sunnypilot/sunnylink/
  settings_ui.json            <-- UI structure (you edit this)
  settings_ui.schema.json     <-- JSON Schema for IDE autocomplete
  params_metadata.json        <-- Display text and options (you edit this)
  capabilities.py             <-- Car capability fields (reference)
  tools/
    validate_settings_ui.py   <-- Run this after every edit
    generate_settings_schema.py  <-- Merges definition + metadata at boot
    extract_settings_ui.py    <-- One-time extraction tool (historical)
```

---

## How It Works

```
settings_ui.json     +     params_metadata.json
  (structure/rules)           (titles/options/ranges)
        |                            |
        +---------- MERGE ----------+
                      |
                      v
              gzip + base64 encode
                      |
                      v
              SettingsSchema param (stored on device)
                      |
                      v (fetched via getParams RPC)
              sunnylink frontend
              (decodes, decompresses, renders)
```

At device boot, the generator:
1. Reads `settings_ui.json` for structure and rules
2. Reads `params_metadata.json` for titles, descriptions, options
3. Merges them together
4. Compresses (gzip) and base64-encodes
5. Writes to the `SettingsSchema` param

The frontend fetches this param, decompresses it, and renders the UI.

---

## settings_ui.json Structure

### Hierarchy

```
Root
  panels[]                    <-- Top-level navigation categories
    sections[]                <-- Grouped cards within a panel (V2)
      items[]                 <-- Individual settings
        sub_items[]           <-- Nested settings revealed by parent
      sub_panels[]            <-- Drill-down pages (chevron rows)
    items[]                   <-- Flat items (panels without sections)
  vehicle_settings{}          <-- Brand-specific settings (by brand key)
```

### Panel (top-level category)

```json
{
  "id": "steering",
  "label": "Steering",
  "icon": "steering_wheel",
  "order": 1,
  "description": "Lateral control, lane changes, and steering behavior",
  "remote_configurable": true,
  "sections": [...]
}
```

| Field | Required | Description |
|-------|----------|-------------|
| `id` | Yes | Unique identifier, matches the URL path (`/dashboard/settings/{id}`) |
| `label` | Yes | Display name in the sidebar navigation |
| `icon` | Yes | Icon identifier |
| `order` | Yes | Sort order in navigation (must be unique across panels) |
| `description` | No | Subtitle shown below the panel heading |
| `remote_configurable` | No | Whether the frontend can push changes (default: `true`) |
| `sections` | No | Array of grouped sections (use this OR `items`, not both) |
| `items` | No | Array of flat items (for simple panels without grouping) |

### Section (grouped card within a panel)

```json
{
  "id": "mads",
  "title": "MADS",
  "description": "Modified Assistive Driving Safety",
  "order": 1,
  "items": [...],
  "sub_panels": [...]
}
```

| Field | Required | Description |
|-------|----------|-------------|
| `id` | Yes | Unique within the panel |
| `title` | Yes | Section header displayed above the card |
| `description` | No | Subtitle below the section header |
| `order` | No | Sort order within the panel (falls back to array position) |
| `items` | No | Settings within this section |
| `sub_panels` | No | Drill-down pages triggered by items in this section |

### Item (individual setting)

```json
{
  "key": "Mads",
  "widget": "toggle",
  "visibility": [...],
  "enablement": [{"type": "offroad_only"}]
}
```

| Field | Required | Description |
|-------|----------|-------------|
| `key` | Yes | Param key name (must exist in `params_keys.h`) |
| `widget` | Yes | One of: `toggle`, `option`, `multiple_button`, `button`, `info` |
| `visibility` | No | Rules that control show/hide (all must pass) |
| `enablement` | No | Rules that control enabled/disabled (all must pass) |
| `sub_items` | No | Child items that appear indented below this item |
| `title` | No | Override title (normally comes from metadata) |
| `description` | No | Override description (normally comes from metadata) |

### Sub-Panel (drill-down page)

```json
{
  "id": "mads_settings",
  "label": "MADS Settings",
  "trigger_key": "Mads",
  "trigger_condition": {
    "type": "param",
    "key": "Mads",
    "equals": true
  },
  "items": [...]
}
```

| Field | Required | Description |
|-------|----------|-------------|
| `id` | Yes | Unique identifier |
| `label` | Yes | Text shown on the chevron row |
| `trigger_key` | Yes | Param key that this sub-panel relates to (must exist in same panel) |
| `trigger_condition` | No | Rule that controls when the sub-panel row is visible |
| `items` | No | Settings shown when the sub-panel is opened |

---

## Widget Types

| Widget | Renders as | Use when |
|--------|-----------|----------|
| `toggle` | On/off switch | Boolean param (`BOOL` type) |
| `multiple_button` | Segmented button group | Param with 2-4 discrete options |
| `option` | Dropdown or slider | Param with many options, or numeric range with `min`/`max` |
| `info` | Read-only text display | Display-only values (e.g., language) |
| `button` | Action button | Triggering an action (rarely used) |

**How the frontend decides dropdown vs slider for `option` widget:**
- If metadata has `min`/`max`/`step` -> renders as a **slider**
- If metadata has `options` array -> renders as a **dropdown**

**How the frontend handles `multiple_button` overflow:**
- Fits on screen -> **segmented buttons** (pill-shaped)
- Too many options -> **compact mode** (smaller text)
- Still overflows -> **dropdown fallback**

---

## params_metadata.json Patterns

Metadata provides display text and value constraints. The generator merges these into items automatically -- you do NOT need to duplicate them in `settings_ui.json`.

### Simple toggle (title only)

```json
"Mads": {
  "title": "MADS Enabled",
  "description": ""
}
```

### Toggle with description

```json
"GreenLightAlert": {
  "title": "Green Traffic Light Alert (Beta)",
  "description": "A chime will play when the traffic light turns green and you have no vehicle in front of you."
}
```

### Option selector (discrete values)

```json
"AutoLaneChangeTimer": {
  "title": "Auto Lane Change Timer",
  "description": "",
  "options": [
    {"value": -1, "label": "Off"},
    {"value": 0, "label": "Nudge"},
    {"value": 1, "label": "Nudgeless"},
    {"value": 2, "label": "0.5s"},
    {"value": 3, "label": "1s"},
    {"value": 4, "label": "1.5s"},
    {"value": 5, "label": "2s"}
  ]
}
```

### Numeric range (slider)

```json
"CameraOffset": {
  "title": "Adjust Camera Offset",
  "description": "Virtually shift camera's perspective.",
  "min": -0.35,
  "max": 0.35,
  "step": 0.01,
  "unit": "meters"
}
```

### Numeric range (integer)

```json
"CustomAccLongPressIncrement": {
  "title": "Custom ACC Long Press Increment",
  "description": "",
  "min": 1,
  "max": 10,
  "step": 1
}
```

### Description with line breaks

Use `<br>` tags for line breaks (only `<br>` is allowed, all other HTML is stripped):

```json
"SomeParam": {
  "title": "Feature Name",
  "description": "First line of explanation.<br>Second line with more detail."
}
```

---

## Rules Reference

Rules control **visibility** (show/hide) and **enablement** (enabled/greyed out).

- `visibility` rules: if ANY rule fails, the item is **completely hidden**
- `enablement` rules: if ANY rule fails, the item is **visible but greyed out**
- All rules in an array use **AND** logic (all must pass)
- Empty array or no rules = always visible/enabled

### offroad_only

Only passes when the device is not actively driving.

```json
{"type": "offroad_only"}
```

Use in `enablement` (not `visibility`) so users can see the setting exists but know they need to stop to change it. The frontend shows an "Offroad" badge.

### capability

Checks a vehicle capability derived from CarParams at runtime.

```json
{"type": "capability", "field": "has_longitudinal_control", "equals": true}
```

```json
{"type": "capability", "field": "brand", "equals": "toyota"}
```

```json
{"type": "capability", "field": "steer_control_type", "equals": "angle"}
```

**Available capability fields:**

| Field | Type | Description |
|-------|------|-------------|
| `has_longitudinal_control` | bool | Car supports openpilot longitudinal |
| `has_icbm` | bool | Intelligent Cruise Button Management active |
| `icbm_available` | bool | ICBM is available for this car |
| `torque_allowed` | bool | Torque lateral control supported |
| `brand` | string | Vehicle brand (e.g., "toyota", "hyundai") |
| `pcm_cruise` | bool | PCM cruise control |
| `alpha_long_available` | bool | Alpha longitudinal available |
| `steer_control_type` | string | Steering control type (e.g., "angle", "torque") |
| `enable_bsm` | bool | Blind spot monitoring available |
| `is_release` | bool | Running release branch |
| `is_sp_release` | bool | Running sunnypilot release branch |
| `is_development` | bool | Running development branch |
| `tesla_has_vehicle_bus` | bool | Tesla with vehicle bus access |
| `has_stop_and_go` | bool | Stop and go capability |
| `stock_longitudinal` | bool | Using stock longitudinal control |

### param

Checks the current value of another param.

```json
{"type": "param", "key": "Mads", "equals": true}
```

```json
{"type": "param", "key": "SpeedLimitMode", "equals": 0}
```

### param_compare

Numeric comparison against another param's value.

```json
{"type": "param_compare", "key": "AutoLaneChangeTimer", "op": ">", "value": 0}
```

| Operator | Meaning |
|----------|---------|
| `>` | Greater than |
| `<` | Less than |
| `>=` | Greater than or equal |
| `<=` | Less than or equal |

### not

Negates a single rule.

```json
{
  "type": "not",
  "condition": {
    "type": "capability",
    "field": "steer_control_type",
    "equals": "angle"
  }
}
```

### any (OR logic)

Passes if **at least one** child condition passes.

```json
{
  "type": "any",
  "conditions": [
    {"type": "capability", "field": "has_longitudinal_control", "equals": true},
    {"type": "capability", "field": "has_icbm", "equals": true}
  ]
}
```

### all (AND logic)

Passes if **all** child conditions pass. (Note: a plain array of rules already uses AND logic. Use `all` inside `any` or `not` for nested logic.)

```json
{
  "type": "all",
  "conditions": [
    {"type": "param_compare", "key": "SpeedLimitMode", "op": ">", "value": 0},
    {"type": "param_compare", "key": "SpeedLimitOffsetType", "op": ">", "value": 0}
  ]
}
```

---

## Common Scenarios

### 1. Add a new toggle to an existing section

Find the panel and section, add to `items`:

```json
// In settings_ui.json, under device panel -> general section -> items
{
  "key": "FirehoseMode",
  "widget": "toggle",
  "enablement": [{"type": "offroad_only"}]
}
```

Add metadata:
```json
// In params_metadata.json
"FirehoseMode": {
  "title": "Firehose Mode",
  "description": "Upload all driving data continuously."
}
```

### 2. Add a multi-button selector with options

```json
// In settings_ui.json
{
  "key": "RecordingQuality",
  "widget": "multiple_button"
}
```

Options come from metadata:
```json
// In params_metadata.json
"RecordingQuality": {
  "title": "Recording Quality",
  "options": [
    {"value": 0, "label": "Low (720p)"},
    {"value": 1, "label": "Medium (1080p)"},
    {"value": 2, "label": "High (4K)"}
  ]
}
```

### 3. Add a slider/range control

```json
// In settings_ui.json
{
  "key": "FollowDistance",
  "widget": "option"
}
```

Range comes from metadata:
```json
// In params_metadata.json
"FollowDistance": {
  "title": "Follow Distance",
  "description": "Time gap to lead vehicle.",
  "min": 0.5,
  "max": 3.0,
  "step": 0.1,
  "unit": "seconds"
}
```

### 4. Show a setting only when another setting is enabled

```json
{
  "key": "BlinkerMinLateralControlSpeed",
  "widget": "option",
  "visibility": [
    {"type": "param", "key": "BlinkerPauseLateralControl", "equals": true}
  ]
}
```

### 5. Show a setting only for specific cars

```json
{
  "key": "SmartCruiseControlVision",
  "widget": "toggle",
  "visibility": [
    {
      "type": "any",
      "conditions": [
        {"type": "capability", "field": "has_longitudinal_control", "equals": true},
        {"type": "capability", "field": "has_icbm", "equals": true}
      ]
    }
  ]
}
```

### 6. Mutual exclusion (two toggles that can't both be on)

Each toggle's `enablement` requires the other to be `false`:

```json
{
  "key": "EnforceTorqueControl",
  "widget": "toggle",
  "enablement": [
    {"type": "offroad_only"},
    {"type": "param", "key": "NeuralNetworkLateralControl", "equals": false}
  ]
},
{
  "key": "NeuralNetworkLateralControl",
  "widget": "toggle",
  "enablement": [
    {"type": "offroad_only"},
    {"type": "param", "key": "EnforceTorqueControl", "equals": false}
  ]
}
```

Both toggles are visible. When one is on, the other is greyed out.

### 7. Add a new section to a panel

Add a section object to the panel's `sections` array:

```json
{
  "id": "comfort",
  "title": "Comfort",
  "description": "Steering feel and responsiveness tuning",
  "order": 5,
  "items": [
    {"key": "SteeringResponsiveness", "widget": "option"}
  ]
}
```

The frontend renders this as a new card with a "Comfort" header.

### 8. Add a sub-panel (drill-down page)

```json
{
  "id": "comfort",
  "title": "Comfort",
  "items": [
    {"key": "SteeringResponsiveness", "widget": "option"}
  ],
  "sub_panels": [
    {
      "id": "advanced_steering",
      "label": "Advanced Steering",
      "trigger_key": "SteeringResponsiveness",
      "items": [
        {"key": "SteeringDeadzone", "widget": "option"},
        {"key": "SteeringRampRate", "widget": "option"}
      ]
    }
  ]
}
```

A "Advanced Steering >" chevron row appears. Tapping it opens a slide-in sub-panel.

### 9. Add vehicle-specific settings

Add to `vehicle_settings` in `settings_ui.json`:

```json
"rivian": [
  {
    "key": "RivianOnePedalMode",
    "widget": "toggle",
    "enablement": [{"type": "offroad_only"}]
  }
]
```

Only users with a Rivian (where `capabilities.brand === "rivian"`) see this on the Vehicle page.

### 10. Change display text only

Edit only `params_metadata.json` -- no `settings_ui.json` change needed:

```json
"Mads": {
  "title": "M.A.D.S.",
  "description": "Modified Assistive Driving Safety -- keep lateral active without cruise."
}
```

### 11. Move a setting from one panel to another

1. Remove the item from its current panel/section in `settings_ui.json`
2. Add it to the target panel/section
3. Run the validator (catches duplicate keys if you forget to remove)

### 12. Reorder sections within a panel

Add or change `order` fields on the sections:

```json
{"id": "mads", "title": "MADS", "order": 1, ...},
{"id": "lane_change", "title": "Lane Change", "order": 2, ...},
{"id": "blinker", "title": "Blinker Control", "order": 3, ...},
{"id": "torque", "title": "Torque Control", "order": 4, ...}
```

Or simply reorder the items in the JSON array -- array position is used when `order` is not set.

### 13. Grey out a setting while driving

Use `enablement` with `offroad_only`:

```json
{
  "key": "MyParam",
  "widget": "toggle",
  "enablement": [{"type": "offroad_only"}]
}
```

The toggle is visible but disabled while driving. The frontend shows an "Offroad" badge.

### 14. Conditionally show a sub-panel

The sub-panel row only appears when `trigger_condition` passes:

```json
{
  "id": "torque_settings",
  "label": "Torque Settings",
  "trigger_key": "EnforceTorqueControl",
  "trigger_condition": {
    "type": "param",
    "key": "EnforceTorqueControl",
    "equals": true
  },
  "items": [...]
}
```

"Torque Settings >" only shows when "Enforce Torque Control" is on.

### 15. Complex nested rule: visible only when multiple conditions are met

```json
{
  "key": "SpeedLimitValueOffset",
  "widget": "option",
  "visibility": [
    {
      "type": "all",
      "conditions": [
        {"type": "param_compare", "key": "SpeedLimitMode", "op": ">", "value": 0},
        {"type": "param_compare", "key": "SpeedLimitOffsetType", "op": ">", "value": 0}
      ]
    }
  ]
}
```

This item is hidden unless BOTH SpeedLimitMode > 0 AND SpeedLimitOffsetType > 0.

---

## Validation

**Always run after editing `settings_ui.json`:**

```bash
python sunnypilot/sunnylink/tools/validate_settings_ui.py
```

The validator performs 10 checks:

| Check | What it catches |
|-------|----------------|
| JSON parseable | Syntax errors, trailing commas, missing brackets |
| Structural | Missing required fields (id, key, widget, etc.) |
| Param existence | Keys not found in params_metadata.json (warns, doesn't fail) |
| No duplicate keys | Same param key in multiple panels |
| Rule well-formedness | Invalid rule types, missing fields, bad operators |
| Capability refs | Capability field names that don't exist |
| No self-reference | Item whose rule references its own key |
| Sub-panel triggers | trigger_key that doesn't exist in the same panel |
| Ordering | Duplicate panel order values |
| Vehicle brands | Non-lowercase brand keys |

**Example output (all passing):**
```
OK: JSON parseable
OK: structural
OK: param existence
OK: no duplicate keys
OK: rule well-formedness
OK: capability refs
OK: no self-reference
OK: sub-panel triggers
OK: ordering
OK: vehicle brands

============================================================
Summary: 10 checks passed, 0 checks failed
Result: PASS
```

---

## IDE Support

`settings_ui.json` references a JSON Schema file for editor autocomplete:

```json
{
  "$schema": "./settings_ui.schema.json",
  ...
}
```

In VS Code or JetBrains IDEs, this provides:
- Autocomplete for field names
- Enum validation for widget types and rule types
- Red squiggles for structural errors
- Hover documentation

---

## Checklist

Before committing changes to `settings_ui.json` or `params_metadata.json`:

- [ ] Param registered in `common/params_keys.h` with correct type
- [ ] Metadata added in `params_metadata.json` (title required, description recommended)
- [ ] Item placed in correct panel/section in `settings_ui.json`
- [ ] Widget type matches the param type (toggle for BOOL, option/multiple_button for INT/FLOAT)
- [ ] Visibility rules use correct capability field names
- [ ] Enablement includes `offroad_only` for settings that should not change while driving
- [ ] `python sunnypilot/sunnylink/tools/validate_settings_ui.py` passes
- [ ] No metadata fields duplicated in `settings_ui.json` (title, description, options come from metadata)

---

## FAQ

**Q: Do I need to modify any frontend code?**
No. The frontend renders whatever the schema contains. All UI changes are made through `settings_ui.json` and `params_metadata.json`.

**Q: When does the frontend pick up my changes?**
At device boot, the generator reads both files, merges them, compresses the result, and writes it to the `SettingsSchema` param. The frontend fetches this when it connects to the device.

**Q: What if my param key doesn't exist in params_metadata.json yet?**
The validator warns but doesn't fail. The item will render without a title (showing the raw key name). Add metadata for a proper display name.

**Q: Can I override the title from metadata for a specific context?**
Yes. Add `"title": "Custom Title"` directly on the item in `settings_ui.json`. Item-level fields take precedence over metadata.

**Q: What's the difference between `visibility` and `enablement`?**
- `visibility`: hidden entirely when rules fail (user doesn't know it exists)
- `enablement`: visible but greyed out when rules fail (user sees it but can't change it)

**Q: How do I test my changes locally?**
Run the generator directly to see the full merged output:
```bash
python sunnypilot/sunnylink/tools/generate_settings_schema.py
```

**Q: What happens if I add a key that doesn't exist in params_keys.h?**
The validator warns about it. The frontend will render the item but won't be able to read/write the value (it won't exist in the device's param store).

---

## How Capabilities Work

Capabilities are **car-derived boolean/string fields** that rules can reference. They bridge CarParams (device-specific) to the schema (declarative).

### Generation pipeline (`capabilities.py`)

```
Device boot
  |
  v
CarParamsPersistent (serialized CarParams from car fingerprint)
  |
  v
capabilities.py: generate_capabilities()
  |
  +-- Phase 1: All fields default to False / ""
  +-- Phase 2: Boolean params (IsReleaseBranch, etc.) -- no CarParams needed
  +-- Phase 3: CarParams-derived (alphaLongitudinalAvailable, brand, etc.)
  +-- Phase 3b: CarParamsSP-derived (ICBM, Tesla flags)
  |
  v
SettingsCapabilities JSON param (written to device param store)
  |
  v (fetched by frontend via getParams RPC)
Frontend rule evaluator checks capabilities.field === equals
```

### Capability fields and their sources

| Field | Type | Source | Description |
|-------|------|--------|-------------|
| `has_longitudinal_control` | bool | `CP.openpilotLongitudinalControl` or `AlphaLongitudinalEnabled` | Car supports openpilot longitudinal |
| `has_icbm` | bool | `CP_SP.intelligentCruiseButtonManagementAvailable` AND `IntelligentCruiseButtonManagement` param | ICBM active |
| `icbm_available` | bool | `CP_SP.intelligentCruiseButtonManagementAvailable` | ICBM is available for this car |
| `torque_allowed` | bool | `CP.lateralTuning.which() == "torque"` | Torque lateral control supported |
| `brand` | string | `CP.brand` | Vehicle brand (e.g., "toyota", "hyundai") |
| `pcm_cruise` | bool | `CP.pcmCruise` | PCM cruise control |
| `alpha_long_available` | bool | `CP.alphaLongitudinalAvailable` | Alpha longitudinal feature available |
| `steer_control_type` | string | `CP.lateralTuning.which()` | Steering control type ("angle", "torque") |
| `enable_bsm` | bool | `CP.enableBsm` | Blind spot monitoring available |
| `is_release` | bool | `IsReleaseBranch` param | Running release branch |
| `is_sp_release` | bool | `IsReleaseSpBranch` param | Running SP release branch |
| `is_development` | bool | `IsDevelopmentBranch` param | Running development branch |
| `tesla_has_vehicle_bus` | bool | `CP_SP.flags & TeslaFlagsSP.HAS_VEHICLE_BUS` | Tesla with vehicle bus access |
| `has_stop_and_go` | bool | `CP.openpilotLongitudinalControl` | Stop and go capability |
| `stock_longitudinal` | bool | `ToyotaEnforceStockLongitudinal` param | Using stock longitudinal |

### When capabilities are unavailable

When `CarParamsPersistent` hasn't been written yet (no car detected), ALL CarParams-derived capabilities default to `False` or `""`. The frontend rule evaluator treats **null capabilities as permissive** (returns `true`) to avoid hiding settings before capabilities load. Once capabilities arrive, rules are evaluated normally.

This means:
- Items with `visibility: [capability: torque_allowed == true]` will be **temporarily visible** before caps load, then hidden if the car doesn't support torque
- Items with `enablement: [capability: has_longitudinal_control == true]` will be **temporarily enabled**, then disabled

This is intentional — it prevents a jarring flash of empty panels on page load.

---

## Schema Generator Pipeline (`generate_settings_schema.py`)

### What the generator does

```python
# Simplified flow
def generate_schema():
    definition = load("settings_ui.json")       # Step 1: Load structure
    panels = deep_copy(definition["panels"])

    for panel in panels:
        flatten_sections(panel)                  # Step 2: Generate backward-compat flat items

    schema = {
        "schema_version": "1.0",
        "generated_at": "...",
        "panels": panels,
        "vehicle_settings": definition["vehicle_settings"],
        "capability_fields": list(CAPABILITY_FIELDS),
    }

    metadata = load("params_metadata.json")      # Step 3: Load metadata
    enrich_schema(schema, metadata)              # Step 4: Merge titles/options/ranges

    return schema                                # Step 5: Return merged schema
```

### Metadata enrichment rules

For each item, the generator fills in fields from `params_metadata.json` **only if the field is not already set in the definition**:

| Field | Source | Override? |
|-------|--------|-----------|
| `title` | `params_metadata.json[key].title` | Yes -- set in `settings_ui.json` to override |
| `description` | `params_metadata.json[key].description` | Yes |
| `options` | `params_metadata.json[key].options` | Yes |
| `min` | `params_metadata.json[key].min` | Yes |
| `max` | `params_metadata.json[key].max` | Yes |
| `step` | `params_metadata.json[key].step` | Yes |
| `unit` | `params_metadata.json[key].unit` | Yes |

### Backward compatibility

Panels with `sections` automatically get flat `items` and `sub_panels` arrays generated from those sections. This supports older frontends that don't understand sections.

### Compression

The final schema is compressed before writing to the param store:
1. JSON serialize (compact, no whitespace) -- ~36KB
2. gzip compress -- ~5KB
3. base64 encode -- ~7KB string

The frontend detects compressed data (gzip magic bytes `H4sI`) and decompresses automatically. Uncompressed JSON is also accepted for backward compatibility.

---

## Device-Side Dialogs vs. Frontend Widgets

The device UI uses several dialog types that have **no direct equivalent** in the schema. Instead, the schema maps them to the closest frontend widget type.

### TreeOptionDialog (device) -> `multiple_button` or `option` (schema)

On the device, `TreeOptionDialog` renders a hierarchical tree selector with search and favorites. Used for:

| Param | Device dialog | Schema widget | Frontend renders as |
|-------|--------------|---------------|-------------------|
| `TorqueControlTune` | TreeOptionDialog (torque version list from JSON) | `multiple_button` | Segmented buttons (options from metadata) |

The frontend doesn't need a tree selector because the options are flat — the tree structure on the device is for navigating large lists (e.g., model downloads), which the frontend handles with its own dedicated pages.

### MultiOptionDialog (device) -> `info` (schema)

On the device, `MultiOptionDialog` renders a scrollable flat list picker. Used for:

| Param | Device dialog | Schema widget | Frontend renders as |
|-------|--------------|---------------|-------------------|
| `LanguageSetting` | MultiOptionDialog (language list) | `info` | Read-only display |

Language selection is not remotely configurable — it requires a device reboot and locale change. The schema shows it as `info` (display-only).

### ConfirmDialog (device) -> handled by frontend

On the device, `ConfirmDialog` shows a two-button confirmation before toggling certain params. The frontend handles confirmation for destructive operations in its own push flow — no schema representation needed.

Params that use ConfirmDialog on device:
- `AlphaLongitudinalEnabled` — confirmation before enabling alpha longitudinal
- `ExperimentalMode` — confirmation before enabling
- `OffroadMode` — double confirmation before forcing offroad
- Calibration reset — confirmation before deleting calibration data

### OptionControlSP (device) -> `option` (schema)

On the device, `OptionControlSP` renders a +/- stepper with numeric display. In the schema, this maps to `widget: "option"` with `min`/`max`/`step` from metadata. The frontend renders it as a **slider** when range metadata is present.

| Device widget | Schema widget | Frontend renders as | Metadata needed |
|--------------|---------------|-------------------|----------------|
| `option_item_sp(min=0, max=255, step=5)` | `"option"` | Slider | `min`, `max`, `step` in params_metadata.json |

---

## Parity Reference: Device UI vs. sunnylink Frontend

### Full param coverage

All **80 remotely-configurable params** from the device settings layouts are present in `settings_ui.json`. This was verified by auditing every non-mici layout file:

| Layout file | Params | All in schema? |
|-------------|--------|---------------|
| `steering.py` + sub-layouts | 17 | Yes |
| `cruise.py` + sub-layouts | 10 | Yes |
| `display.py` | 3 | Yes |
| `visuals.py` | 13 | Yes |
| `developer.py` (upstream + SP) | 10 | Yes |
| `sunnylink.py` | 2 | Yes |
| `device.py` (upstream + SP) | 10 | Yes |
| `models.py` | 5 | Yes |
| `toggles.py` | 9 | Yes |
| Vehicle settings | 6 | Yes |

### Known behavior differences

These are intentional differences between the device UI and the frontend rendering:

| Param | Device behavior | Frontend behavior | Why |
|-------|----------------|-------------------|-----|
| `EnforceTorqueControl` | Hidden when CP=None | Visible but disabled (torque_allowed=false) | Frontend uses permissive defaults before caps load |
| `NeuralNetworkLateralControl` | Hidden when CP=None | Visible but disabled | Same as above |
| `AlphaLongitudinalEnabled` | Disabled when engaged | No engagement check | Frontend can't detect real-time engagement state |
| `SpeedLimitMode` | "Assist" option disabled for Tesla/Rivian SP release | All options enabled | Per-option disabling not supported in schema |
| `MadsMainCruiseAllowed` | Hidden for limited MADS platforms (Tesla w/o bus, Rivian) | Visible (no platform-specific rule) | Would require new capability fields |
| `LanguageSetting` | MultiOptionDialog picker | Read-only info display | Language change requires device reboot |
| `TorqueControlTune` | TreeOptionDialog with version folders | Segmented buttons | Options are flat on frontend |

### Panels NOT in schema (device-only)

These panels exist on the device but are intentionally excluded from the schema because they involve device-local operations:

| Panel | Why excluded |
|-------|-------------|
| Network | WiFi scanning, connection management -- device-local hardware |
| Software | Update download/install -- device-local operation |
| Trips | Read-only drive statistics from API |
| OSM | Offline map download/management -- large file operations |
| Navigation | Not yet implemented on device |

### Device UI features not representable in schema

| Feature | Description | Workaround |
|---------|-------------|------------|
| ConfirmDialog | Two-step confirmation before toggling | Frontend has its own push confirmation flow |
| Param removal | Device removes params when feature unavailable | Frontend hides via visibility rules |
| OnroadCycleRequested | Some toggles trigger a restart | Frontend push doesn't trigger restart -- device handles on next boot |
| Lock params | `{Param}Lock` disables user control | Not needed for remote config |
| Metric scaling | Speed values scale by IsMetric | Frontend reads IsMetric and formats accordingly |
| Mutual exclusion side effects | JoystickDebugMode resets LongitudinalManeuverMode | Frontend uses enablement rules only (no cross-param reset) |
