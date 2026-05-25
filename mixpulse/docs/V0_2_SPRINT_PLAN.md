# WaveFrame v0.2 Sprint Plan

Each v0.2 sprint should produce one focused PR. No sprint should add public-release, installer/signing, video export, NDI, Spout/Syphon, shader SDK, virtual camera, macOS/AU, cloud, telemetry, plugin ID rename, or CMake target rename scope.

## Sprint 1 - Beta Feedback Fixes

Goal:
- Fix top P0/P1 issues from private beta feedback.
- Stabilize output/window/HUD/frame if needed.
- Update QA matrix after fixes.

Allowed files:
- Small, targeted app/UI files only when a confirmed bug requires it.
- Docs and QA tracker files.

Danger files:
- `mixpulse/Source/PluginProcessor.cpp`
- `mixpulse/include/PluginProcessor.h`
- `mixpulse/CMakeLists.txt`
- `.github/workflows/mixpulse-build.yml`

Success criteria:
- Top 1-3 P0/P1 issues fixed or clearly deferred.
- No audio behavior changes.
- CI green.

Manual tests:
- Standalone launch.
- Output close/reopen.
- Frame/HUD repeat clicks.
- Module/template switching.
- DAW load/remove/reload for touched areas.

Merge criteria:
- Green CI.
- Artifacts uploaded.
- Retest notes added.
- QA tracker updated.

## Sprint 2 - Visual Modules v2

Goal:
- Improve Logo Reactor, Type Pulse, Promo Card, Particles, and Spectrum Bars visual quality.

Allowed files:
- Visual renderer files.
- Visual module docs.
- Small UI labels if needed.

Danger files:
- Processor/audio files.
- CMake unless new source files are added.
- Workflow YAML.

Success criteria:
- Modules look more polished.
- Switching modules does not crash.
- No audio analysis behavior changes.

Manual tests:
- Render each module.
- Switch modules repeatedly.
- Open Output window.
- Capture frame.

Merge criteria:
- Green CI.
- No forbidden feature scope.
- Docs mark current vs future.

## Sprint 3 - Template + Brand UX

Goal:
- Improve template picker, brand controls, preview overlays, and template/module mapping.

Allowed files:
- Plugin editor UI files if needed.
- Brand/template model files if safe.
- Creator workflow docs.

Danger files:
- Processor/audio files.
- Major PluginEditor rewrite.
- CMake/workflow changes.

Success criteria:
- Template and brand state are clearer.
- Placeholder/future status is honest.
- No crashes on default/empty selection.

Manual tests:
- Template switching.
- Brand defaults.
- Preview overlay readability.
- Reset/default behavior.

Merge criteria:
- Green CI.
- Current/future docs updated.
- No broken output/frame/HUD behavior.

## Sprint 4 - Preset / Session Polish

Goal:
- Improve save/load/reset safety, built-in presets, validation, and status messages.

Allowed files:
- Preset/session/UI state files.
- Docs.

Danger files:
- Processor/audio files.
- File IO paths that could affect audio thread.
- CMake/workflow changes.

Success criteria:
- Reset returns to sane defaults.
- Missing/invalid preset data does not crash.
- Status messages are clear.

Manual tests:
- Save/load/reset.
- Missing preset handling.
- Module/template state after reset.
- DAW project recall if safe to test.

Merge criteria:
- Green CI.
- No audio-thread file IO.
- Known limitations documented.

## Sprint 5 - Output / OBS Polish

Goal:
- Improve aspect guides, OBS capture mode clarity, output status, and still-frame workflow.

Allowed files:
- Visualizer/output window files.
- Plugin editor labels/status if needed.
- Export/OBS docs.

Danger files:
- Processor/audio files.
- Video export, NDI, Spout/Syphon, virtual camera, shader SDK.
- Workflow/CMake.

Success criteria:
- Output workflow is clearer.
- Still-frame behavior is honest.
- OBS capture docs match UI.

Manual tests:
- Output open/close/reopen.
- Resize.
- Fullscreen.
- OBS Window Capture.
- Frame/current-frame behavior.

Merge criteria:
- Green CI.
- No video/export engine added.
- Artifacts unchanged.

## Sprint 6 - v0.2 Release Candidate

Goal:
- Prepare v0.2 release notes, known issues, QA matrix, and tester notes.

Allowed files:
- Docs only unless a release blocker fix is approved.

Danger files:
- App code.
- Processor/audio files.
- CMake/workflow.

Success criteria:
- Release notes exist.
- Known issues updated.
- QA matrix updated.
- Tester instructions updated.

Manual tests:
- Standalone smoke.
- DAW smoke.
- OBS smoke.
- Artifact inspection.

Merge criteria:
- Green CI.
- Artifacts uploaded.
- No release blockers open.
