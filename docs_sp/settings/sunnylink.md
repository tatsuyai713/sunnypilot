---
title: sunnylink Settings
---

# sunnylink Settings

Configure the sunnylink cloud backend integration for backup/restore, sponsorship, and data upload.

**Location:** Settings > sunnypilot > sunnylink

---

## Enable sunnylink

| Property | Value |
|----------|-------|
| **Param** | `SunnylinkEnabled` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Master toggle for the sunnylink cloud integration. When disabled, all sunnylink features (backup, sponsor status, uploader, remote management) are inactive. Enabling sunnylink requires completing a consent flow on first activation.

---

## Sponsor Status

| Property | Value |
|----------|-------|
| **Type** | Status display / Button |

Displays your current sponsor tier and color. If you are a sponsor, shows your tier name. Tapping opens the sponsor status dialog.

!!! info "Requirements"
    - sunnylink must be enabled

---

## Pair GitHub Account

| Property | Value |
|----------|-------|
| **Type** | Button |

Opens the GitHub pairing dialog to link your GitHub account to this device. Displays current pairing status: "Paired" or "Not Paired".

!!! info "Requirements"
    - sunnylink must be enabled

---

## Enable sunnylink Uploader

| Property | Value |
|----------|-------|
| **Param** | `EnableSunnylinkUploader` |
| **Type** | Toggle (On/Off) |
| **Default** | Off |

Enables driving data upload to sunnypilot cloud infrastructure. Uploads include logs, camera data, and crash reports. Respects metered connections by skipping video on cellular networks.

!!! warning "Infrastructure Test"
    This feature is currently available to high-tier sponsors only and provides no direct user benefit. It exists for infrastructure testing purposes.

!!! info "Requirements"
    - sunnylink must be enabled

---

## Backup / Restore Settings

| Property | Value |
|----------|-------|
| **Type** | Dual button |

Two action buttons for managing settings backups:

- **Backup**: Encrypts and uploads all sunnypilot settings to the cloud. Progress shown in real-time.
- **Restore**: Downloads and restores the most recent backup. Progress shown in real-time.

!!! info "Requirements"
    - sunnylink must be enabled
    - Device must be offroad (not actively driving)

!!! note
    Backups are encrypted with your device's unique keys using AES-256-CBC. Only the same device (or one with the same keys) can decrypt a backup.

---

## Related Features

- [sunnylink](../features/sunnylink.md)
