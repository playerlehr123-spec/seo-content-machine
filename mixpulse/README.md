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
