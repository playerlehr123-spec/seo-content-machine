# WaveFrame Beta Tester Message Template

Hey, thanks for trying WaveFrame.

WaveFrame is a Windows-first private beta for turning audio into branded visual content. Some files and artifacts may still say MixPulse because that is the current internal build name.

Please do not share this build publicly yet.

## What To Download

Download `MixPulse-Windows-Beta` from the approved green GitHub Actions run.

Optional/internal debugging artifact:
- `MixPulse-Windows-Build-Folder`

## What To Test First

1. Run the standalone app.
2. Confirm the UI opens and meters move.
3. Open the Output window.
4. Toggle HUD and fullscreen.
5. Try Frame/still capture.
6. Switch a few modules/templates.
7. If you use a DAW, try the VST3 and confirm audio passes through unchanged.
8. If you use OBS, capture the Output window with Window Capture.

## Known Limits

- Windows unsigned warning is expected.
- No built-in video export yet.
- OBS is the current motion capture workflow.
- VST3 testing is welcome but still experimental.
- Some templates/modules may still be placeholders.
- No NDI, Spout, Syphon, shader SDK, virtual camera, macOS/AU, cloud upload, or telemetry.

## What To Report

Please report:
- Crashes or freezes.
- Audio pass-through changes.
- DAW scan/load issues.
- Output/OBS problems.
- Frame/HUD problems.
- Module/template switching issues.
- Confusing UI or docs.
- Visual quality feedback.

Include the artifact/run number, Windows version, DAW/version if relevant, module/template selected, OBS/output status, repro steps, and screenshots/video/logs when useful.

Thank you. The goal of this beta is honest testing, not perfection theater.
