# MixPulse Beta QA Checklist

## A) Build artifact checks
- macOS artifact downloaded.
- Windows artifact downloaded.
- README_INSTALL included.
- VST3 included.
- Standalone included if built.
- AU included on macOS if built.

## B) Standalone checks
- App launches.
- Window resizes.
- Tap tempo works.
- Beat Sync toggle works.
- Visualizer opens.
- Visualizer closes.
- Fullscreen works.
- Escape exits fullscreen.
- Screenshot saves to Documents/MixPulse.

## C) DAW checks
### Ableton
- VST3 scans.
- Plugin loads on audio track.
- Audio passes through unchanged.
- Meters move.
- Visualizer opens/closes.

### FL Studio
- VST3 scans.
- Plugin loads.
- Audio passes through unchanged.
- Meters move.

### Logic (macOS)
- AU validates if built.
- AU loads.
- Audio passes through unchanged.

## D) Stress checks
- 44.1kHz / 48kHz / 96kHz.
- Buffer 64 / 128 / 256 / 512.
- Mono track / stereo track.
- Multiple plugin instances.
- Close/reopen editor repeatedly.
- Remove plugin while visualizer is open.

## E) Known beta limitations
- Unsigned builds.
- Placeholder LUFS.
- Placeholder true peak.
- Placeholder non-spectrum visual modes.
- No installer.
- No NDI/PDF/CSV/video export.
