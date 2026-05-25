# WaveFrame Tester Instructions

WaveFrame v0.1 is a private beta candidate. Some files may still say MixPulse.

## Before Testing
Record:
- Artifact/run number.
- Windows version.
- DAW/version if testing VST3.
- Audio interface.
- Standalone or VST3.

## Smoke Test
1. Download `MixPulse-Windows-Beta`.
2. Unzip it.
3. Run the standalone EXE if present.
4. Confirm audio pass-through is unchanged.
5. Confirm meters move.
6. Open Output.
7. Click Frame.
8. Toggle HUD.
9. Switch modules/templates.
10. Close and reopen Output.

## VST3 Test
1. Copy `MixPulse.vst3` to `C:\Program Files\Common Files\VST3\`.
2. Rescan the DAW.
3. Load on an audio track.
4. Confirm audio pass-through is unchanged.
5. Open/close UI.
6. Open Output.
7. Remove/reload plugin.

## OBS Test
1. Open Output.
2. Add OBS Window Capture.
3. Capture Output.
4. Resize/fullscreen Output.
5. Record a short external clip.

Report bugs with the GitHub template.
