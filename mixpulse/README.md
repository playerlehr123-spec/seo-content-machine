# MixPulse Phase 1 MVP (Ableton/FL Optimized Baseline)

## File Tree
- CMakeLists.txt
- include/
- Source/

## Implemented (Phase 1)
- JUCE plugin targets (VST3/AU/Standalone)
- Ableton/FL-oriented plugin metadata (VST3 Fx|Analyzer, AU effect type)
- Audio pass-through with analysis-only process block
- Peak/RMS/sample-peak metering
- Atomic spectrum transfer from audio thread to GUI thread (lock-free snapshot)
- Tap tempo (4 taps), BPM display
- Beat pulse envelope
- Main editor window and Dark Neon theme
- Detachable visualizer window (always-on-top by default)
- Spectrum bars visualizer
- Screenshot export (S)
- Keyboard shortcuts (T/B/V/R/S/F/Esc)

## Scaffolded / TODO
- Full BS.1770 loudness
- Oversampled true peak
- Additional visualizer modes
- Export manager, preset manager, settings persistence

## Deployment Notes for Ableton + FL Studio
- Use VST3 format on Windows/macOS for both DAWs.
- Use AU on macOS where needed for Ableton.
- Keep plugin as insert FX; do not place on MIDI-only tracks.
- Recommended QA matrix:
  - Sample rates: 44.1/48/96 kHz
  - Buffer sizes: 64/128/256/512 samples
  - Session stress test: 8+ plugin instances

## Build (macOS)
```bash
cmake -S . -B build -DJUCE_DIR=/path/to/JUCE
cmake --build build --config Release
```

## Build (Windows)
```powershell
cmake -S . -B build -DJUCE_DIR=C:/JUCE
cmake --build build --config Release
```
