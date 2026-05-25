# WaveFrame Visual Style Guide

WaveFrame visuals should feel dark, clean, neon, music-first, and ready for social capture. The current renderer pass focuses on polish inside the existing CPU/JUCE drawing paths.

## Shared Language
- Dark canvas backgrounds with soft framed stages.
- Cyan and green/yellow accent glows from Brand Layer colors where available.
- Subtle grid lines and safe-frame corner ticks.
- Readable artist/title/CTA text.
- Rounded panels, restrained outlines, and low-noise motion.
- Still PNG and OBS capture workflows only.

## Module Behavior
- Spectrum Bars: framed spectrum scope, subtle grid, center guide, rounded mirrored bars, no mastering claims.
- Logo Reactor: pulsing circular brand mark, glow rings, placement awareness, artist/title/label text, no image import.
- Type Pulse: repeated text texture, centered title block, CTA footer, opacity/scale pulse.
- Promo Card: release tag, cover placeholder, title hierarchy, CTA, label footer, audio-reactive spectrum strip.
- Particles: deterministic dot field with audio-reactive size, spread, brightness, and brand color blending.

## Future / TODO
- Editable module style presets.
- Template-specific typography controls.
- Logo/image import after a safe UI/file workflow exists.
- Video export, timeline, NDI, Spout/Syphon, virtual camera, and shader SDK remain out of scope.

## Manual Tests
- Switch through each visual module.
- Confirm no module renders blank.
- Confirm output window opens.
- Confirm Frame does not crash.
- Confirm meters still move.
- Confirm audio remains pass-through.
