---
title: Developer Settings
---

# Developer Settings

Advanced settings for developers and power users. Most of these settings are hidden behind the Advanced Controls toggle.

**Location:** Settings → sunnypilot → Developer

---

## Show Advanced Controls

| Property | Value |
|----------|-------|
| **Param** | `ShowAdvancedControls` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Master toggle that reveals advanced settings throughout the sunnypilot UI. Many settings across different panels are only visible when this is enabled.

**Settings gated by Advanced Controls:**

- Models & AI → Lane Turn Value, LAGD Delay
- Software → Disable Updates
- Developer → GitHub Runner, Error Log, Copyparty, Quick Boot

---

## Enable GitHub Runner

| Property | Value |
|----------|-------|
| **Param** | `EnableGithubRunner` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables the GitHub Actions self-hosted runner on the device. This allows the device to execute CI/CD jobs.

!!! info "Requirements"
    - Advanced Controls must be enabled
    - Only available on non-release branches

---

## Enable Copyparty

| Property | Value |
|----------|-------|
| **Param** | `EnableCopyparty` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables the Copyparty file sharing server on the device, allowing easy file transfer to and from the device over the network.

!!! info "Requirements"
    - Advanced Controls must be enabled

---

## Error Log

| Property | Value |
|----------|-------|
| **Param** | N/A (action button) |
| **Type** | Button |

Opens the error log viewer, showing recent system errors and warnings. Useful for diagnosing issues with sunnypilot features or vehicle communication.

!!! info "Requirements"
    - Advanced Controls must be enabled

---

## Quick Boot

| Property | Value |
|----------|-------|
| **Param** | `QuickBootToggle` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables a faster boot sequence by skipping certain initialization steps. Can reduce the time from power-on to driving readiness.

!!! info "Requirements"
    - Advanced Controls must be enabled
    - Updates must not be disabled (`DisableUpdates` must be Off)
