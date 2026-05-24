# WaveFrame Known Issues

This list is for private beta testing. It should describe known limitations truthfully without inventing unverified bugs.

## Current Known Limitations
- Windows builds are unsigned. SmartScreen or antivirus warnings may appear.
- Artifacts, binaries, plugin IDs, or folders may still say MixPulse while the product name is WaveFrame.
- VST3 testing is still required across multiple DAWs.
- Output window capture relies on OBS or another external capture tool.
- Built-in video export is not implemented.
- NDI, Spout, Syphon, virtual camera, and shader SDK support are not implemented.
- Logo/image import may be placeholder-only depending on the build.
- Some templates and visual modules may be placeholders or v1 polish rather than final production modules.
- There is no installer.
- There is no auto-update system.
- macOS/AU builds are not enabled.
- No cloud upload, account system, template marketplace, or telemetry is included.

## Known Test Areas
Mark each item as Pass, Fail, or Needs manual verification during beta testing.

| Area | Status | Notes |
| --- | --- | --- |
| Output close/reopen | Needs manual verification | Confirm repeated clicks do not create unstable windows. |
| Frame button behavior | Needs manual verification | Confirm still-frame behavior is clear and does not crash. |
| HUD toggle | Needs manual verification | Confirm repeated on/off toggles are stable. |
| Fullscreen | Needs manual verification | Confirm enter/exit works in standalone and output window. |
| Module/template switching | Needs manual verification | Confirm switching does not crash or blank the renderer. |
| Preset save/load/reset | Needs manual verification | Confirm defaults restore sane creator state. |
| DAW scan/load | Needs manual verification | Test Ableton Live, FL Studio, Reaper, Bitwig where available. |
| DAW remove/reload | Needs manual verification | Confirm removing and reloading the plugin is stable. |
| Audio pass-through | Needs manual verification | Confirm no gain, EQ, compression, limiting, or other audio effects. |

## Blocking Issues
Treat these as private beta blockers:
- App does not launch.
- Plugin does not scan in any tested DAW.
- Audio is muted, changed, clipped, or processed unexpectedly.
- `processBlock` modifies valid audio samples beyond pass-through requirements.
- UI crashes on load.
- Output window crashes.
- Latest CI artifact is missing.
