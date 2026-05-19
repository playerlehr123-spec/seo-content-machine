# WaveFrame Export Workflow

## Current Status

WaveFrame export is still-frame only.

- Frame button captures a PNG.
- Fixed social aspect presets render still PNGs.
- Output window remains the live capture target for OBS.
- Video export is future/TODO only.

## Still Presets

| Preset | Dimensions | Use |
|---|---:|---|
| 9:16 Reel / TikTok / Shorts | 1080x1920 | vertical social still |
| 1:1 Square Post | 1080x1080 | square post or cover |
| 4:5 Feed Post | 1080x1350 | feed announcement |
| 16:9 YouTube / Visualizer | 1920x1080 | YouTube thumbnail or visualizer still |
| 16:9 Stream Overlay | 1920x1080 | OBS overlay still/reference |

## Template Integration

Templates recommend an export preset. Selecting a template can update the export preset, visual module, CTA text, release status, and text/logo overlay defaults.

## OBS Workaround

For motion capture today:

- Open the Output window.
- Capture that window in OBS.
- Use WaveFrame as the audio-reactive visual source.

## Not Implemented

- MP4/WebM export.
- Encoder or recorder.
- Timeline.
- Background render queue.
- Cloud upload.
- NDI, Spout, or Syphon.

## Manual Test Checklist

- Output opens.
- Frame does not crash.
- Current Window PNG exports.
- 9:16, 1:1, 4:5, and 16:9 presets export or clearly report status.
- Export filename uses WaveFrame naming.
- App closes cleanly after export.
