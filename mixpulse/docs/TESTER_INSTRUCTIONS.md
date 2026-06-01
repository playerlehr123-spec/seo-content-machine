# WaveFrame Tester Instructions

WaveFrame v0.1 is a private Windows-first beta candidate. Please do not share the build publicly.

Some artifact/plugin names may still say MixPulse. The product name is WaveFrame.

## Before Testing

1. Download `MixPulse-Windows-Beta` from the approved green GitHub Actions run.
2. Unzip the artifact.
3. Note the artifact/run number.
4. Read `KNOWN_ISSUES.md`.
5. Read `RELEASE_NOTES_v0.1.md`.
6. Use `QA_MATRIX.md` to record results.
7. Use `BETA_FEEDBACK_INTAKE.md` for reports.

## Standalone Test

1. Run the standalone EXE if present.
2. Confirm the UI opens.
3. Confirm meters move.
4. Open Output.
5. Toggle HUD.
6. Try fullscreen.
7. Try Frame/current-frame behavior.
8. Switch modules/templates.
9. Try preset reset/save/load if available.
10. Close the app cleanly.

## DAW Test

1. Copy `MixPulse.vst3` to `C:\Program Files\Common Files\VST3\` if present.
2. Rescan plugins in the DAW.
3. Load WaveFrame/MixPulse on an audio track.
4. Confirm audio pass-through is unchanged.
5. Confirm meters move.
6. Open the UI.
7. Open Output.
8. Remove/reload the plugin.

## OBS Test

1. Open the Output window.
2. Add an OBS Window Capture source.
3. Capture the Output window.
4. Resize the Output window.
5. Try fullscreen capture.
6. Record a short external test clip.

## Reporting Feedback

Use:
- `BETA_FEEDBACK_INTAKE.md`
- `FEEDBACK_TRIAGE_RULES.md`
- `BETA_BUG_REPORTING.md`
- `BETA_FEEDBACK_TRACKER.md`

Include artifact/run number, Windows version, DAW/version, module/template selected, output/OBS status, steps to reproduce, expected/actual behavior, and whether audio pass-through changed.
