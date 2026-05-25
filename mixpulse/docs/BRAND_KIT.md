# WaveFrame Brand Kit

Status: v0.2 Sprint 3 clarifies Brand Kit defaults and display behavior. The current implementation uses `BrandLayer::CreatorBrandState`.

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
- Brand text appears in the editor Brand panel and preview overlay.
- Preset save/load uses local JSON under `Documents/WaveFrame/Presets`.
- Malformed logo scale, opacity, and placement values are clamped or reset safely.
- Reset restores default Brand Kit text and visual defaults.

## Placeholder / Future

- Real text field editing needs a dedicated safe UI pass.
- Logo/image import remains placeholder/TODO.
- Background/text color fields may be split from the current primary/secondary/accent color model later.
- Cloud presets, user accounts, telemetry, and template marketplace behavior are out of scope.

## Manual Tests

- Reset defaults and confirm Artist Name, Track Title, Label Name, and Out Now return.
- Load a missing preset and confirm the UI reports failure without crashing.
- Load malformed preset values and confirm the UI remains readable.
- Switch templates and confirm CTA/release text updates safely.
