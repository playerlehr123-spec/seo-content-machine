# WaveFrame Private Beta Guide

WaveFrame is a Windows-first private beta. Some artifacts, plugin names, and internals may still say MixPulse.

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
- Use `mixpulse/docs/BUG_BASH_PLAN.md` to run a focused QA session.
- Track pass/fail status in `mixpulse/docs/QA_MATRIX.md` and `mixpulse/docs/DAW_TEST_MATRIX.md`.
- Use `mixpulse/docs/BLOCKER_CRITERIA.md` to decide whether a bug blocks private beta.
- Send testers `mixpulse/docs/TESTER_INSTRUCTIONS.md` before the session.
