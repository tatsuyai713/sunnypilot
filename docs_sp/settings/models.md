---
title: Models & AI Settings
---

# Models & AI Settings

Configure driving model behavior and advanced AI parameters.

**Location:** Settings → sunnypilot → Models & AI

---

## Model Selection

Select which driving model to use. Different models may have different driving characteristics and capabilities.

!!! warning "Offroad Only"
    Model selection can only be changed while the vehicle is offroad (parked with ignition off).

---

## Lane Turn Desire

| Property | Value |
|----------|-------|
| **Param** | `LaneTurnDesire` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables lane-aware turn desire signals to the driving model. When active, the model receives enhanced lane positioning cues during turns.

### Lane Turn Value

| Property | Value |
|----------|-------|
| **Param** | `LaneTurnValue` |
| **Type** | Option selector |
| **Range** | 500–2000 (displayed with float scaling) |
| **Default** | 500 |

Adjusts the intensity of the lane turn desire signal sent to the model. Higher values produce a stronger turn desire.

!!! info "Requirements"
    - Lane Turn Desire must be enabled
    - Advanced Controls must be enabled (`ShowAdvancedControls`)

---

## LAGD (Live Lateral Delay Compensation)

| Property | Value |
|----------|-------|
| **Param** | `LagdToggle` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables live steering delay compensation. When enabled, sunnypilot continuously measures the actual steering actuator delay via cross-correlation of desired vs. actual lateral acceleration, and uses the measured value to improve steering responsiveness. When disabled, a fixed delay value is used instead (base actuator delay + the LAGD Delay offset below).

### LAGD Delay

| Property | Value |
|----------|-------|
| **Param** | `LagdToggleDelay` |
| **Type** | Option selector |
| **Range** | 5–50 (displayed with float scaling, in milliseconds) |
| **Default** | 5 |

Sets an additional fixed steering delay offset (in milliseconds) added to the base steering actuator delay. This value is used **when LAGD is disabled** as the total fixed delay for steering compensation. Useful for fine-tuning steering feel on vehicles where the default actuator delay is slightly off.

!!! info "Requirements"
    - LAGD must be **disabled** (this setting configures the fixed fallback delay used when LAGD is off)
    - Advanced Controls must be enabled (`ShowAdvancedControls`)

---

## Related Features

- [Models & AI](../features/models.md)
