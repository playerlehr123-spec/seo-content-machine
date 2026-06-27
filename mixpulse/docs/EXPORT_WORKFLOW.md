# WaveFrame Export Workflow

Status: still-frame only. v0.2 Sprints 5 and 6 clarify output capture, aspect guides, social export presets, current-frame PNG capture, and the boundary between still-frame and future video export.

## Implemented Now

- Frame button writes current-frame PNG stills from the output/editor visual state.
- Export preset selector exposes:
  - Current Window
  - Vertical Reel / Story 9:16, 1080x1920
  - Square Post 1:1, 1080x1080
  - Feed Portrait 4:5, 1080x1350
  - Wide / YouTube 16:9, 1920x1080
  - Wide / Stream Overlay 16:9, 1920x1080
- Built-in creator session presets can choose an export preset/aspect recommendation.
- Output window overlay shows OBS Capture Mode, selected aspect, output dimensions, and a safe-area guide.
- `Frame` status text says current-frame PNG/still image and reports future-only presets honestly.
- The export panel shows preset name, aspect/dimensions, use case, and workflow status.
- Frame failure states report cleanly when presets, folders, file streams, encoders, or render sizes are unavailable.
- Future video export presets remain disabled or clearly marked future/TODO.

## Current Workflow

1. Pick a built-in session preset or creator template.
2. Confirm the visual module and export preset.
3. Open Output for OBS capture if motion is needed.
4. Use Frame for PNG still output.
5. Use OBS Window Capture for motion recording/streaming.

## Template / Export Defaults

- Release Announcement: 9:16 or 4:5.
- Label Drop: 1:1.
- Stream Overlay: 16:9.
- Reel Visualizer: 9:16.
- Album Motion: 1:1.
- Minimal Meter: Current Window or 16:9.
- Logo Reactor: 9:16, 1:1, or 16:9 depending on selected session preset.
- Promo Card: 4:5 or 1:1.

## Not Implemented

- MP4/WebM export.
- Timeline or recorder.
- Background render engine.
- NDI / Spout / Syphon.
- Virtual camera.
- Cloud upload or social upload.

## Manual Tests

- Switch built-in session presets and confirm export preset changes safely.
- Switch export presets manually and confirm preview aspect guide remains coherent.
- Open, close, reopen, resize, and fullscreen the output window.
- Press Frame and confirm no crash.
- Press Frame before opening Output and confirm it opens/falls back safely.
- Press Frame repeatedly and confirm no crash.
- Switch each export preset and verify displayed dimensions.
- Confirm future/TODO export paths do not imply video export exists.


