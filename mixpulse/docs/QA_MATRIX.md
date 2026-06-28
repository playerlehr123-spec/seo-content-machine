# WaveFrame QA Matrix

Status values:
- Untested
- Pass
- Fail
- Needs retest
- N/A

## Standalone

| Test | Status | Build / Artifact | Notes |
| --- | --- | --- | --- |
| App launches | Untested |  |  |
| UI paints cleanly | Untested |  |  |
| Meters move | Untested |  |  |
| Output opens | Untested |  |  |
| Output closes/reopens | Untested |  |  |
| Fullscreen works | Untested |  |  |
| Frame does not crash | Untested |  |  |
| Export preset switching shows dimensions | Untested |  | Test Current, 9:16, 1:1, 4:5, 16:9 |
| Frame before Output does not crash | Untested |  | Should open/fallback safely |
| Repeated Frame clicks do not crash | Untested |  | Still PNG only |
| HUD toggles | Untested |  |  |
| Module/template switching | Untested |  |  |
| Preset reset/save/load | Untested |  |  |

## DAWs

| DAW | Version | Plugin scanned | Plugin loads | Audio pass-through unchanged | Meters move | UI opens | Output opens | Frame works | HUD works | Remove/reload works | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Ableton Live |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| FL Studio |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| Reaper |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| Bitwig |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| Other |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |

## OBS

| Test | Status | Build / Artifact | Notes |
| --- | --- | --- | --- |
| Output window captured with OBS Window Capture | Untested |  |  |
| Resize does not crash | Untested |  |  |
| Fullscreen capture works | Untested |  |  |
| Short external recording succeeds | Untested |  |  |

## Artifacts

| Artifact | Status | Notes |
| --- | --- | --- |
| `MixPulse-Windows-Beta` | Untested | Download and unzip before testing |
| `MixPulse-Windows-Build-Folder` | Untested | Optional/internal debugging artifact |
| `README_INSTALL.txt` present | Untested | Confirm instructions match current naming |

## Feedback Routing

When a test fails:
- Open a beta bug issue or add a row to `BETA_FEEDBACK_TRACKER.md`.
- Classify severity with `FEEDBACK_TRIAGE_RULES.md`.
- Mark ambiguous reports `Needs info`.
- Move confirmed P0/P1 issues into the next fix sprint.

## v0.2 Sprint 1 Stability Fix Retest

| Fix ID | Area | Status | Retest |
| --- | --- | --- | --- |
| WF-S1-001 | Module/template selection fallback | Needs retest | Switch modules/templates rapidly; verify invalid/default state falls back to Spectrum Bars / first template |
| WF-S1-002 | Brand preset malformed state clamp | Needs retest | Load malformed preset JSON; verify logo opacity/scale/placement remain sane |
| WF-S1-003 | Export preset fallback | Needs retest | Clear or force invalid export preset state; verify UI/export falls back to a valid preset |
| WF-S6-001 | Export preset clarity | Needs retest | Switch each preset and verify aspect, dimensions, use case, and still-PNG workflow text |
| WF-S6-002 | Frame/current-frame failure handling | Needs retest | Click Frame before Output, after Output, repeatedly, and with future-only presets |
| WF-S8-001 | Current-window PNG rendering | Needs retest | In Ableton, select Current, click Frame, confirm the PNG contains the visual scene, and confirm Explorer reveals the file |
| WF-S8-002 | Creator control-row layout | Needs retest | Open the normal creator view at minimum and default sizes; verify Preset, Module, Beat Sync, Tap, and Full do not overlap |
| WF-S9-001 | Live modular workspace | Needs retest | Play audio in Ableton; verify the central workspace animates, metric tiles update, and controls remain usable |
| WF-S9-002 | Modular UI resizing | Needs retest | Resize from 980x620 through 1280x720 and larger; verify command bar, signal rail, workspace, and inspector remain readable |
