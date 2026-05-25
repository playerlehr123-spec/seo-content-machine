# WaveFrame Social Content Modules

## 1) Promo Card
- Purpose: release announcement stills/reels
- Controls: artist, title, label, CTA, logo, colors, aspect
- Status: v1 renderer with release tag, cover placeholder, artist/title/CTA text, label footer, and audio-reactive accent/spectrum strip

## 2) Logo Reactor
- Purpose: audio-reactive logo visual
- Controls: logo, glow, scale, beat pulse, background
- Status: v1 renderer using Brand Layer text, color, opacity, scale, and placement placeholders; image import is TODO

## 3) Particles
- Purpose: particle-inspired audio motion
- Controls: density, size, frequency, motion, audio amount
- Status: v1 renderer with deterministic dot field, audio-reactive brightness, size, and spread; no heavy physics or shader SDK

## 4) Type Pulse
- Purpose: audio-reactive text pattern
- Controls: text, font size, repetition, color, pulse amount
- Status: v1 renderer using repeated artist/title/CTA text and a pulsing centered title; editable text UI is TODO

## 5) Pixelator
- Purpose: image/logo pixel treatment
- Controls: image, pixel size, contrast, hue, motion amount
- Status: planned

## 6) GeoSync
- Purpose: geometric compositions
- Controls: grid, shapes, spacing, symmetry, audio modulation
- Status: planned

## 7) Stream Overlay
- Purpose: OBS-friendly live overlay
- Controls: meter, logo, spectrum, scene, transparency (future)
- Status: planned

## 8) Album Motion
- Purpose: album-art motion loop
- Controls: image, motion, spectrum, text, export
- Status: planned

## Known limitations
- PNG still/frame export only.
- OBS remains the current workaround for motion capture.
- No built-in video export, upload, timeline, NDI, Spout, Syphon, or shader SDK.

## v0.2 Sprint 3 Template Mapping

| Template | Recommended module | Status |
| --- | --- | --- |
| Minimal Meter | Spectrum Bars | implemented |
| Logo Reactor | Logo Reactor | implemented |
| Release Announcement | Promo Card | implemented |
| Label Drop | Promo Card | implemented |
| Stream Overlay | Spectrum Bars | placeholder |
| Reel Visualizer | Particles | placeholder |
| Album Motion | Type Pulse | placeholder |
| Type Pulse | Type Pulse | implemented |
| Particle Card | Particles | placeholder |
| Spectrum Promo | Spectrum Bars | implemented |
