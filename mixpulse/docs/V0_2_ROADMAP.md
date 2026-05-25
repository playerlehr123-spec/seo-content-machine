# WaveFrame v0.2 Roadmap

v0.1 is the private beta foundation. v0.2 should make WaveFrame more useful and testable without turning it into a public release.

WaveFrame remains the user-facing product name. MixPulse remains the current internal codename, CMake target, plugin/artifact name, and build naming for now.

## v0.2 Goals

- Improve visual module quality.
- Improve template editing.
- Improve Brand Kit workflow.
- Improve preset save/load UX.
- Improve Output/OBS workflow.
- Fix stability issues found through private beta feedback.
- Start naming cleanup stage 1 if safe.
- Increase DAW compatibility confidence.

## What v0.2 Should Improve

- More polished Logo Reactor, Type Pulse, Promo Card, Particles, and Spectrum Bars visuals.
- Clearer template picker and template/module mapping.
- Better brand defaults, color controls, logo placeholder positioning, and text placement options.
- Safer preset save/load/reset behavior with clearer status messages.
- Output window status, aspect guides, OBS capture mode clarity, and still-frame workflow copy.
- QA matrix quality, DAW test coverage, and feedback tracking.

## What v0.2 Will Not Include

- Public release.
- Installer implementation.
- Code signing implementation.
- Built-in video export.
- NDI / Spout / Syphon.
- Shader SDK.
- Virtual camera.
- macOS / AU.
- Cloud accounts/templates.
- Telemetry.
- Plugin ID rename.
- CMake target rename.

## Feature Candidates

### A. Visual Modules v2

- Logo Reactor polish.
- Type Pulse polish.
- Promo Card polish.
- Particles polish.
- Spectrum Bars polish.
- Better template/module mapping.

### B. Template Editing v2

- Clearer template picker.
- Editable template fields.
- Template status.
- Template preview overlays.
- Better default templates.
- Sprint 3 implemented safer template metadata, 10 starter presets, template/module mapping display, and preview overlay context. Deeper field editing remains future work.

### C. Brand Kit v2

- Better color controls.
- Logo placeholder positioning.
- Text placement options.
- Save/load brand defaults.
- Logo/image import research only, not implementation unless approved later as safe.
- Sprint 3 improved default brand text, reset expectations, and preview fallback display. Color pickers and logo/image import remain future/TODO.

### D. Presets v2

- Better built-in presets.
- Safer save/load/reset.
- Preset validation.
- Recent presets if safe.
- Clearer status messages.

### E. Output / OBS v2

- Cleaner output status.
- Better aspect guides.
- OBS capture mode polish.
- Full-screen capture reliability.
- Still-frame workflow clarity.

### F. Naming Cleanup Stage 1

- Docs and UI clarify WaveFrame.
- Possible artifact display label cleanup.
- No plugin ID rename.
- No risky CMake target rename.

### G. QA / Beta Feedback

- Fix P0/P1 first.
- Improve QA matrix.
- Track DAW compatibility.
- Keep tester feedback loop visible.

## Bug-Fix Candidates

Prioritize from beta feedback:
- App launch, scan/load, and CI artifact blockers.
- Audio pass-through reports.
- Output window close/reopen crashes.
- Frame/HUD crashes.
- Module/template switching crashes.
- Preset save/load/reset crashes.
- DAW remove/reload crashes.
- OBS capture workflow blockers.

## QA Goals

- Keep CI green for every PR.
- Preserve `MixPulse-Windows-Beta` and `MixPulse-Windows-Build-Folder`.
- Track Ableton, FL Studio, Reaper, Bitwig, and Other DAW results.
- Keep audio pass-through unchanged.
- Keep manual test instructions current.
- Retest fixed P0/P1 issues before closing.

## Release Criteria

v0.2 can become a private beta candidate when:
- P0 issues are closed or explicitly out of scope with evidence.
- P1 issues in common workflows are fixed or clearly deferred.
- CI is green.
- Artifacts upload.
- Manual standalone smoke test passes.
- At least one DAW smoke test passes.
- OBS output capture workflow is understandable.
- Known issues and release notes are updated.

## Risks

- Plugin ID, target, artifact, or folder renames can break DAW scanning or CI.
- Feature creep can bury P0/P1 fixes.
- Video/export scope can pull the project away from v0.2 goals.
- File IO, GUI calls, locks, or allocations in `processBlock` would violate the audio safety promise.
- Visual polish can become expensive if it turns into a renderer rewrite.
