# MixPulse Phase 1.5 / Phase 2 Foundation

## Implemented in this pass
- Analysis-only audio pass-through with extra output channel clearing safety
- Hardened analyzer guards for zero-channel/empty buffers
- Main editor UI refresh (header, meter panel, loudness panel, LUFS ref bar, preview placeholders)
- Meter dB scale markings at: 0, -3, -6, -9, -12, -24 (meter scale only)
- LUFS reference bar markers at: -14 ref and -23 ref only
- LUFS S/I placeholders displayed as `--.-`
- Visualizer mode enum expanded with placeholders, `V` cycles modes
- Spectrum bars renderer upgraded with mirrored center-out neon bars and subtle grid
- Screenshot export saves to `Documents/MixPulse/`

## Placeholder / TODO status
- LUFS S/I full implementation (BS.1770): TODO
- True Peak oversampled dBTP: TODO (currently sample peak placeholder)
- Additional mode renderers beyond placeholder visuals: TODO
- Auto BPM detection: TODO
- NDI/PDF/CSV/video export: NOT implemented

## Build
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

## Plugin install paths
- macOS VST3: `/Library/Audio/Plug-Ins/VST3/`
- macOS AU: `/Library/Audio/Plug-Ins/Components/`
- Windows VST3: `C:\Program Files\Common Files\VST3\`

## DAW test checklist
- Ableton VST3
- Ableton AU (macOS)
- FL Studio VST3
- Standalone target

## Build status in this environment
- Configure attempted, but full build was blocked because JUCE package config was unavailable in the container path used.
