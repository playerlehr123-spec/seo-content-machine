# WaveFrame Roadmap

## Tier 0 Ã¢â‚¬â€ Proven Foundation
- buildable Windows standalone
- app launches
- settings opens
- mic moves meters
- output opens
- fullscreen works
- audio pass-through

## Tier 1 Ã¢â‚¬â€ Core Stability
- CI green
- artifact verification
- CMake/source integration
- createPluginFilter stable
- VST3 DAW test
- no-crash basics
- docs truth pass
- Packaging / Distribution: current ZIP beta artifact, installer research, signing research, and naming cleanup remain future/TODO.
- Beta Feedback / Triage: intake docs, severity rules, manual tracker, issue templates, label guidance, and fix sprint workflow are the current process layer.
- v0.1 Release Freeze: frozen private beta scope, final readiness checklist, known issues, release notes, and v0.2 parking lot.

## Tier 2 Ã¢â‚¬â€ Meter + Output Product
- WaveFrame branding polish
- compact HUD
- better meters
- better output window
- spectrum bars v2
- frame export reliability
- UI/UX Polish Pass 1: cleaner layout, larger preview, grouped controls, right-side creator panels, clearer export/template workflow, still no video export

## Tier 3 Ã¢â‚¬â€ Creator Templates
- Brand Layer
- Promo Card
- Logo Reactor
- export presets
- social aspect guides
- OBS workflow
- template selector
- Visual Modules Batch 2: Logo Reactor v1, Type Pulse v1, Promo Card v1, Particles v1/placeholder
- Visual Modules Batch 2 polish: cleaner v1 renderers for Logo Reactor, Type Pulse, Promo Card, Particles, and Spectrum Bars readability
- v0.2 Sprint 3: Template + Brand UX improves starter template metadata, module recommendations, Brand Kit defaults, preview overlay context, and status labels. Full template editor, logo import, and video export remain future/TODO.
- v0.2 Sprint 4: Preset / Session polish adds built-in session presets, safer Brand preset save/load normalization, clearer reset/default behavior, and truthful docs. Full creator-session file serialization remains future/TODO.
- v0.2 Sprint 5: Output / OBS polish improves output close/reopen/fullscreen safety, OBS Capture Mode messaging, aspect/safe-area guides, and still-frame status clarity. Built-in video export remains future/TODO.
- v0.2 Sprint 7: Editable Brand Fields + Creator Controls v2 adds UI-side Artist, Track, Label, and CTA editing, template-aware helper text, and safer reset/preset synchronization. Logo import, full color picker UX, and deeper template editing remain future/TODO.
- v0.2 Sprint 6: Creator Export + Frame workflow polish clarifies social still PNG presets, current-frame capture, failure messaging, and still-frame vs future video export boundaries.

## Tier 4 Ã¢â‚¬â€ Tool Suite
- Particles
- Pixelator
- Type Pulse
- GeoSync
- Halftone
- Album Motion
- Stream Overlay
- Reel Visualizer

## Tier 5 Ã¢â‚¬â€ Template Club / Community
- Inspiration Wall
- Request Tool
- Submit Visual
- monthly template/tool drops
- preset packs
- future account system

## Tier 6 Ã¢â‚¬â€ Pro Visual Engine Research
- video export
- video import
- Spout/Syphon/NDI
- shader support
- webcam/external input
- timeline/clip playback
- network/render research
- macOS/AU

## Packaging / Distribution
- Current private beta path: ZIP-style `MixPulse-Windows-Beta` artifact.
- Current debug path: `MixPulse-Windows-Build-Folder`.
- Future installer research: Inno Setup, NSIS, WiX, and MSIX comparison.
- Future signing research: standalone EXE, installer, and VST3 signing strategy.
- Future naming cleanup: WaveFrame artifact/plugin display names after beta testing.
- Installer, signing, artifact renames, plugin ID renames, macOS/AU, cloud upload, telemetry, and video export are not implemented.

## Beta Feedback / Triage
- Current intake docs: `BETA_FEEDBACK_INTAKE.md`, `FEEDBACK_TRIAGE_RULES.md`, and `BETA_FEEDBACK_TRACKER.md`.
- Current issue templates: beta bug report, beta feedback, bug report, DAW test report, and feature request.
- Current fix process: `FIX_SPRINT_WORKFLOW.md` with top-3-issue sprint limits.
- Recommended labels are documented in `GITHUB_LABELS.md`.
- Future/TODO: automated label creation, project board automation, and form-backed tester submissions.

## v0.1 Release Freeze
- Current freeze docs: `RELEASE_FREEZE_v0.1.md`, `FINAL_READINESS_CHECKLIST_v0.1.md`, and `RELEASE_NOTES_v0.1.md`.
- Known issues are tracked in `KNOWN_ISSUES.md`.
- Tester instructions are tracked in `TESTER_INSTRUCTIONS.md`.
- v0.2 ideas belong in `V0_2_PARKING_LOT.md`.
- After freeze, only P0/P1 fixes should land before private beta.

## v0.2 Planning
- v0.2 planning has started in `V0_2_ROADMAP.md`, `V0_2_SPRINT_PLAN.md`, `V0_2_BACKLOG.md`, `V0_2_MERGE_RULES.md`, and `V0_2_CODEX_PROMPTS.md`.
- v0.2 remains a private beta development cycle, not a public release.
- Primary goals: visual module quality, template editing, Brand Kit workflow, preset save/load UX, Output/OBS workflow, beta feedback fixes, naming cleanup stage 1 if safe, and DAW compatibility confidence.
- First sprint should be beta feedback fixes: P0/P1 issues before polish.
- Suggested follow-up sprints: Visual Modules v2, Template + Brand UX, Preset / Session Polish, Output / OBS Polish, and v0.2 Release Candidate.
- Sprint 3 Template + Brand UX is in progress as a compile-safe creator workflow polish pass.
- Sprint 4 Preset / Session polish is in progress as a compile-safe reliability and status pass.
- Sprint 5 Output / OBS polish is in progress as a compile-safe capture workflow clarity pass.
- Sprint 7 Editable Brand Fields + Creator Controls v2 is in progress as a compile-safe creator panel polish pass.
- Sprint 6 Creator Export + Frame workflow polish is in progress as a compile-safe still-image workflow clarity pass.

## v0.2 Out Of Scope
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

## v0.3 / Future Ideas
- Video export research after v0.2, with implementation still deferred.
- Installer/signing implementation after research and beta feedback.
- Staged naming cleanup after DAW compatibility confidence improves.
- macOS/AU future research only.
- NDI/Spout/Syphon future research only.
- Template packs and community workflows after private beta scope is stable.



