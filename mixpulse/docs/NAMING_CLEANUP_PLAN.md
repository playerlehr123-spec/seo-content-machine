# WaveFrame Naming Cleanup Plan

This is a planning document only. Do not rename plugin IDs, CMake targets, artifact names, folders, or bundle identifiers during private beta hardening without a dedicated compatibility pass.

## Current State
- User-facing product name: WaveFrame.
- Internal codename: MixPulse.
- CMake project and target: `MixPulse`.
- Current plugin product name in CMake: `MixPulse`.
- Current company/manufacturer text in CMake: `MixPulse`.
- Current bundle ID: `com.mixpulse.plugin`.
- Current plugin manufacturer/code values: `MxPl` / `Mpv1`.
- Current expected VST3 bundle name: `MixPulse.vst3`.
- Current expected standalone names: `MixPulse.exe` or `MixPulse_Standalone.exe`.
- Current GitHub Actions workflow name: `MixPulse Build`.
- Current beta artifact names: `MixPulse-Windows-Beta` and `MixPulse-Windows-Build-Folder`.
- Current generated artifact README: `README_INSTALL.txt`, with WaveFrame beta copy and MixPulse internal/artifact naming.
- Current repo folder: `mixpulse`.
- Current source class names: `MixPulseAudioProcessor`, `MixPulseAudioProcessorEditor`.
- Current local user-facing data paths may use WaveFrame, such as `Documents/WaveFrame/`.

WaveFrame is already the intended user-facing name in UI/docs. MixPulse remains the build, plugin, target, artifact, and compatibility name for now.

## Future Desired State
- User-facing UI: WaveFrame.
- Standalone app: `WaveFrame.exe` eventually.
- Beta artifact: `WaveFrame-Windows-Beta` eventually.
- Plugin display name: WaveFrame eventually.
- VST3 bundle: `WaveFrame.vst3` eventually, only after DAW compatibility review.
- Installer/package display: WaveFrame eventually.
- CMake/internal target may remain `MixPulse` until final release if that keeps CI and source layout stable.
- Source folder may remain `mixpulse` until a larger repo cleanup is justified.

## Naming Risk Audit
| Surface | Current name | Desired name | Risk |
| --- | --- | --- | --- |
| UI header/product copy | WaveFrame | WaveFrame | Low |
| Branding constants | WaveFrame + MixPulse codename | WaveFrame + explicit internal codename | Low |
| CMake project/target | MixPulse | Maybe MixPulse until release | Medium |
| `PRODUCT_NAME` | MixPulse | WaveFrame | High for DAW/plugin identity |
| `BUNDLE_ID` | `com.mixpulse.plugin` | WaveFrame-style bundle ID | High for DAW scan/cache behavior |
| Plugin code/manufacturer code | `Mpv1` / `MxPl` | TBD | High for plugin identity compatibility |
| VST3 bundle name | `MixPulse.vst3` | `WaveFrame.vst3` | High for install, scan, docs, user cache |
| Standalone EXE | `MixPulse.exe` | `WaveFrame.exe` | Medium |
| GitHub artifact names | MixPulse-prefixed | WaveFrame-prefixed | Medium |
| Workflow name | `MixPulse Build` | `WaveFrame Build` | Low/medium |
| Repo folder | `mixpulse` | maybe `waveframe` | High for CMake/includes/scripts |
| README_INSTALL text | Mixed | WaveFrame-first with MixPulse note | Low |
| Docs | Mixed historical references | WaveFrame-first with MixPulse note | Low |

## Why Plugin Renames Are Risky
- Changing VST3/plugin IDs can affect DAW scanning, plugin cache entries, saved project recall, and duplicate plugin detection.
- Changing CMake targets can break CI, fallback build targets, artifact discovery, and generated JUCE target names.
- Changing artifact names can break docs, release checklists, beta tester instructions, and downstream scripts.
- Changing folder names can break CMake paths, include paths, workflow scripts, and local worktrees.
- Changing source class names creates broad churn without improving private beta quality.

## Recommended Staged Rename

### Stage 1 - Private Beta Clarity
- Docs clarify that WaveFrame is user-facing.
- UI says WaveFrame.
- Artifact, plugin, CMake target, VST3, EXE, workflow, and folder names stay MixPulse.
- `README_INSTALL.txt` remains WaveFrame-first but explicitly warns that MixPulse names are expected.
- Beta testers are told to look for MixPulse or WaveFrame in DAWs.

### Stage 2 - Packaging Copy Cleanup
- Keep internal target `MixPulse`.
- Keep plugin IDs and VST3 bundle name stable.
- Make artifact README, release notes, and GitHub summary more WaveFrame-first.
- Optionally add a `WaveFrame_README.txt` inside the artifact while retaining `README_INSTALL.txt`.
- Consider whether artifact display names can change without breaking existing docs or tester instructions.

### Stage 3 - Standalone Display Cleanup
- Review JUCE standalone app display behavior.
- Consider producing `WaveFrame.exe` only if CMake/JUCE output naming is predictable in CI.
- Keep `MixPulse.exe` accepted by docs and artifact verification during transition.
- Do not change VST3 plugin identity in this stage.

### Stage 4 - Plugin Identity Review
- Decide final plugin display name, manufacturer, bundle ID, plugin code, and VST3 bundle name.
- Test DAW scan/load/remove/reload/save/reopen before and after the rename.
- Document whether old MixPulse beta projects are expected to recall the renamed plugin.
- Rename artifacts only after plugin identity behavior is understood.

## Recommended Private Beta Decision
For the next private beta, keep MixPulse internal/plugin/artifact naming stable and make the mismatch explicit in docs and artifact copy. The private beta should validate launch, pass-through, output, OBS capture, visual modules, and DAW loading before plugin identity changes are attempted.

## Checks Before Any Rename PR
- Main CI green before the rename.
- Rename PR CI green.
- `MixPulse-Windows-Beta` and `MixPulse-Windows-Build-Folder` artifact behavior intentionally updated or intentionally preserved.
- Standalone EXE discovered in CI.
- VST3 bundle discovered in CI.
- Ableton Live, FL Studio, Reaper, and Bitwig scan/load tests completed where available.
- Saved DAW project recall behavior tested.
- Docs updated in the same PR as any user-visible rename.
