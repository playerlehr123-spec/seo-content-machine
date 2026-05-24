# WaveFrame Export Workflow

WaveFrame export is currently still-frame focused. The supported workflow is live output plus OBS capture for motion, and PNG frame export for still social content.

## Implemented
- `Output` opens the visual output window.
- `Frame` saves a still PNG from the current output or selected fixed-size preset.
- Aspect presets:
  - 9:16, 1080x1920.
  - 1:1, 1080x1080.
  - 4:5, 1080x1350.
  - 16:9, 1920x1080.
- Output overlay shows selected module, aspect guide, and still-PNG-only status.
- OBS Window Capture is the recommended current recording/streaming path.

## Placeholder
- Some future/social presets may be listed but disabled.
- Template-specific export recommendations are still evolving.

## Future / TODO
- MP4/WebM export.
- Background rendering.
- Timeline or clip recorder.
- NDI, Spout, Syphon, or virtual camera.
- Cloud upload or social posting.

## Manual Test Checklist
- Select each aspect preset.
- Confirm the preview/output guide changes.
- Open the output window.
- Save a still PNG.
- Confirm the PNG lands under `Documents/WaveFrame/Exports`.
- Confirm OBS can capture the output window.
- Confirm video export is not presented as implemented.
