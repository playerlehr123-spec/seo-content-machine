# WaveFrame v0.1 Private Beta Release Freeze

Status:
- Private beta candidate.
- Windows-first.
- Unsigned.
- Internal artifact names may still say MixPulse.

WaveFrame is the user-facing product name. MixPulse remains the current internal codename, CMake target, plugin/artifact naming, and build artifact name for v0.1.

## Frozen Scope

WaveFrame v0.1 private beta includes:
- Standalone beta artifact.
- VST3 beta artifact if present.
- Compact metering.
- Creator UI layout.
- Output window.
- OBS capture workflow.
- Visual modules/placeholders.
- Brand/template/preset workflow.
- Still-frame/current-frame workflow.
- Bug reporting and QA docs.

## Out Of Scope For v0.1

The following are not part of v0.1:
- Public release.
- Installer.
- Code signing.
- Video export.
- NDI / Spout / Syphon.
- Shader SDK.
- macOS / AU.
- Cloud templates/accounts.
- Telemetry.
- Plugin/artifact renaming.
- Full logo/image import unless already safely implemented.

## Release Rule

After this freeze:
- Only P0/P1 fixes should be accepted before private beta.
- No new features until v0.2 planning.
- No UI rewrites.
- No plugin/artifact/internal renames.
- No audio behavior changes.
- No `processBlock` changes.

## Merge Readiness Rule

A release-freeze PR is merge-ready only when:
- CI is green.
- `MixPulse-Windows-Beta` uploads.
- `MixPulse-Windows-Build-Folder` uploads.
- No app/audio/build behavior changed in the freeze pass.
- Known issues and feedback/triage docs are linked.
