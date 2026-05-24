# WaveFrame Private Beta Guide

WaveFrame is a Windows-first VST3 and standalone creator tool for turning audio into branded social visuals. During this beta, some files, artifacts, and plugin internals still use the MixPulse codename. The user-facing product name is WaveFrame.

## What This Beta Includes
- Windows GitHub Actions artifacts.
- Standalone app build when the artifact includes an EXE.
- Experimental VST3 build when the artifact includes a `.vst3` bundle.
- Audio analysis and pass-through behavior.
- Output window for OBS Window Capture.
- Still-frame PNG workflow where available.
- Visual modules, creator templates, brand placeholders, HUD, meters, and export presets.

## What This Beta Does Not Include
- No built-in video export.
- No NDI, Spout, Syphon, virtual camera, or shader SDK.
- No macOS/AU build.
- No installer, signing, auto-update, cloud upload, account system, or telemetry.
- No final logo/image import workflow unless explicitly present in the build.
- Not public release ready.

## Download The Artifact
1. Open the GitHub Actions page for `playerlehr123-spec/seo-content-machine`.
2. Open the latest successful `MixPulse Build` run for the branch or PR being tested.
3. Download `MixPulse-Windows-Beta`.
4. Keep `MixPulse-Windows-Build-Folder` available only if a developer asks for debug details.
5. Unzip `MixPulse-Windows-Beta` into a normal folder such as Downloads or Desktop.

If older runs show a red X, ignore them unless they are the latest run for the branch being tested.

## Run The Standalone App
1. Open the unzipped artifact.
2. Locate `MixPulse.exe` or another MixPulse/WaveFrame standalone EXE if present.
3. Run the EXE.
4. If Windows SmartScreen or unsigned app warnings appear, choose the manual continue path only if you trust this private beta artifact.
5. Confirm the UI launches, meters move with input/audio, Output opens, HUD toggles, Frame does not crash, and the app closes cleanly.

## Install And Test VST3
1. Locate `MixPulse.vst3` if present.
2. Copy it to:

```text
C:\Program Files\Common Files\VST3\
```

3. Restart or rescan plugins in the DAW.
4. Load the plugin on an audio track.
5. Confirm audio passes through unchanged and meters move.
6. Open/close the UI, open Output, test HUD and Frame, then remove/reload the plugin.

The VST3 is experimental. Test Ableton Live, FL Studio, Reaper, and Bitwig separately when available.

## OBS Capture Workflow
1. Open WaveFrame standalone or the plugin UI.
2. Click Output.
3. In OBS, add a Window Capture source.
4. Select the WaveFrame/MixPulse output window.
5. Resize or fullscreen the output window as needed.
6. Record or stream from OBS.

Current motion capture is external through OBS. WaveFrame does not include built-in video export in this beta.

## Naming Mismatch
- Product name: WaveFrame.
- Internal codename, target, binary, plugin, and artifact names may still say MixPulse.

Do not treat MixPulse naming as a release branding decision. It is preserved for beta build stability and DAW/plugin compatibility.

## What To Send Back
- Artifact name and run number.
- Standalone or VST3.
- DAW name/version if applicable.
- Windows version.
- Audio interface, sample rate, and buffer size if relevant.
- Module/template selected.
- Whether Output, OBS, Frame, HUD, fullscreen, or preset reset were involved.
- Clear steps to reproduce and whether audio pass-through changed.
