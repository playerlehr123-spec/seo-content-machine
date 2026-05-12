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
- NDI/PDF/CSV/video export

## Local build
### macOS
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

## CI workflow
Workflow: `.github/workflows/mixpulse-build.yml`
- Runs on: `pull_request`, `workflow_dispatch`
- Builds on: `macos-latest`, `windows-latest`
- Uses pinned JUCE ref `7.0.12`
- macOS builds: VST3 + AU + Standalone
- Windows builds: VST3 + Standalone
- Uploads artifacts:
  - `MixPulse-macOS-Release`
  - `MixPulse-Windows-Release`

## Expected output locations
Typical JUCE outputs:
- macOS VST3: `mixpulse/build/MixPulse_artefacts/Release/VST3/MixPulse.vst3`
- macOS AU: `mixpulse/build/MixPulse_artefacts/Release/AU/MixPulse.component`
- macOS Standalone: `mixpulse/build/MixPulse_artefacts/Release/Standalone/MixPulse.app`
- Windows VST3: `mixpulse/build/MixPulse_artefacts/Release/VST3/MixPulse.vst3`
- Windows Standalone: `mixpulse/build/MixPulse_artefacts/Release/Standalone/MixPulse.exe`

## Install paths
- macOS VST3: `/Library/Audio/Plug-Ins/VST3/`
- macOS AU: `/Library/Audio/Plug-Ins/Components/`
- Windows VST3: `C:\Program Files\Common Files\VST3\`

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

## Supersede note template
“This PR is superseded by PR #6, which contains the updated MixPulse JUCE project, CI workflow, artifact packaging, and corrected LUFS reference markers.”


## CI status (important)
- This local environment cannot directly verify the latest remote GitHub Actions result.
- Use the latest `MixPulse Build` run in Actions as source of truth for pass/fail and artifact availability.
- Artifacts expected on success:
  - `MixPulse-macOS-Release`
  - `MixPulse-Windows-Release`


## CI status update
- Current CI fix pass disables AU in CI (`MIXPULSE_BUILD_AU=OFF`) to reduce macOS build blockers and prioritize VST3/Standalone beta artifact output.
- Local AU support remains in CMake option handling for developer builds.
- If CI still fails, inspect the first failure line in configure/build logs and the debug output tree printed by workflow.


## CI scope (temporary)
- GitHub Actions currently proves **Standalone-only** beta builds on macOS and Windows.
- CI flags currently used:
  - `MIXPULSE_BUILD_VST3=OFF`
  - `MIXPULSE_BUILD_STANDALONE=ON`
  - `MIXPULSE_BUILD_AU=OFF`
- VST3 CI build validation is the next target after Standalone gate stability.

- Visual Rack concept: `mixpulse/docs/VISUAL_RACK_CONCEPT.md`
