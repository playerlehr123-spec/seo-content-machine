# WaveFrame Private Beta Guide

WaveFrame is a Windows-first private beta. Some artifacts, plugin names, and internals may still say MixPulse.

Current release candidate status: WaveFrame v0.1 private beta candidate.

## Current Install Path
- Download `MixPulse-Windows-Beta` from the latest approved green GitHub Actions run.
- Unzip the artifact.
- Run the standalone EXE if present.
- Copy `MixPulse.vst3` to `C:\Program Files\Common Files\VST3\` if testing VST3.
- Rescan plugins in the DAW.

## Current Distribution Model
- Private beta uses a ZIP-style GitHub Actions artifact.
- The build is unsigned, so Windows warnings are expected.
- Installer and code signing are future work.

## Not Included Yet
- Built-in video export.
- Installer.
- Code signing.
- Auto-update.
- NDI, Spout, Syphon, shader SDK, virtual camera.
- macOS/AU.
- Cloud upload or telemetry.

## Tester Notes
- Confirm audio passes through unchanged.
- Confirm meters move.
- Test Output, Frame, HUD, fullscreen, module switching, and OBS capture.
- Report artifact/run number, Windows version, DAW version, audio interface, and reproduction steps.
- Start with `mixpulse/docs/PRIVATE_BETA_README.md`.
- Use `mixpulse/docs/RC_CHECKLIST_v0.1.md` before sharing a candidate.
- Read `mixpulse/docs/RELEASE_NOTES_v0.1.md` for current included/not-included scope.
- Track known limitations in `mixpulse/docs/KNOWN_ISSUES.md`.
- Use `mixpulse/docs/BETA_BUG_REPORTING.md` and the GitHub bug template for reports.
