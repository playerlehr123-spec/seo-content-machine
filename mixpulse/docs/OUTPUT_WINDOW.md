# WaveFrame Output Window

The WaveFrame output window is the capture surface for live visuals, creator templates, and still-frame PNG export. It is intentionally separate from the plugin/editor controls so OBS can capture a clean visual target.

## Implemented
- Separate resizable output window.
- Always-on-top behavior for DAW and OBS workflows.
- Fullscreen toggle.
- Close/reopen behavior through the `Output` button.
- Lightweight capture overlay with:
  - WaveFrame output label.
  - OBS Window Capture readiness.
  - selected visual module.
  - selected aspect/export guide.
  - still PNG only status.
- Existing visual modules continue to render in the output window.

## Current Aspect Presets
| Preset | Size | Use |
| --- | --- | --- |
| 9:16 | 1080x1920 | Reels, TikTok, Shorts |
| 1:1 | 1080x1080 | Square social posts |
| 4:5 | 1080x1350 | Feed posts |
| 16:9 | 1920x1080 | YouTube, streams, visualizers |

## Frame Capture
- `Frame` saves the current visual output as a still PNG.
- Fixed-size presets render through the visual renderer.
- Current-window capture uses the output component size.
- Video export is not implemented.

## Manual Test Checklist
- Open output.
- Close output.
- Reopen output.
- Resize output.
- Toggle fullscreen.
- Capture in OBS Window Capture.
- Save a still PNG with `Frame`.
- Switch modules and confirm no crash.

## Future / TODO
- Hide/show capture overlay toggle.
- Transparent-background capture options.
- Output window safe-area style controls.
- Video export remains future only.
