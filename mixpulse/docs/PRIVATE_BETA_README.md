# WaveFrame v0.1 Private Beta README

WaveFrame is a Windows-first VST3 + standalone creator tool for turning audio into branded social visuals. Some artifact, plugin, and internal names may still say MixPulse during this beta.

Do not share this build publicly yet.

## What To Download
Download from the latest approved green GitHub Actions run:
- `MixPulse-Windows-Beta`

Optional/internal debug artifact:
- `MixPulse-Windows-Build-Folder`

## Run Standalone
1. Unzip `MixPulse-Windows-Beta`.
2. Read `README_INSTALL.txt`.
3. Run `MixPulse.exe`, `MixPulse_Standalone.exe`, or another included WaveFrame/MixPulse EXE if present.
4. Windows may show unsigned beta warnings.

## Install VST3
1. Locate `MixPulse.vst3` if present.
2. Copy the whole `.vst3` bundle to:

```text
C:\Program Files\Common Files\VST3\
```

3. Rescan plugins in your DAW.
4. Look for MixPulse or WaveFrame.

## Test OBS Output
1. Open the WaveFrame/MixPulse Output window.
2. In OBS, add Window Capture.
3. Select the Output window.
4. Resize/fullscreen if needed.
5. Record a short external test clip.

## Test First
- App launches.
- Audio pass-through is unchanged.
- Meters move.
- Output opens, closes, and reopens.
- Frame does not crash.
- HUD toggles.
- Module/template switching does not crash.
- VST3 scans and loads if present.
- DAW remove/reload does not crash.

## Known Limitations
- Unsigned Windows beta.
- Artifact/internal names may still say MixPulse.
- VST3 is experimental.
- No signed installer yet.
- No built-in video export.
- No NDI, Spout, Syphon, shader SDK, or virtual camera.
- No macOS/AU.
- No cloud upload or telemetry.

## Report Bugs
Use the GitHub bug report template.

Include artifact/run number, Windows version, DAW/version, standalone or VST3, module/template selected, Output/OBS status, steps to reproduce, expected vs actual behavior, and whether audio pass-through changed.
