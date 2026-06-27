# WaveFrame Private Beta README

WaveFrame is a Windows-first private beta for turning audio into branded visual content. MixPulse may still appear in artifact names, plugin names, and internals during this beta.

Do not share private beta builds publicly.

## What To Download

- Main tester artifact: `MixPulse-Windows-Beta`
- Optional/internal debugging artifact: `MixPulse-Windows-Build-Folder`

## What To Test

- Standalone launch.
- Audio meters.
- Output window.
- HUD, fullscreen, and Frame.
- Module/template switching.
- Preset reset/save/load if present.
- VST3 scan/load in DAWs if comfortable.
- OBS Window Capture workflow.
- Export preset switching and current-frame PNG capture.

## How To Report Feedback

- Start with `BETA_FEEDBACK_INTAKE.md`.
- Use `FEEDBACK_TRIAGE_RULES.md` for severity.
- Use GitHub beta issue templates for bugs and feedback.
- Include artifact/run number, Windows version, DAW/version when relevant, module/template selected, output/OBS status, repro steps, and screenshots/video/logs when useful.

Useful links:
- Release freeze: `RELEASE_FREEZE_v0.1.md`
- Final readiness checklist: `FINAL_READINESS_CHECKLIST_v0.1.md`
- Release notes: `RELEASE_NOTES_v0.1.md`
- Known issues: `KNOWN_ISSUES.md`
- Bug reporting details: `BETA_BUG_REPORTING.md`
- Manual tracker: `BETA_FEEDBACK_TRACKER.md`
- Fix sprint rules: `FIX_SPRINT_WORKFLOW.md`
- Label recommendations: `GITHUB_LABELS.md`
- Tester invite copy: `BETA_TESTER_MESSAGE_TEMPLATE.md`

## Known Limits

- Unsigned Windows warning is expected.
- Built-in video export is not implemented.
- Frame/current-frame export is still PNG only.
- OBS is the current motion capture workflow.
- VST3 testing is experimental.
- Some templates/modules may be placeholders.
- No NDI, Spout, Syphon, shader SDK, virtual camera, macOS/AU, cloud upload, or telemetry.
