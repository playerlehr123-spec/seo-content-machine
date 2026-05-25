# WaveFrame v0.1 Private Beta Release Notes

Status: Private beta candidate

Product name: WaveFrame

Internal codename: MixPulse

Artifact names:
- `MixPulse-Windows-Beta`
- `MixPulse-Windows-Build-Folder`

## What Is Included
- Windows standalone beta artifact when produced by CI.
- VST3 beta artifact when produced by CI.
- Compact producer meter UI.
- Output window for external capture.
- OBS Window Capture workflow.
- Creator template workflow.
- Brand/template/preset scaffolding.
- Visual modules and placeholders.
- Still-frame/current-frame PNG workflow.
- QA docs and bug reporting flow.

## What Is Not Included
- Signed installer.
- Public release packaging.
- Built-in video export.
- NDI, Spout, or Syphon.
- Shader SDK.
- Virtual camera.
- macOS/AU.
- Cloud templates, account system, or telemetry.
- Final plugin/artifact naming cleanup.
- Full logo/image import if the current build still shows placeholder behavior.

## Known Limitations
- Unsigned Windows warning is expected.
- Artifact, binary, plugin, or internal names may still say MixPulse.
- DAW compatibility still needs testing across hosts.
- VST3 is experimental for private beta.
- Some modules/templates may be placeholders or v1 visuals.
- Output capture currently uses OBS/manual capture workflow.
- No installer or auto-update exists yet.

## Tester Focus
- Launch standalone app.
- Confirm audio pass-through is unchanged.
- Confirm meters move.
- Open/close/reopen Output window.
- Capture Output in OBS.
- Switch modules/templates.
- Test Frame, HUD, fullscreen, and reset/save/load where available.
- Scan/load VST3 in DAWs.
- Report crash/freeze cases with reproduction steps.

## Bug Reporting
Use the GitHub bug report template or `mixpulse/docs/BETA_BUG_REPORTING.md`.

Include:
- Artifact/run number.
- Windows version.
- DAW/version if applicable.
- Standalone or VST3.
- Module/template selected.
- Output window open?
- OBS involved?
- Steps to reproduce.
- Expected vs actual behavior.
- Crash/freeze status.
- Whether audio pass-through changed.
- Screenshot, log, or short video if available.
