# WaveFrame Creator Templates (Beta)

Creator Templates are workflow presets that combine:
- visual module intent
- recommended export preset
- Brand Layer text defaults
- social/output use case

## Built-in templates

| Template | Best For | Aspect | Module | Status |
|---|---|---|---|---|
| Release Announcement | IG post / reel cover | 4:5 / 9:16 | Promo Card | beta |
| New Music Teaser | Reels/TikTok | 9:16 | Reel Visualizer | beta |
| Label Drop | Label social | 1:1 | Logo Reactor | beta |
| DJ Stream Overlay | OBS | 16:9 | Stream Overlay | beta |
| YouTube Thumbnail | YouTube | 16:9 | Promo Card | planned |
| Minimal Meter | Utility | Free | Meter Overlay | beta |

## Brand Layer connection
- Templates prefer: Artist Name, Track Title, Out Now, Label Name, WaveFrame.
- If user Brand Layer values are present, those values should be shown first.

## Export workflow
- Use **Export > Preset** to select Current/Reel/Square/Feed/Thumb.
- Use **Export Frame** to write PNG files to `Documents/WaveFrame/Exports/`.
- Filename format: `WaveFrame_<PresetName>_YYYY-MM-DD_HH-MM-SS.png`.

## OBS linkage
- Use WaveFrame Output aspect guides for framing.
- Use Export Frame for stills/covers.
- Use OBS recording for motion video capture.

## Interaction status
- The right control panel shows the selected template, use case, and recommended module.
- Invalid or empty template selections fall back to the safe default template.
- Template changes may update the visual module and preferred still export preset.
- Deeper template editing remains future/TODO.

## Current limitations
- PNG only (no built-in video export).
- No MP4/WebM, NDI, Spout, or Syphon.
- No transparent background export yet.
- No cloud upload; local files only.

## Future
- richer template styling and typography
- deeper module/template auto-wiring
- fixed-size export quality controls
- video export investigation (later)
