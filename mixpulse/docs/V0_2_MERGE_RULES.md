# WaveFrame v0.2 Merge Rules

Use these rules for every v0.2 PR.

## Rules

- One focused PR per sprint.
- No feature PR if the current PR is red.
- No merge without green CI.
- No merge if audio pass-through is at risk.
- No merge if `processBlock` changed without explicit review.
- No merge if `PluginProcessor` was touched unnecessarily.
- No merge if CMake/workflow changed unexpectedly.
- Docs must mark current vs future.
- No public beta claims until QA passes.
- No plugin ID rename.
- No CMake target rename.
- No video export implementation.
- No NDI, Spout/Syphon, shader SDK, virtual camera, macOS/AU, cloud upload, or telemetry.

## Required Final Report For Every v0.2 PR

- Files changed.
- Feature/bug summary.
- `processBlock` changed?
- Audio behavior changed?
- CMake changed?
- Workflow changed?
- PluginProcessor touched?
- CI status.
- Artifact status.
- Manual tests recommended.
- Remaining TODOs.

## Merge Blockers

- CI red.
- `MixPulse-Windows-Beta` missing.
- `MixPulse-Windows-Build-Folder` missing.
- Audio pass-through uncertainty.
- Unreviewed processor/audio changes.
- Unplanned build/workflow changes.
- Feature scope that belongs in v0.3/future.
