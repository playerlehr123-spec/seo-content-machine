# WaveFrame Visual Modules

WaveFrame visual modules are audio-reactive creator surfaces for still PNG export and live OBS capture. They remain analysis-only: no audio effects, no video export engine, no external transport SDKs, and no file I/O in `processBlock`.

## Current Modules

| Module | Purpose | Status | Export Modes |
|---|---|---|---|
| Spectrum Bars | compact audio-reactive spectrum visual | active | PNG frame, live output/OBS |
| Logo Reactor | brand/logo pulse visual | v1 beta | PNG frame, live output/OBS |
| Type Pulse | audio-reactive artist/title text | v1 beta | PNG frame, live output/OBS |
| Promo Card | branded social release card | v1 beta | PNG frame, live output/OBS |
| Particles | deterministic audio-reactive dot field | v1 beta | PNG frame, live output/OBS |

## MVP Controls

- Spectrum Bars: intensity, motion amount, beat sync, colorize/mirror/bloom toggles.
- Logo Reactor: logo scale placeholder, glow amount, pulse amount, brand color, placement placeholder.
- Type Pulse: text size placeholder, pulse amount, repetition placeholder, color/glow/alignment placeholder.
- Promo Card: artist, title, label, CTA, status text, brand colors, aspect guide awareness.
- Particles: density placeholder, size placeholder, motion amount, audio amount, color mode placeholder.

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
