# MixPulse Beta QA Checklist

## Standalone
- App opens.
- UI draws.
- Tap tempo changes BPM.
- Visualizer opens.
- Fullscreen works.
- Screenshot saves to Documents/MixPulse.
- Closing visualizer does not crash.
- Reopening visualizer works.

## DAW
- VST3 scans in Ableton.
- VST3 scans in FL Studio.
- AU scans in Ableton/Logic on macOS if built.
- Plugin loads on audio track.
- Audio passes through unchanged.
- Meters move.
- Clip dots latch/reset.
- Visualizer opens/closes.
- Multiple plugin instances do not crash.

## Stress
- 44.1kHz / 48kHz / 96kHz.
- 64 / 128 / 256 / 512 buffers.
- Mono and stereo tracks.
- Open/close editor repeatedly.
- Remove plugin while visualizer is open.

## Known beta limitations
- LUFS M is placeholder approximation.
- LUFS S/I are placeholders.
- True Peak is sample peak placeholder.
- Visual modes beyond Spectrum are placeholders.
- Builds are unsigned.
- No NDI/PDF/CSV/video export.
