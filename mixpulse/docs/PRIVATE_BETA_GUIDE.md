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

## Feedback Intake
- Start with `PRIVATE_BETA_README.md` for tester-facing instructions.
- Use `BETA_FEEDBACK_INTAKE.md` to collect structured feedback.
- Use `FEEDBACK_TRIAGE_RULES.md` to classify severity and release impact.
- Track reports in `BETA_FEEDBACK_TRACKER.md` or GitHub issues.
- Use `BETA_BUG_REPORTING.md` for required bug report details.
- Use `FIX_SPRINT_WORKFLOW.md` when selecting the top issues for a focused fix PR.
- Use `BETA_TESTER_MESSAGE_TEMPLATE.md` when inviting private testers.
