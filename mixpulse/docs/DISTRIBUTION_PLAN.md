# WaveFrame Distribution Plan

This document defines release channels and packaging expectations. It does not implement distribution, signing, installer generation, artifact renames, or plugin ID changes.

## Current Distribution Strategy
Use GitHub Actions artifacts for private beta:
- `MixPulse-Windows-Beta`
- `MixPulse-Windows-Build-Folder`

The user-facing product name is WaveFrame. Artifact, binary, and plugin names may still say MixPulse until the naming cleanup stage.

## Release Levels

### Level 0 - Internal CI Artifact
- Audience: developer testing only.
- Source: pull request or branch GitHub Actions run.
- Package: unsigned ZIP-style artifact.
- Install: manual.
- Purpose: validate CI, artifact contents, standalone launch, VST3 presence, and smoke tests.

### Level 1 - Private Beta ZIP
- Audience: trusted testers.
- Source: latest known-good GitHub Actions run.
- Package: `MixPulse-Windows-Beta`.
- Install: unzip, run EXE if present, manually copy VST3 if present.
- Expected warning: unsigned Windows warning.
- Current recommendation for WaveFrame private beta.

### Level 2 - Signed Beta Installer
- Audience: broader private beta group.
- Source: tagged build or approved release branch.
- Package: signed installer candidate.
- Install: guided installer.
- Goal: reduce friction and make VST3/standalone placement more reliable.
- Installer technology: likely Inno Setup or NSIS, to be selected later.

### Level 3 - Public Beta
- Audience: public testers.
- Source: release page or website download page.
- Package: signed installer.
- Requirements: release notes, known issues, support/bug-reporting flow, clear install/uninstall docs.

### Level 4 - Public Release
- Audience: public users.
- Source: website/download page.
- Package: signed installer with stable naming and versioning.
- Requirements: versioning policy, release notes, support docs, final plugin identity decision, regression-tested DAW compatibility.

## Current Artifact Packaging
Expected `MixPulse-Windows-Beta` contents:
- `README_INSTALL.txt`.
- Standalone EXE if produced.
- VST3 bundle if produced.

Expected `MixPulse-Windows-Build-Folder` contents:
- Full build output for debugging.
- Not intended as the normal tester download.

## Future Package Names
Future names are TODO only:
- `WaveFrame-Windows-Beta`.
- `WaveFrame-Windows-Standalone`.
- `WaveFrame-VST3-Beta`.

Do not rename artifacts now. Rename only after docs, tester instructions, and CI packaging checks are updated together.

## VST3 Manual Install
Current private beta testers copy the VST3 bundle to:

```text
C:\Program Files\Common Files\VST3\
```

Then they rescan plugins in the DAW and look for MixPulse or WaveFrame.

## Tester Workflow
1. Download the latest approved artifact.
2. Unzip.
3. Read `README_INSTALL.txt`.
4. Run standalone EXE if present.
5. Copy VST3 bundle if testing plugin format.
6. Rescan DAW.
7. Confirm audio pass-through is unchanged.
8. Confirm meters move.
9. Open Output and test OBS Window Capture.
10. Report bugs with artifact/run number, Windows version, DAW version, and selected module/template.

## What Not To Ship Yet
- Installer.
- Signing certificates or secrets.
- Auto-updater.
- Public download page.
- Account/cloud/template marketplace.
- Telemetry.
- Video export.
- NDI, Spout, Syphon, shader SDK, or virtual camera.
- macOS/AU builds.
- Renamed plugin IDs or artifacts.

## Public Beta Exit Criteria
- Installer path chosen.
- Signing path chosen.
- VST3 install/uninstall tested.
- Standalone install/uninstall tested.
- Known issues documented.
- DAW test matrix has real results.
- Release notes template used for at least one beta.
- WaveFrame/MixPulse naming mismatch either cleaned up or clearly documented.
