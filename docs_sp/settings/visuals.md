---
title: Visuals & HUD Settings
---

# Visuals & HUD Settings

Customize what information is displayed on the driving screen (HUD) while driving.

**Location:** Settings → sunnypilot → Visuals & HUD

---

## Toggles

These are on/off toggles for individual HUD elements.

| Toggle | Param | Description |
|--------|-------|-------------|
| **Blind Spot Indicator** | `BlindSpot` | Shows a visual indicator when a vehicle is detected in your blind spot |
| **Torque Bar** | `TorqueBar` | Displays a bar showing the current steering torque applied |
| **Rainbow Mode** | `RainbowMode` | Adds a colorful visual effect to the driving path |
| **Standstill Timer** | `StandstillTimer` | Shows how long you've been stopped at a standstill |
| **Road Name** | `RoadNameToggle` | Displays the name of the road you're currently on |
| **Green Light Alert** | `GreenLightAlert` | Alerts you when a traffic light turns green while you're stopped |
| **Lead Depart Alert** | `LeadDepartAlert` | Alerts you when the car ahead starts moving while you're stopped |
| **True Vehicle Speed** | `TrueVEgoUI` | Shows the true vehicle speed from the CAN bus (may differ from GPS speed) |
| **Hide Speed** | `HideVEgoUI` | Hides the speed display from the HUD entirely |
| **Turn Signals** | `ShowTurnSignals` | Shows the turn signal status on the HUD |
| **Rocket Fuel** | `RocketFuel` | Displays a real-time acceleration bar on the left side of the driving screen. Green indicates acceleration, red indicates deceleration. |

---

## Chevron Info

| Property | Value |
|----------|-------|
| **Param** | `ChevronInfo` |
| **Type** | Multi-button selector |
| **Options** | Off · Distance · Speed · Time · All |
| **Default** | Off |

Controls what information is displayed near the lead vehicle chevron (the triangle marker shown above the car ahead of you):

| Option | What's Shown |
|--------|-------------|
| **Off** | No additional info near the chevron |
| **Distance** | Distance to the lead vehicle |
| **Speed** | Speed of the lead vehicle |
| **Time** | Time gap to the lead vehicle |
| **All** | All of the above |

!!! info "Requirements"
    - Longitudinal control must be available

---

## Developer UI Info

| Property | Value |
|----------|-------|
| **Param** | `DevUIInfo` |
| **Type** | Multi-button selector |
| **Options** | Off · Bottom · Right · Right & Bottom |
| **Default** | Off |

Shows developer/debug information on the driving screen. Useful for diagnostics and troubleshooting.

| Option | Display Location |
|--------|-----------------|
| **Off** | No developer info shown |
| **Bottom** | Developer info at the bottom of the screen |
| **Right** | Developer info on the right side |
| **Right & Bottom** | Developer info on both right and bottom |

---

## Related Features

- [HUD & Visuals](../features/hud-visuals.md)
