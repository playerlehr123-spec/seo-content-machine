# WaveFrame Brand Kit

## Purpose

Brand Kit v1 gives templates and visual modules a shared creator identity state without adding audio processing or background services.

## Fields

- `artistName`: default `Artist Name`
- `trackTitle`: default `Track Title`
- `labelName`: default `Label Name`
- `callToAction`: default `Out Now`
- `releaseStatusText`: default `Out Now`
- `brandPrimaryColor`: default cyan
- `brandAccentColor`: default gold
- `brandBackgroundColor`: default dark WaveFrame background
- `brandTextColor`: default white
- `logoPlacement`: center/corner/watermark placement state
- `logoScale`: placeholder logo scale
- `logoOpacity`: placeholder logo opacity
- `showLogoPlaceholder`: shows or hides the placeholder logo mark
- `showTextOverlay`: shows or hides brand text overlays

## Current Implementation

- Brand Kit v1 extends the existing `BrandLayer::CreatorBrandState`.
- The editor exposes artist, track, label, CTA, logo/text toggles, logo placement, and safe color preset placeholders.
- Preset save/load uses the existing WaveFrame preset JSON flow from the UI thread.
- Visualizer rendering reads Brand Kit values for text, colors, background, logo opacity, and overlay visibility.

## Future/TODO

- Real logo/image import.
- Full color picker UI.
- Multiple named brand kits.
- Font selection and typography presets.
- Cloud presets, accounts, telemetry, or online template marketplace.

## Safety Notes

- No Brand Kit file I/O happens in `processBlock`.
- Brand Kit state is UI/template/render state only.
- Audio remains pass-through and analysis-only.
