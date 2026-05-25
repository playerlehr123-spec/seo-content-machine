# WaveFrame Tester Instructions

Thank you for testing WaveFrame. Some files and plugins may still say MixPulse. That is expected during private beta.

## Before You Start
Record:
- GitHub Actions run number.
- Artifact name.
- Commit SHA if available.
- Windows version.
- Audio interface.
- DAW name/version if testing VST3.

## Download
1. Open the approved GitHub Actions run.
2. Download `MixPulse-Windows-Beta`.
3. Unzip the artifact.
4. Read `README_INSTALL.txt`.

## Standalone Test
1. Run the standalone EXE if present.
2. Confirm the app launches.
3. Confirm meters move with input/audio.
4. Open Output.
5. Toggle HUD.
6. Click Frame.
7. Switch a few modules/templates.
8. Close and reopen Output.
9. Close the app.

## VST3 Test
1. Copy `MixPulse.vst3` to:

```text
C:\Program Files\Common Files\VST3\
```

2. Rescan plugins in your DAW.
3. Load the plugin on an audio track.
4. Play known audio through the track.
5. Confirm audio pass-through is unchanged.
6. Confirm meters move.
7. Open and close the plugin UI.
8. Open Output.
9. Test Frame and HUD.
10. Remove and reload the plugin.

## OBS Test
1. Open the WaveFrame/MixPulse Output window.
2. In OBS, add Window Capture.
3. Select the Output window.
4. Resize the output.
5. Try fullscreen if available.
6. Record a short clip externally in OBS.

## Filing Bugs
Use the GitHub bug template and include:
- QA level.
- Severity.
- Artifact/run number.
- Standalone or VST3.
- DAW name/version.
- Module/template selected.
- Output window open?
- OBS involved?
- Repro rate.
- Whether audio pass-through changed.
- Screenshot, video, or log if available.

## Audio Safety
Report immediately as P0 if audio becomes louder, quieter, muted, clipped, delayed, distorted, filtered, compressed, widened, or otherwise changed.
