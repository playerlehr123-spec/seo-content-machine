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
