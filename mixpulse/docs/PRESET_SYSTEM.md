# WaveFrame Preset System

Status: v0.2 Sprint 7 keeps the Sprint 4 preset safety work and adds editable Brand Text fields that save/load through the local Brand preset path.

## Implemented Now

- Built-in session preset selector in the editor Controls section.
- Built-in session presets set safe starter Brand Text values.
- Built-in session presets can recommend a creator template, visual module, and export preset/aspect.
- Local Brand preset save/load under `Documents/WaveFrame/Presets/WaveFrame_UserPreset.json`.
- Reset restores a known default creator session.
- Brand preset load tolerates missing fields and malformed JSON safely.
- Brand numeric fields are clamped before save/load use:
  - `logoScale`: `0.1` to `3.0`
  - `logoOpacity`: `0.0` to `1.0`
- Visual defaults are clamped in the UI path:
  - intensity: `0.0` to `2.0`
  - motion amount: `0.0` to `1.0`
  - bloom/glow amount: `0.0` to `1.0`

## Built-in Session Presets

| Preset | Template | Module | Export/aspect | Status |
| --- | --- | --- | --- | --- |
| Minimal Meter - Dark Cyan | Minimal Meter | Spectrum Bars | Current | implemented |
| Logo Reactor - Neon Green | Logo Reactor | Logo Reactor | 1:1 | implemented |
| Release Announcement - Vertical | Release Announcement | Promo Card | 4:5 | implemented |
| Label Drop - Square | Label Drop | Promo Card | 1:1 | implemented |
| Stream Overlay - Wide | Stream Overlay | Spectrum Bars | 16:9 | placeholder |
| Type Pulse - Dark Glow | Type Pulse | Type Pulse | 9:16 | implemented |
| Particle Card - Accent Motion | Particle Card | Particles | 1:1 | placeholder |
| Spectrum Promo - Clean Grid | Spectrum Promo | Spectrum Bars | 16:9 | implemented |

Export preset status is still-image focused. v0.2 does not include full creator-session file serialization or video export.

## What Save/Load Means Today

Save Preset and Load Preset currently save/load Brand Kit JSON only:

- artist name
- track title
- label name
- CTA
- release/status text
- logo path and logo display values
- brand color hints

Session state such as selected module/template/export preset is handled by the current editor state and DAW project recall, not the local Brand preset JSON.

## Future/TODO

- Full creator session preset serialization.
- Recent preset list.
- File picker based save/load.
- Preset validation UI.
- Cloud presets, accounts, sharing, marketplace, and telemetry remain out of scope.

## Manual Tests

- Select every built-in session preset and confirm template/module/export state updates.
- Confirm built-in session presets update editable Artist, Track, Label, and CTA fields.
- Reset and confirm Minimal Meter / Spectrum Bars / Current export / default Brand Kit values.
- Save a Brand preset and confirm status reports local save.
- Load a missing or malformed Brand preset and confirm the app fails safely without losing the current session.

