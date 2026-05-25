# WaveFrame Creator Templates (Beta)

Creator Templates are workflow presets that combine:
- visual module intent
- recommended export preset
- Brand Layer text defaults
- social/output use case

## Built-in templates

| Template | Best For | Aspect | Module | Status |
|---|---|---|---|---|
| Minimal Meter | Producer utility / quick level check | Current | Spectrum Bars | implemented |
| Logo Reactor | Artist or label identity post | 1:1 | Logo Reactor | implemented |
| Release Announcement | IG feed / reel cover | 4:5 | Promo Card | implemented |
| Label Drop | Label social post | 1:1 | Promo Card | implemented |
| Stream Overlay | OBS / livestream capture | 16:9 | Spectrum Bars | placeholder |
| Reel Visualizer | Reels/TikTok/Shorts | 9:16 | Particles | placeholder |
| Album Motion | Album art motion concept | 1:1 | Type Pulse | placeholder |
| Type Pulse | Lyric/title teaser | 9:16 | Type Pulse | implemented |
| Particle Card | Visualizer card / teaser | 1:1 | Particles | placeholder |
| Spectrum Promo | Classic visualizer promo | 16:9 | Spectrum Bars | implemented |

## v0.2 Sprint 3 updates

- Template metadata now includes descriptions, use cases, module recommendations, export preset preference, CTA/status defaults, and status labels.
- The right-side Templates panel shows the selected template purpose, recommended module, status, and aspect label.
- The preview canvas shows template/module context and Brand Layer text so testers can see the current creator state.
- Invalid template selections fall back to Minimal Meter.

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

## Current limitations
- PNG only (no built-in video export).
- No MP4/WebM, NDI, Spout, or Syphon.
- No transparent background export yet.
- No cloud upload; local files only.

## Future
- richer template styling and typography
- deeper field editing controls
- fixed-size export quality controls
- video export investigation (later)
