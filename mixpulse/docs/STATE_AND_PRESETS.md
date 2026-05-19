# WaveFrame State and Presets (Beta)

## Plugin/DAW state (ValueTree)
WaveFrame stores visual/session state in `WaveFrameState` (stateVersion=1):
- selected scene/module/output preset/export preset
- beat sync + HUD state
- visual FX toggles and intensity/motion/mod source
- Brand Layer text fields and logo path metadata

This supports DAW project recall without changing audio behavior.

## User preset JSON
User preset buttons save/load Brand Layer JSON at:
`Documents/WaveFrame/Presets/WaveFrame_UserPreset.json`

Current preset persistence focus:
- artist/track/label/CTA text
- release status text
- logo path + logo transform settings

## Not saved
- live meter values, FFT data, clip latch runtime state
- output window pointers/streams
- audio device settings
- audio signal content

## Logo path behavior
- State/presets store logo file path only.
- On load, logo path is checked on UI thread.
- Missing logo is handled safely with status messaging.

## Privacy and naming
- Local-only storage. No cloud sync. No telemetry.
- User-facing name is **WaveFrame**.
- Internal codename **MixPulse** may appear in artifacts/state keys.

## Automation prep
- Project currently does **not** use APVTS.
- Future automation targets visual controls only.
- Audio remains pass-through/analysis-only.
