# MixPulse Private Beta Install Guide

## 1) Download beta artifacts from GitHub Actions
1. Open the repository on GitHub.
2. Go to **Actions**.
3. Open the **MixPulse Build** workflow.
4. Open the latest successful run.
5. Download artifacts:
   - `MixPulse-macOS-Release`
   - `MixPulse-Windows-Release`

## 2) macOS install
- Unzip `MixPulse-macOS-Release`.
- Copy `MixPulse.vst3` to:
  `/Library/Audio/Plug-Ins/VST3/`
- Copy `MixPulse.component` to:
  `/Library/Audio/Plug-Ins/Components/`
- If included, open `MixPulse.app` for Standalone testing.

Unsigned beta note:
- macOS may block first launch.
- Use right-click **Open**.
- If required, allow in **System Settings > Privacy & Security**.

## 3) Windows install
- Unzip `MixPulse-Windows-Release`.
- Copy `MixPulse.vst3` to:
  `C:\Program Files\Common Files\VST3\`
- If included, run `MixPulse.exe` for Standalone testing.

## 4) DAW rescan
Ableton:
- Preferences > Plug-Ins
- Enable VST3
- Rescan

FL Studio:
- Options > Manage plugins
- Find installed plugins

Logic (macOS):
- AU only
- Rescan/validate if needed

## 5) Known beta limitations
- Builds are unsigned.
- LUFS M is placeholder approximation.
- LUFS S/I are placeholders.
- True Peak is sample peak placeholder.
- Visual modes beyond Spectrum are placeholders.
- No NDI/PDF/CSV/video export.
- No installer yet.

## 6) What to report
Please include:
- OS
- DAW
- sample rate
- buffer size
- whether VST3 scanned
- whether plugin loaded
- whether audio passed through unchanged
- whether meters moved
- whether visualizer opened
- whether screenshot saved
- crash steps/logs
