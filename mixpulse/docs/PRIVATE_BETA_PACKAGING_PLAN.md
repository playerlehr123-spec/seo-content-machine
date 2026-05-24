# WaveFrame Private Beta Packaging Plan

This is a planning document for the Windows private beta package. It does not require renaming MixPulse internals, plugin IDs, targets, or artifacts.

## Packaging Goal
Private beta testers should be able to:
1. Download the GitHub Actions artifact.
2. Unzip it.
3. Run the standalone app if included.
4. Install and rescan the VST3 if included.
5. Open the output window for OBS Window Capture.
6. Test Frame, HUD, fullscreen, modules, templates, and meters.
7. Report bugs with artifact/run number and environment details.

## Current Artifact Names
- Primary tester artifact: `MixPulse-Windows-Beta`.
- Debug fallback artifact: `MixPulse-Windows-Build-Folder`.
- Workflow name: `MixPulse Build`.

These names should remain stable for private beta unless a dedicated packaging compatibility pass changes them.

## Expected `MixPulse-Windows-Beta` Contents
- `README_INSTALL.txt`.
- Standalone EXE if produced by CI:
  - `MixPulse.exe`, `MixPulse_Standalone.exe`, or future `WaveFrame.exe`.
- VST3 bundle if produced by CI:
  - currently expected as `MixPulse.vst3`.
- No full build tree unless intentionally copied.
- No source checkout.
- No installer.
- No signing assets or private keys.
- No telemetry, account, cloud, or upload configuration.

## Expected `README_INSTALL.txt` Contents
The artifact README should be WaveFrame-first and include:
- Product name: WaveFrame.
- Internal/artifact naming note: MixPulse may appear in files, plugin names, and DAW scans.
- Unsigned Windows beta warning.
- Standalone launch instructions.
- VST3 install path:

```text
C:\Program Files\Common Files\VST3\
```

- DAW rescan hints for Ableton Live, FL Studio, Reaper, and other hosts.
- Audio pass-through safety expectation.
- Output window and OBS Window Capture workflow.
- Frame button is still-frame/PNG only.
- No built-in video export.
- No NDI, Spout, Syphon, shader SDK, virtual camera, macOS/AU, cloud upload, or telemetry.
- Where to report bugs and which details to include.

## Standalone App Expectations
- The standalone app should launch directly from the unzipped artifact when an EXE is present.
- Testers should not need an installer for private beta.
- The app may still be named MixPulse during private beta.
- UI should present WaveFrame as the product name.
- Windows SmartScreen warnings are expected because the build is unsigned.

## VST3 Bundle Expectations
- The VST3 may still appear as `MixPulse.vst3`.
- Testers should copy the whole `.vst3` bundle folder to the VST3 install path.
- DAWs may show MixPulse or WaveFrame depending on current plugin metadata and host cache behavior.
- VST3 remains experimental until the DAW test matrix has real pass/fail data.

## Docs Testers Need
The repo should keep these docs current:
- `mixpulse/docs/BETA_ARTIFACT_TEST_PLAN.md`
- `mixpulse/docs/RELEASE_CHECKLIST.md`
- `mixpulse/docs/DAW_SMOKE_TEST_CHECKLIST.md`
- `mixpulse/docs/BUG_REPORT_TEMPLATE.md`
- `mixpulse/docs/OBS_CAPTURE_GUIDE.md`
- `mixpulse/docs/STATE_AND_PRESETS.md`
- future/private beta docs when merged:
  - `mixpulse/docs/PRIVATE_BETA_GUIDE.md`
  - `mixpulse/docs/KNOWN_ISSUES.md`
  - `mixpulse/docs/BETA_BUG_REPORTING.md`
  - `mixpulse/docs/DAW_TEST_MATRIX.md`

## What Should Not Be Included
- Installer or auto-updater.
- Signing certificates or secrets.
- Source tree.
- Full build folder in the primary beta artifact.
- macOS/AU outputs.
- MP4/WebM/video export tools.
- NDI, Spout, Syphon, virtual camera, shader SDK, cloud upload, telemetry, or account-system files.

## Manual Install Flow
1. Download `MixPulse-Windows-Beta` from the latest successful relevant GitHub Actions run.
2. Unzip the artifact.
3. Read `README_INSTALL.txt`.
4. Run the standalone EXE if included.
5. For VST3, copy `MixPulse.vst3` to `C:\Program Files\Common Files\VST3\`.
6. Rescan plugins in the DAW.
7. Load on an audio track.
8. Confirm audio passes through unchanged.
9. Confirm meters move.
10. Open Output and capture it with OBS Window Capture if testing motion capture.

## Packaging Readiness Checklist
- Latest relevant CI run is green.
- `MixPulse-Windows-Beta` exists.
- `MixPulse-Windows-Build-Folder` exists.
- `README_INSTALL.txt` exists in the beta artifact.
- At least one of EXE or VST3 exists in the beta artifact.
- Artifact README explains WaveFrame/MixPulse naming.
- Artifact README states unsigned beta warning.
- Artifact README states no built-in video export.
- Artifact README states OBS capture is current motion workflow.
- Manual standalone smoke test completed.
- Manual VST3 scan/load test completed in at least one DAW before sharing the plugin more broadly.

## Future Packaging Improvements
- Add `WaveFrame_README.txt` alongside `README_INSTALL.txt`.
- Add a small `KNOWN_LIMITATIONS.txt` inside the beta artifact.
- Add a release tag or version stamp to artifact copy.
- Consider `WaveFrame-Windows-Beta` artifact rename after docs and tester instructions are updated.
- Consider installer/signing only after private beta stability is proven.
