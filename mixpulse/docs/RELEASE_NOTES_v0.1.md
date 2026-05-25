# WaveFrame v0.1 Private Beta Release Notes

Status: private beta candidate. Do not share publicly yet.

Product name: WaveFrame.

Internal codename/build naming: MixPulse.

Artifact names:
- `MixPulse-Windows-Beta`
- `MixPulse-Windows-Build-Folder`

Some files, plugin names, and artifact names may still say MixPulse during v0.1. Naming cleanup is staged for later to avoid breaking CI, plugin scanning, and beta docs.

## What Is Included

- Windows standalone beta artifact if produced by CI.
- VST3 beta artifact if produced by CI.
- Compact meter UI.
- Output window.
- OBS capture workflow.
- Creator template workflow.
- Brand/template/preset scaffolding.
- Visual modules and placeholders.
- Still-frame/current-frame workflow.
- QA docs, bug reporting docs, and feedback triage docs.

## What Is Not Included

- Signed installer.
- Public release.
- Built-in video export.
- NDI / Spout / Syphon.
- Shader SDK.
- macOS / AU.
- Cloud templates/accounts.
- Telemetry.
- Final plugin/artifact renaming.
- Full logo/image import unless already safely implemented.

## Known Limitations

- Unsigned Windows warning is expected.
- Artifact/internal names may still say MixPulse.
- Windows-first only.
- VST3 is experimental and needs DAW testing.
- DAW compatibility still needs manual verification.
- OBS/manual capture is the current motion capture workflow.
- Some modules/templates may be placeholders.
- No installer or code signing yet.

## Tester Focus

Please test:
- Launch.
- Audio pass-through.
- Meters.
- Output window.
- OBS capture.
- Module/template switching.
- Preset reset/save/load if implemented.
- DAW scan/load.
- Crash/freeze reports.

## Bug Reporting

Use the beta issue templates or `BETA_FEEDBACK_INTAKE.md`.

Include:
- Artifact/run number.
- Windows version.
- Standalone or VST3.
- DAW/version if relevant.
- Audio interface if relevant.
- Module/template selected.
- Output window open: yes/no.
- OBS involved: yes/no.
- Steps to reproduce.
- Expected vs actual behavior.
- Screenshot/video/log if helpful.
- Whether audio pass-through changed.
