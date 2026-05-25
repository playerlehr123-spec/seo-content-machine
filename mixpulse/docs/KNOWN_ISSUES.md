# WaveFrame Known Issues

This document lists known limitations and test areas for the v0.1 private beta. It does not invent confirmed bugs; unverified areas are marked as needs verification.

## Current Limitations

- Unsigned Windows beta: Windows security warnings are expected.
- Artifact/internal names may still say MixPulse.
- WaveFrame is Windows-first for v0.1.
- VST3 is experimental and needs DAW testing.
- Built-in video export is not implemented.
- OBS/manual capture is the current motion capture workflow.
- Installer and code signing are not implemented yet.
- macOS/AU are not enabled.
- NDI, Spout, Syphon, shader SDK, and virtual camera are not implemented.
- Cloud templates/accounts and telemetry are not implemented.
- Some visual modules/templates may remain placeholders.
- Logo/image import may be placeholder-only unless already safely implemented.

## Needs Verification

- Standalone launch across tester machines.
- VST3 scan/load in Ableton, FL Studio, Reaper, Bitwig, and other DAWs.
- Audio pass-through unchanged in DAWs.
- Output window close/reopen.
- Frame/current-frame behavior.
- HUD toggle.
- Fullscreen behavior.
- Module/template switching.
- Preset save/load/reset behavior.
- DAW remove/reload.
- OBS Window Capture workflow.
- Artifact contents after download/unzip.

## Blocking Issues

Treat these as release blockers:
- App will not launch.
- CI cannot build artifacts.
- `MixPulse-Windows-Beta` is missing.
- Plugin will not scan/load.
- Audio is muted or changed unexpectedly.
- Crash on open.
- Output window crash.
- `processBlock` changed.
