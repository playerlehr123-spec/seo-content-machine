# MixPulse Phase 1 MVP (Compile-Focused)

## Scope (Phase 1 only)
Implemented now:
- JUCE plugin targets: VST3, AU, Standalone
- Analysis-only audio pass-through (no audio processing changes)
- Peak/RMS meters with clip latch dots
- LUFS M/S/I placeholders
- True Peak placeholder (sample peak based)
- Integrated loudness reference bar with -14 and -23 markers
- Tap tempo + beat pulse trigger
- Detachable spectrum visualizer window
- Screenshot export of visualizer window

Deferred (TODO):
- Full ITU-R BS.1770 loudness gating
- Oversampled true peak detection (dBTP)
- Additional visualizer modes
- NDI/PDF/CSV export and advanced creator FX

## Build prerequisites
- CMake 3.22+
- C++17 compiler
- JUCE 7.x checkout or JUCE package with CMake config

## Exact build steps
### macOS
```bash
cd mixpulse
cmake -S . -B build -DJUCE_DIR=/absolute/path/to/JUCE
cmake --build build --config Release
```

### Windows (PowerShell)
```powershell
cd mixpulse
cmake -S . -B build -DJUCE_DIR=C:/path/to/JUCE
cmake --build build --config Release
```

## Notes for Ableton + FL Studio deployment
- Prefer VST3 for both Ableton and FL Studio on Windows/macOS.
- AU is available for macOS hosts that use AU.
- Keep plugin on audio/effect tracks (not MIDI-only tracks).
- Validate with buffer sizes 64/128/256/512 and sample rates 44.1/48/96 kHz.

## Known limitations in this phase
- LUFS S/I are placeholders and not standards-accurate yet.
- True Peak is sample-peak placeholder only.
- Meter visuals are MVP-level and will be refined in later phases.
