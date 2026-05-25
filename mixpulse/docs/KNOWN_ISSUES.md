# WaveFrame Known Issues

This list is for v0.1 private beta candidate testing. Unknowns should stay marked as needs verification rather than invented as bugs.

## Current Limitations
- Unsigned Windows beta; SmartScreen or antivirus warnings may appear.
- Artifact, binary, plugin, and internal names may still say MixPulse while the product name is WaveFrame.
- VST3 needs DAW testing across Ableton Live, FL Studio, Reaper, Bitwig, and other hosts.
- Built-in video export is not implemented.
- OBS/manual capture is the current motion workflow.
- Installer and code signing are not implemented yet.
- macOS/AU is not enabled.
- NDI, Spout, Syphon, shader SDK, and virtual camera are not implemented.
- Cloud upload, account system, template marketplace, and telemetry are not implemented.
- Some visual modules/templates may be placeholders or v1 polish rather than final production modules.
- Logo/image import may remain placeholder-only depending on the build.

## Needs Verification
- Output close/reopen stability.
- Frame button behavior across export presets.
- HUD repeated toggle behavior.
- Module/template switching under repeated use.
- Preset save/load/reset stability.
- DAW scan/load/remove/reload.
- Audio pass-through in standalone and VST3.
- OBS Window Capture resize/fullscreen workflow.

## Blocking Issues
Treat these as blockers before sharing v0.1:
- App does not launch.
- Latest CI run is red.
- `MixPulse-Windows-Beta` is missing.
- Plugin does not scan in any tested DAW.
- Audio is muted or changed unexpectedly.
- Crash on open.
- Output window crash.
- `processBlock` audio behavior changed.
