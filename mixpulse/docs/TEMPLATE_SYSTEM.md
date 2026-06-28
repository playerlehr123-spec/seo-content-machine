# WaveFrame Template System

Status: v0.2 Sprint 3 improves metadata, template/module mapping, status labels, and preview communication. This is still a beta creator workflow, not a full template editor.

## Implemented Now

- Built-in template presets live in `CreatorTemplate`.
- The template picker includes 10 starter presets.
- Each preset stores display name, description, use case, recommended module, preferred export preset, CTA text, release/status text, and implementation status.
- Selecting a template safely updates the recommended visual module, CTA text, release text, and export preset.
- Template selection keeps Brand Text editable and shows which brand fields matter for the selected workflow.
- Invalid template selection falls back to Minimal Meter.
- v0.2 Sprint 4 built-in session presets can choose template presets as part of a larger creator session default.

## Starter Templates

| Template | Use case | Recommended module | Preferred aspect | Status |
| --- | --- | --- | --- | --- |
| Minimal Meter | Producer utility / quick level check | Spectrum Bars | Current | Implemented |
| Logo Reactor | Artist or label identity post | Logo Reactor | 1:1 | Implemented |
| Release Announcement | IG feed / reel cover | Promo Card | 4:5 | Implemented |
| Label Drop | Label social post | Promo Card | 1:1 | Implemented |
| Stream Overlay | OBS / livestream capture | Spectrum Bars | 16:9 | Placeholder |
| Reel Visualizer | Reels / TikTok / Shorts | Particles | 9:16 | Placeholder |
| Album Motion | Album art motion concept | Type Pulse | 1:1 | Placeholder |
| Type Pulse | Lyric/title teaser | Type Pulse | 9:16 | Implemented |
| Particle Card | Visualizer card / teaser | Particles | 1:1 | Placeholder |
| Spectrum Promo | Classic visualizer promo | Spectrum Bars | 16:9 | Implemented |

## Current Limitations

- Template text editing is still mostly Brand Layer driven.
- Full per-template field visibility/locking is not implemented; fields remain visible to avoid surprising state changes.
- Logo/image import remains future/TODO unless already present through local preset state.
- No social upload, marketplace, cloud templates, timeline, or video export.

## Manual Tests

- Switch through every template without crashing.
- Confirm the module selector follows the template recommendation.
- Confirm selected template info updates in the right panel.
- Confirm the preview canvas shows template, module, brand text, aspect guide, and still-frame messaging.
- Confirm editable Brand Text remains coherent after template switching.

