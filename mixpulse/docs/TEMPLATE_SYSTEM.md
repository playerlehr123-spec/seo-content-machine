# WaveFrame Template System

## Purpose

Creator Template Presets map a social content use case to a visual module, aspect preset, brand text defaults, and implementation status.

## Presets

| Template | Module | Aspect | Use Case | Status |
|---|---|---|---|---|
| Minimal Meter | Spectrum Bars | Current / 16:9 | Meter utility still or OBS capture | Implemented |
| Logo Reactor | Logo Reactor | 1:1 Square | Artist or label identity post | Implemented |
| Release Announcement | Promo Card | 4:5 Feed | Release announcement still | Implemented |
| Label Drop | Promo Card | 1:1 Square | Label social still | Implemented |
| Stream Overlay | Spectrum Bars | 16:9 | OBS window capture | Placeholder |
| Reel Visualizer | Type Pulse | 9:16 Reel | Short-form social still | Implemented |
| Album Motion | Particles | 1:1 Square | Album motion concept still | Placeholder |
| Type Pulse | Type Pulse | 9:16 Reel | Lyric/title social still | Implemented |
| Particle Card | Particles | 4:5 Feed | Reactive artwork still | Placeholder |
| Spectrum Promo | Spectrum Bars | 16:9 | YouTube visualizer still | Implemented |

## Template Data

Each preset includes:

- display name
- short description
- preferred aspect ratio
- recommended visual module
- preferred still export preset
- brand text visibility default
- export use case
- status: implemented, placeholder, or future

## Current Behavior

- Selecting a template updates the selected visual module.
- Selecting a template updates CTA/release text and preferred still export preset.
- The right panel shows template purpose, module recommendation, status, and short description.
- The preview canvas shows selected module, selected template, brand text, aspect guide, safe-area guide, and still-frame status.

## Testing

Standalone:

- Select each template.
- Confirm the module selector follows the template recommendation.
- Confirm export preset/aspect changes.
- Confirm Frame produces a PNG or a clear status message.
- Confirm Output opens and module switching does not crash.

DAW:

- Confirm plugin opens/closes.
- Confirm audio passes through unchanged.
- Confirm module/template switching does not crash.

## Future/TODO

- Template thumbnails.
- Per-template layout controls.
- Editable template duplication.
- Timeline/video export.
- Cloud or marketplace workflows.
