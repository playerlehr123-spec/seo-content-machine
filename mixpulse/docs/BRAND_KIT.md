# WaveFrame Brand Kit

Status: v0.2 Sprint 7 adds editable Brand Text fields for the core creator workflow while keeping logo/image import and deeper color controls future/TODO.

## Fields

- `artistName`
- `trackTitle`
- `labelName`
- `callToAction`
- `releaseStatusText`
- `logoPath`
- `hasLogo`
- `logoOpacity`
- `logoScale`
- `logoPositionMode`
- `brandPrimaryColor`
- `brandSecondaryColor`
- `brandAccentColor`

## Defaults

- Artist: `Artist Name`
- Track: `Track Title`
- Label: `Label Name`
- CTA: `Out Now`
- Release/status: `Out Now`
- Logo: placeholder layer
- Logo opacity: clamped between `0.0` and `1.0`
- Logo scale: clamped between `0.1` and `3.0`

## Implemented Now

- Brand state is local and UI-side.
- Brand text appears in editable editor fields, the preview overlay, and visual modules that already consume `BrandLayer`.
- Editable fields are Artist Name, Track Title, Label Name, and CTA Text.
- Empty editable fields fall back to readable defaults.
- Text input is limited to a compact beta-safe length to protect layout.
- Preset save/load uses local JSON under `Documents/WaveFrame/Presets`.
- Saved JSON includes schema metadata for the current beta format.
- Missing/empty text fields normalize back to readable defaults.
- Malformed logo scale, opacity, and placement values are clamped or reset safely.
- Reset restores default Brand Kit text and visual defaults.
- Built-in session presets apply safe starter Brand Text values.
- Text edits stay UI-side and do not touch the audio callback.

## Placeholder / Future

- Logo/image import remains placeholder/TODO.
- Color controls currently expose primary/accent/background intent as labels/status; full color picker UX remains future/TODO.
- Cloud presets, user accounts, telemetry, and template marketplace behavior are out of scope.

## Manual Tests

- Reset defaults and confirm Artist Name, Track Title, Label Name, and Out Now return.
- Load a missing preset and confirm the UI reports failure without crashing.
- Load malformed preset values and confirm the UI remains readable.
- Switch templates and confirm CTA/release text updates safely.
- Edit Artist, Track, Label, and CTA fields and confirm preview/output text updates where supported.

