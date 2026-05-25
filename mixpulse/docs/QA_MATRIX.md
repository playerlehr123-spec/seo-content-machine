# WaveFrame QA Matrix

Status values: Untested, Pass, Fail, Needs retest, N/A.

## Standalone
| Test | QA level | Status | Notes |
| --- | --- | --- | --- |
| Artifact unzips | Level 0 | Untested |  |
| Standalone EXE exists if expected | Level 0 | Untested |  |
| App launches | Level 1 | Untested |  |
| App closes cleanly | Level 1 | Untested |  |
| Window resize works | Level 1 | Untested |  |
| Settings opens | Level 1 | Untested |  |
| Meters move | Level 1 | Untested |  |
| Audio pass-through unchanged | Level 1 | Untested |  |
| Output opens | Level 1 | Untested |  |
| Output close/reopen works | Level 1 | Untested |  |
| Fullscreen works | Level 1 | Untested |  |
| Frame does not crash | Level 1 | Untested |  |
| HUD toggles | Level 1 | Untested |  |
| Module selector works | Level 3 | Untested |  |
| Template selector works | Level 3 | Untested |  |
| Preset save/load/reset does not crash | Level 3 | Untested |  |
| Brand fields/defaults display | Level 3 | Untested |  |

## DAWs
| DAW | Version | Plugin scanned | Plugin loads | Audio pass-through unchanged | Meters move | UI opens | Output opens | Frame works | HUD works | Remove/reload works | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| Ableton Live |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| FL Studio |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| Reaper |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| Bitwig |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |
| Other |  | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested | Untested |  |

## OBS
| Test | QA level | Status | Notes |
| --- | --- | --- | --- |
| Output window appears in OBS Window Capture | Level 4 | Untested |  |
| Output captures while resized | Level 4 | Untested |  |
| Output captures in fullscreen | Level 4 | Untested |  |
| Short external recording works | Level 4 | Untested |  |
| OBS workflow docs are understandable | Level 4 | Untested |  |

## Artifacts
| Test | QA level | Status | Notes |
| --- | --- | --- | --- |
| Latest CI run green | Level 0 | Untested |  |
| `MixPulse-Windows-Beta` exists | Level 0 | Untested |  |
| `MixPulse-Windows-Build-Folder` exists | Level 0 | Untested |  |
| `README_INSTALL.txt` exists | Level 0 | Untested |  |
| EXE or VST3 exists | Level 0 | Untested |  |
| Artifact naming mismatch is documented | Level 0 | Untested | WaveFrame user-facing, MixPulse internal/artifact. |

## Longer Stability
| Test | QA level | Status | Notes |
| --- | --- | --- | --- |
| App idles for 15 minutes | Level 5 | Untested |  |
| Output open/close repeated 10 times | Level 5 | Untested |  |
| Module/template switching repeated 20 times | Level 5 | Untested |  |
| Frame clicked 10 times | Level 5 | Untested |  |
| DAW remove/reload repeated 5 times | Level 5 | Untested |  |
