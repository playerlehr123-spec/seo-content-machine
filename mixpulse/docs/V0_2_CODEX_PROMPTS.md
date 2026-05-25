# WaveFrame v0.2 Codex Prompt Library

These are concise prompt outlines for v0.2 work. Add specific issue IDs, files, and test results before using them.

## 1. Bug Fix Sprint

Goal:
- Fix the top 1-3 confirmed P0/P1 issues from beta feedback.

Allowed scope:
- Minimal bug fixes only.
- Docs/QA tracker updates.

Non-negotiables:
- Do not change audio behavior.
- Do not touch `processBlock` unless explicitly approved for an audio safety fix.
- No feature scope.
- Keep CI green.

Final report:
- Issues fixed/deferred.
- Files changed.
- Audio/processBlock/CMake/workflow status.
- CI/artifact status.
- Retest notes.

## 2. Visual Modules v2

Goal:
- Polish Logo Reactor, Type Pulse, Promo Card, Particles, and Spectrum Bars.

Allowed scope:
- Visual renderer polish.
- Template/module mapping labels if safe.
- Docs updates.

Non-negotiables:
- No audio processing changes.
- No shader SDK.
- No video export.
- No renderer rewrite unless specifically approved.

Final report:
- Modules improved.
- Modules deferred.
- Files changed.
- CI/artifact status.
- Manual visual tests.

## 3. Template + Brand UX

Goal:
- Improve template picker, brand controls, preview overlays, and default template clarity.

Allowed scope:
- UI grouping.
- Existing Brand Kit/template structures.
- Docs updates.

Non-negotiables:
- No full PluginEditor rewrite.
- No cloud templates/accounts.
- No risky file import.
- No audio behavior changes.

Final report:
- UX changes.
- Files changed.
- Current vs future status.
- CI/artifact status.
- Manual tests.

## 4. Preset / Session Polish

Goal:
- Make save/load/reset safer and clearer.

Allowed scope:
- Existing preset/session state handling.
- Validation and status messages.
- Docs updates.

Non-negotiables:
- No file IO in `processBlock`.
- No processor/audio changes unless explicitly required and reviewed.
- No cloud sync.

Final report:
- Preset behavior changed.
- Edge cases handled.
- Files changed.
- CI/artifact status.
- Manual reset/save/load tests.

## 5. Output / OBS v2

Goal:
- Improve output status, aspect guide clarity, OBS capture mode, fullscreen capture reliability, and still-frame messaging.

Allowed scope:
- Output window/UI copy.
- Existing export/still-frame docs.
- Lightweight status/guides if safe.

Non-negotiables:
- No video export.
- No NDI, Spout/Syphon, virtual camera, or shader SDK.
- No workflow/CMake changes unless required.

Final report:
- Output/OBS changes.
- Frame/still behavior.
- Files changed.
- CI/artifact status.
- OBS/manual tests.

## 6. v0.2 Release Candidate

Goal:
- Prepare v0.2 release notes, known issues, QA matrix, tester notes, and final readiness docs.

Allowed scope:
- Docs only unless a release blocker fix is explicitly approved.

Non-negotiables:
- No new features.
- No renames.
- No app/audio behavior changes.
- Keep CI green.

Final report:
- Docs changed.
- Readiness status.
- CI/artifact status.
- Remaining blockers.
