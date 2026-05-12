# MixPulse Beta Install (Windows-first)

## 1) Download artifacts from GitHub Actions
From the latest successful **MixPulse Build** run, download:
- `MixPulse-Windows-Beta`
- `MixPulse-Windows-Build-Folder` (debug fallback)

## 2) Standalone
- Unzip `MixPulse-Windows-Beta`.
- If present, run `MixPulse.exe` or `MixPulse_Standalone.exe`.
- Windows SmartScreen warnings are expected for unsigned beta builds.

## 3) VST3 (if included)
- If `MixPulse.vst3` is present, copy it to:
  - `C:\Program Files\Common Files\VST3\`
- Rescan plugins in your DAW.

## 4) What to validate quickly
- Audio passes through unchanged.
- Peak/RMS meters move.
- LUFS M shows placeholder/approximation behavior.
- LUFS S/I remain `--.-` placeholders.
- Creator Output Window opens/closes.
- Export Frame writes PNG to `Documents/MixPulse/`.

## 5) Current limitations
- Windows-first beta workflow.
- macOS/AU deferred.
- LUFS not final BS.1770 implementation.
- True Peak currently sample-peak placeholder.
- Visual modules beyond Spectrum Bars are placeholders.
- No video import/export, no NDI/Spout/Syphon.
