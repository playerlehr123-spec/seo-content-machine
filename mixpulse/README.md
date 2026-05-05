# MixPulse Phase 1 MVP

## File Tree

- CMakeLists.txt
- include/
- Source/

## Implemented (Phase 1)
- JUCE plugin targets (VST3/AU/Standalone)
- Audio pass-through with analysis-only process block
- Peak/RMS/sample-peak metering
- Tap tempo (4 taps), BPM display
- Beat pulse envelope
- Main editor window and Dark Neon theme
- Detachable visualizer window
- Spectrum bars visualizer
- Screenshot export (S)
- Keyboard shortcuts (T/B/V/R/S/F/Esc)

## Scaffolded / TODO
- Full BS.1770 loudness
- Oversampled true peak
- Additional visualizer modes
- Export manager, preset manager, settings persistence

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
