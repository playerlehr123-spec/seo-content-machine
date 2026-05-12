# MixPulse

MixPulse is a mini meter and audio-reactive creator visual engine for producers, DJs, streamers, and artists.

Current build status: **private beta / early build**.

# MixPulse Phase 1.5 / Phase 2 Foundation

## Implemented
- Analysis-only pass-through processing (no gain/effects; extra output channels cleared only for safety)
- Peak/RMS meter system with dB ticks at `0, -3, -6, -9, -12, -24`
- LUFS panel with placeholder behavior (`LUFS S/I = --.-`)
- Integrated LUFS ref bar with neutral refs: `-6, -12, -14, -23`
- Spectrum Bars visualizer (primary implemented mode)
- Tap tempo + beat sync skeleton
- Screenshot export to `Documents/MixPulse/`

## Placeholder / not implemented
- Full BS.1770 LUFS pipeline
- Oversampled true peak
- Auto BPM detection
- Non-spectrum visualizer modes (placeholders)
- Video import/export (MP4/WebM)
- NDI/Spout/Syphon transport
- Installer packaging / code signing

## Local build
### macOS (local-only, CI deferred)
```bash
cd mixpulse
cmake -S . -B build -DJUCE_DIR=/absolute/path/to/JUCE
cmake --build build --config Release
```

### Windows
```powershell
cd mixpulse
cmake -S . -B build -DJUCE_DIR=C:/path/to/JUCE
cmake --build build --config Release
```

## Current CI status
- Windows-only CI is active.
- The immediate goal is to produce a testable standalone EXE and/or VST3 artifact from CI.
- macOS/AU are deferred; Windows artifact stability is prioritized first.
- Full build folder artifact is uploaded for debugging.
- Search downloaded artifacts for:
  - `MixPulse.exe`
  - `MixPulse_Standalone.exe`
  - `MixPulse.vst3`

## CI workflow
Workflow: `.github/workflows/mixpulse-build.yml`
- Runs on: `pull_request`, `workflow_dispatch`
- Builds on: `windows-latest` (temporary standalone-first scope)
- Uses pinned JUCE ref `7.0.11` (with `master` fallback)
- Windows builds: Standalone + VST3 attempt (`MIXPULSE_BUILD_VST3=ON`, `MIXPULSE_BUILD_STANDALONE=ON`, `MIXPULSE_BUILD_AU=OFF`)
- Uploads artifacts:
  - `MixPulse-Windows-Beta`
  - `MixPulse-Windows-Build-Folder`

## Expected output locations
Typical JUCE outputs:
- Windows Standalone: `mixpulse/build/MixPulse_artefacts/Release/Standalone/MixPulse.exe` (or `MixPulse_Standalone.exe` depending on generator/output layout)

## Install paths
- Windows standalone install is not automatic in CI artifacts; run the EXE directly from the extracted artifact output folder.

## QA checklist
See `mixpulse/docs/QA_CHECKLIST.md`.

## Known limitations
- LUFS refs are technical references only (not targets/recommendations).
- LUFS M is placeholder approximation.
- LUFS S/I are unavailable placeholders.
- True Peak is sample-peak placeholder.
- Builds are unsigned.


## Failure fix note
- CI failure fixed by updating the JUCE pin to `7.0.11` and normalizing Windows `JUCE_DIR` to use forward slashes (`${{ github.workspace }}/_deps/JUCE`) to avoid path parsing/configure errors.


## If CI fails
- First likely failure fixed in this pass: JUCE ref checkout/path robustness in workflow.
- Workflow now falls back to JUCE `master` if tag `7.0.11` is unavailable in the runner checkout path.
- Packaging now discovers artifacts dynamically instead of relying only on one hardcoded output path.


## Beta tester docs
- Install guide: `mixpulse/docs/BETA_INSTALL.md`
- QA checklist: `mixpulse/docs/QA_CHECKLIST.md`
- Roadmap: `mixpulse/docs/ROADMAP.md`

## CI status (important)
- This local environment cannot directly verify the latest remote GitHub Actions result.
- Use the latest `MixPulse Build` run in Actions as source of truth for pass/fail and artifact availability.
- Artifacts expected on success:
  - `MixPulse-Windows-Beta`
  - `MixPulse-Windows-Build-Folder`

## CI scope (temporary)
- GitHub Actions currently runs on **Windows only**.
- CI flags currently used:
  - `MIXPULSE_BUILD_VST3=ON`
  - `MIXPULSE_BUILD_STANDALONE=ON`
  - `MIXPULSE_BUILD_AU=OFF`
- Standalone and VST3 artifacts are both attempted; either is testable output in beta packaging.

- Visual Rack concept: `mixpulse/docs/VISUAL_RACK_CONCEPT.md`

## CI note
Current CI is intentionally **Windows-first**. Standalone remains the gating artifact, while VST3 is re-enabled experimentally; macOS will be restored later.


## Pre-live checklist
- See `mixpulse/docs/PRE_LIVE_CHECKLIST.md`.
- Visual Rack concept: `mixpulse/docs/VISUAL_RACK_CONCEPT.md`.


## Current beta focus
- Analysis-only pass-through
- Compact meter / HUD direction
- Peak/RMS meter
- Placeholder LUFS panel
- Spectrum visualizer
- Visual Rack scaffold
- Creator Output Window
- Export Frame screenshot
- Windows-first beta build

## Future direction
- VST3/macOS expansion after standalone artifact stability
- Logo/image layer
- Export presets
- Video capture/export investigation
- Spout/Syphon/NDI investigation
- True LUFS / true peak implementation

## Beta honesty
- Not mastering-grade yet
- Not a video timeline editor yet
- Not a finished public release yet
