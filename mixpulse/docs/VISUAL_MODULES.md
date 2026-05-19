# WaveFrame Visual Modules

WaveFrame visual modules are audio-reactive creator surfaces for still PNG export and live OBS capture. They remain analysis-only: no audio effects, no video export engine, no external transport SDKs, and no file I/O in `processBlock`.

## Current Modules

| Module | Purpose | Status | Export Modes |
|---|---|---|---|
| Spectrum Bars | compact audio-reactive spectrum visual | active | PNG frame, live output/OBS |
| Logo Reactor | brand/logo pulse visual | v1 renderer | PNG frame, live output/OBS |
| Type Pulse | audio-reactive artist/title text | v1 renderer | PNG frame, live output/OBS |
| Promo Card | branded social release card | v1 renderer | PNG frame, live output/OBS |
| Particles | deterministic audio-reactive dot field | v1 renderer | PNG frame, live output/OBS |

## MVP Controls

- Spectrum Bars: intensity, motion amount, beat sync, colorize/mirror/bloom toggles, rounded bar readability.
- Logo Reactor: brand mark scale, glow, opacity pulse, brand color, placement placeholder, artist/title/label text.
- Type Pulse: repeated text field, centered title, CTA, color/glow pulse.
- Promo Card: artist, title, label, CTA, status text, brand colors, aspect guide awareness, reactive spectrum strip.
- Particles: deterministic dot grid, size/brightness/spread reaction, motion amount, brand color blending.

## Batch 2 Polish Status

- Logo Reactor now renders a cleaner beat-reactive brand mark with brand colors, placement awareness, glow rings, and artist/title text.
- Type Pulse now layers repeated artist/title/CTA text behind a pulsing centered title.
- Promo Card now has a more complete release-card composition with a cover placeholder, release tag, CTA, label footer, and reactive spectrum strip.
- Particles now uses a denser deterministic field with audio-reactive spread, brightness, and size.
- Spectrum Bars now has a clearer scope frame, center guide, and rounded bars while preserving existing meter/reference behavior elsewhere.

## Brand Kit + Templates

- Visual modules read Brand Kit text, color, logo visibility, text overlay visibility, placement, scale, and opacity where supported.
- Creator templates recommend visual modules and still-frame aspect presets.
- Template metadata distinguishes implemented modules from placeholder/future workflows.

## Future Modules

| Module | Purpose | Status |
|---|---|---|
| Pixelator | image/logo pixel treatment | future/TODO |
| GeoSync | geometric modulation compositions | future/TODO |
| Halftone | print-inspired dot/line visual | future/TODO |
| Album Motion | cover-art motion concept | future/TODO |
| Stream Overlay | OBS-friendly live layout | future/TODO |
| Reel Maker | short-form template workflow | future/TODO |

## Known Limits

- No MP4/WebM export.
- No timeline.
- No NDI, Spout, or Syphon.
- No shader SDK.
- No custom font loading.
- No risky logo/image import in v1.
