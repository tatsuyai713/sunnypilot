# sunnylink Settings UI Guide

> Edit two JSON files, run the validator, commit. The sunnylink frontend updates automatically.

For detailed architecture, capability fields, parity analysis, and dialog mappings, see [REFERENCE.md](REFERENCE.md).

## The Two Files You Edit

| File | What | When to edit |
|------|------|-------------|
| `settings_ui.json` | Structure, widget types, visibility/enablement rules | Adding/moving/removing a setting, changing when it shows |
| `params_metadata.json` | Titles, descriptions, option labels, min/max/step/unit | Changing display text or value constraints |

## Quick Reference: Widget Types

| Widget | Use for | Metadata needed |
|--------|---------|----------------|
| `toggle` | On/off boolean | title |
| `multiple_button` | 2-4 discrete options | title + `options` array |
| `option` | Numeric range or dropdown | title + `min/max/step` or `options` |
| `info` | Read-only display | title |

## Quick Reference: Rule Types

| Rule | Example | Use for |
|------|---------|---------|
| `offroad_only` | `{"type": "offroad_only"}` | Grey out while driving |
| `capability` | `{"type": "capability", "field": "has_longitudinal_control", "equals": true}` | Car-dependent visibility |
| `param` | `{"type": "param", "key": "Mads", "equals": true}` | Show/enable based on another setting |
| `param_compare` | `{"type": "param_compare", "key": "SpeedLimitMode", "op": ">", "value": 0}` | Numeric comparison |
| `not` | `{"type": "not", "condition": {...}}` | Negate a rule |
| `any` | `{"type": "any", "conditions": [...]}` | OR logic |
| `all` | `{"type": "all", "conditions": [...]}` | AND logic (for nesting inside `any`/`not`) |

`visibility` = hidden when rules fail. `enablement` = greyed out when rules fail.

Capability fields: `has_longitudinal_control`, `has_icbm`, `icbm_available`, `torque_allowed`, `brand`, `pcm_cruise`, `alpha_long_available`, `steer_control_type`, `enable_bsm`, `is_release`, `is_sp_release`, `is_development`, `tesla_has_vehicle_bus`, `has_stop_and_go`, `stock_longitudinal`

---

## How To

### Add a new toggle

1. Register in `common/params_keys.h`:
   ```cpp
   {"MyToggle", {PERSISTENT | BACKUP, BOOL}},
   ```

2. Add metadata in `params_metadata.json`:
   ```json
   "MyToggle": {"title": "My Feature", "description": "What it does."}
   ```

3. Add to `settings_ui.json` in the right panel/section `items` array:
   ```json
   {"key": "MyToggle", "widget": "toggle", "enablement": [{"type": "offroad_only"}]}
   ```

4. Validate: `python sunnypilot/sunnylink/tools/validate_settings_ui.py`

### Add a multi-button selector

`settings_ui.json`:
```json
{"key": "MySelector", "widget": "multiple_button"}
```

`params_metadata.json`:
```json
"MySelector": {
  "title": "Mode",
  "options": [{"value": 0, "label": "Off"}, {"value": 1, "label": "On"}, {"value": 2, "label": "Auto"}]
}
```

### Add a slider/range

`settings_ui.json`:
```json
{"key": "MyRange", "widget": "option"}
```

`params_metadata.json`:
```json
"MyRange": {"title": "Distance", "min": 0.5, "max": 3.0, "step": 0.1, "unit": "seconds"}
```

### Show only when another setting is on

```json
{"key": "ChildSetting", "widget": "toggle",
 "visibility": [{"type": "param", "key": "ParentToggle", "equals": true}]}
```

### Show only for certain cars

```json
{"key": "LongFeature", "widget": "toggle",
 "visibility": [{"type": "capability", "field": "has_longitudinal_control", "equals": true}]}
```

### Mutual exclusion (only one can be on)

```json
{"key": "OptionA", "widget": "toggle",
 "enablement": [{"type": "param", "key": "OptionB", "equals": false}]},
{"key": "OptionB", "widget": "toggle",
 "enablement": [{"type": "param", "key": "OptionA", "equals": false}]}
```

### Add a new section

Add to panel's `sections` array in `settings_ui.json`:
```json
{"id": "my_section", "title": "My Section", "description": "Optional subtitle", "items": [...]}
```

### Add a sub-panel (drill-down page)

Add to a section's `sub_panels` array:
```json
{"id": "my_sub", "label": "Advanced Settings", "trigger_key": "ParentParam",
 "trigger_condition": {"type": "param", "key": "ParentParam", "equals": true},
 "items": [...]}
```

### Add vehicle-specific settings

Add to `vehicle_settings` in `settings_ui.json`:
```json
"rivian": [{"key": "RivianFeature", "widget": "toggle", "enablement": [{"type": "offroad_only"}]}]
```

### Change display text only

Edit `params_metadata.json` only -- no `settings_ui.json` change needed.

### Move a setting between panels

Remove from source panel, add to target panel. Validator catches duplicates.

### Reorder sections

Set `order` field on sections, or reorder the JSON array.

---

## Pre-Commit Checklist

- [ ] Param registered in `common/params_keys.h`
- [ ] Metadata in `params_metadata.json` (title required)
- [ ] Item in `settings_ui.json` with correct widget type
- [ ] `offroad_only` enablement for settings that shouldn't change while driving
- [ ] `python sunnypilot/sunnylink/tools/validate_settings_ui.py` passes
