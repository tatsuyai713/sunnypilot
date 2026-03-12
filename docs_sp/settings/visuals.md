---
title: Visuals Settings
---

# Visuals Settings

Configure what information and visual elements appear on the driving screen.

**Location**: `Settings -> Visuals`

!!! device-support "Supported Devices"
    :material-check: comma 3X/3 &nbsp; :material-check: sunnylink &nbsp; :material-close: comma four

---

## Show Blind Spot Warnings

Displays visual warnings on the driving screen when a vehicle is detected in your blind spot. Only available on vehicles equipped with Blind Spot Monitoring (BSM) hardware.

---

## Steering Arc

Shows the steering arc overlay on the driving screen when lateral (steering) control is active. This arc illustrates the path sunnypilot is steering toward.

---

## Enable Tesla Rainbow Mode

Applies a rainbow color effect to the model's planned driving path displayed on screen. This is a cosmetic change only and does not affect driving behavior.

---

## Enable Standstill Timer

Displays a timer on the HUD when the vehicle is stopped. The timer shows how long you have been at a standstill.

---

## Display Road Name

Shows the name of the road you are currently driving on. Requires the OSM map database to be downloaded through the [OSM panel](osm.md).

---

## Green Traffic Light Alert (Beta)

Plays a chime and shows an on-screen alert when the traffic light ahead turns green while you are stopped with no lead vehicle in front. Helps you notice the light change.

---

## Lead Departure Alert (Beta)

Plays a chime and shows an on-screen alert when you are stopped and the vehicle ahead begins moving. Useful for noticing when traffic starts flowing again.

---

## Speedometer: Always Display True Speed

Forces the speedometer to always show the true vehicle speed from wheel speed sensors, rather than the GPS-based speed. Applicable to vehicles where wheel speed and GPS speed differ.

---

## Speedometer: Hide from Onroad Screen

Hides the speedometer from the driving screen entirely. When enabled, no speed is displayed while driving.

---

## Display Turn Signals

Draws visual turn signal indicators on the HUD when the turn signals are active.

---

## Real-time Acceleration Bar

Shows a vertical bar on the left side of the driving screen that indicates real-time acceleration and deceleration. The bar moves up during acceleration and down during braking.

---

## Display Metrics Below Chevron

A row of five buttons that controls what information appears below the lead vehicle chevron on the driving screen:

| Option | What it shows |
|--------|--------------|
| **Off** | Nothing displayed below the chevron |
| **Distance** | Distance to the lead vehicle |
| **Speed** | Speed of the lead vehicle |
| **Time** | Time gap to the lead vehicle |
| **All** | Distance, speed, and time together |

!!! note "Availability"
    Requires sunnypilot longitudinal control.

---

## Developer UI

A row of four buttons that controls the display of real-time developer metrics on the driving screen:

| Option | What it shows |
|--------|--------------|
| **Off** | No developer information displayed |
| **Bottom** | Metrics displayed at the bottom of the screen |
| **Right** | Metrics displayed on the right side |
| **Right & Bottom** | Metrics displayed on both the right side and bottom |

---

## Related Features

- [HUD & Visuals](../features/display/hud-visuals.md)
