# WaveFrame Brand Layer (Beta Foundation)

Brand Layer provides local-only creator content state for:
- artist/track/label text
- logo path + display options
- brand color hints
- scene/preset identity helpers

## Current beta scope
- Local state model (`CreatorBrandState`).
- Local JSON preset save/load helpers.
- Default preset path:
  `Documents/WaveFrame/Presets/WaveFrame_UserPreset.json`
- No processBlock file I/O.
- No network upload/telemetry.

## Logo import scope
- Intended formats: PNG/JPG local files.
- If host context blocks picker behavior, standalone-first flow is acceptable in beta.
- No cloud import, no external URLs.

## Release Promo Card scope
- Artist/Track/Label/CTA text model exists in state foundation.
- Rich typography/template styling is future work.

## Future
- Logo PNG import workflow polish
- Editable promo text controls
- Template packs
- Fixed-resolution frame exports
- Social preset bundles
- Video export investigation (later)
