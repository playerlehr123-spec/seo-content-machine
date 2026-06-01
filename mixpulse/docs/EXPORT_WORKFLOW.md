# WaveFrame Export Workflow

Status: still-frame only. v0.2 Sprint 5 clarifies how output capture, aspect guides, and current-frame PNG status relate to OBS workflows.

## Implemented Now

- Frame button writes PNG stills.
- Export preset selector exposes:
  - Current Window
  - Reel / TikTok 9:16
  - Square Post 1:1
  - Feed Post 4:5
  - YouTube Thumbnail 16:9
  - Stream Overlay 16:9
- Built-in creator session presets can choose an export preset/aspect recommendation.
- Output window overlay shows OBS Capture Mode, selected aspect, output dimensions, and a safe-area guide.
- `Frame` status text says current-frame PNG/still image and reports future-only presets honestly.
- Future video export presets remain disabled or clearly marked future/TODO.

## Current Workflow

1. Pick a built-in session preset or creator template.
2. Confirm the visual module and export preset.
3. Open Output for OBS capture if motion is needed.
4. Use Frame for PNG still output.
5. Use OBS Window Capture for motion recording/streaming.

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
- Confirm future/TODO export paths do not imply video export exists.
