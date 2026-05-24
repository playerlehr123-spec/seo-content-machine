# WaveFrame Versioning Plan

This is a lightweight beta versioning plan. Do not overcomplicate semantic versioning until the product is closer to public release.

## Current Status
- Current internal baseline: v0.1 private/internal beta.
- Product name: WaveFrame.
- Internal codename/build target/artifact naming: MixPulse.

## Suggested Version Bands
- `v0.1.x`: internal CI and developer builds.
- `v0.2.x`: private beta builds for trusted testers.
- `v0.3.x`: expanded beta with installer/signing research validated.
- `v1.0.0`: public release candidate/public release once naming, installer, signing, DAW testing, and support docs are stable.

## Where Version Should Appear
- UI header/status label.
- `README_INSTALL.txt` inside beta artifact.
- Release notes.
- GitHub PR/release description.
- Private beta guide.
- Bug report template or issue instructions.

## Build Identifiers
Each beta should record:
- Version label.
- Date.
- Git commit SHA.
- GitHub Actions run number.
- Artifact name.
- Branch or tag.

## Release Notes Expectations
Every beta release should include:
- Version/build.
- Date.
- Major changes.
- Known issues.
- Install steps.
- Manual test checklist.
- Artifact/run reference.
- Bug reporting link/instructions.

## Versioning Rules For Now
- Do not rename MixPulse internals as part of a version bump.
- Do not imply public release readiness before installer/signing/DAW testing are stable.
- Use simple incremental beta labels rather than complex pre-release semantics.
- Keep version copy honest: private beta, experimental VST3, Windows-first.
