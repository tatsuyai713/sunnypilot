---
title: Cruise Control Settings
---

# Cruise Control Settings

Settings for adaptive cruise control behavior, including intelligent button management, smart cruise features, and custom speed increments.

**Location:** Settings → sunnypilot → Cruise Control

---

## Intelligent Cruise Button Management (ICBM)

| Property | Value |
|----------|-------|
| **Param** | `IntelligentCruiseButtonManagement` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Allows sunnypilot to dynamically manage cruise speed by intercepting button presses on the steering wheel. When enabled, speed adjustments are handled intelligently to support features like Speed Limit Assist.

!!! info "Requirements"
    - Vehicle must support ICBM (shown only when `intelligentCruiseButtonManagementAvailable` is true in car parameters)

!!! note "Vehicle Compatibility"
    Not all vehicles support ICBM. If this toggle does not appear, your vehicle does not support this feature.

---

## Smart Cruise Control — Vision (SCC-V)

| Property | Value |
|----------|-------|
| **Param** | `SmartCruiseControlVision` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Uses vision-based data to automatically reduce cruise speed when approaching curves. Monitors predicted lateral acceleration and smoothly decelerates when entering turns, then accelerates back to set speed when exiting.

!!! info "Requirements"
    - Longitudinal control must be available, **or** ICBM must be enabled

---

## Smart Cruise Control — Map (SCC-M)

| Property | Value |
|----------|-------|
| **Param** | `SmartCruiseControlMap` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Uses map data to proactively adjust cruise speed before speed-restricted areas and mapped turns. Calculates deceleration distance based on current speed and upcoming waypoint target velocities.

!!! info "Requirements"
    - Longitudinal control must be available, **or** ICBM must be enabled

---

## Custom ACC Increments

| Property | Value |
|----------|-------|
| **Param** | `CustomAccIncrementsEnabled` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables customization of how much the set speed changes with short and long button presses on the steering wheel.

!!! info "Requirements"
    - Longitudinal control must be available, **or** ICBM must be enabled
    - PCM Cruise must not be active

### Short Press Increment

| Property | Value |
|----------|-------|
| **Param** | `CustomAccShortPressIncrement` |
| **Type** | Option selector |
| **Range** | 1–10 |
| **Default** | 1 |

Sets the speed change (in your unit preference: km/h or mph) for a short press of the cruise speed button.

### Long Press Increment

| Property | Value |
|----------|-------|
| **Param** | `CustomAccLongPressIncrement` |
| **Type** | Option selector |
| **Options** | 1 → 1, 2 → 5, 3 → 10 |
| **Default** | 1 (value: 1) |

Sets the speed change for a long press. The mapping is:

| Selection | Speed Change |
|-----------|-------------|
| 1 | 1 km/h (or mph) |
| 2 | 5 km/h (or mph) |
| 3 | 10 km/h (or mph) |

---

## Dynamic Experimental Control (DEC)

| Property | Value |
|----------|-------|
| **Param** | `DynamicExperimentalControl` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Automatically switches between openpilot and experimental mode based on driving conditions. When enabled, the system uses real-time signals (speed, turn detection, stop signs, traffic lights) to determine the most appropriate driving mode.

!!! info "Requirements"
    - Longitudinal control must be available
    - Device must be offroad to toggle

---

## Speed Limit Assist

Speed Limit Assist settings are located in a sub-panel within Cruise Control. See the dedicated [Speed Limit Settings](speed-limit.md) page for full details.

---

## Related Features

- [Intelligent Cruise Button Management](../features/icbm.md)
- [Smart Cruise Control — Vision](../features/scc-v.md)
- [Smart Cruise Control — Map](../features/scc-m.md)
- [Custom ACC Increments](../features/custom-acc-increments.md)
- [Dynamic Experimental Control](../features/dynamic-experimental-control.md)
