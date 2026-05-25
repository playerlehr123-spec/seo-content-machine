# WaveFrame Bug Bash Plan

This bug bash plan is for private beta readiness and feedback intake.

## Goals

- Find P0/P1 issues before wider sharing.
- Confirm audio pass-through remains unchanged.
- Exercise standalone, VST3, output window, OBS, module/template, and preset workflows.
- Capture reproducible reports with enough detail to fix them.

## QA Levels

- Level 0: CI Build Check.
- Level 1: Standalone Smoke Test.
- Level 2: VST3 DAW Smoke Test.
- Level 3: Creator Workflow Test.
- Level 4: OBS Workflow Test.
- Level 5: Longer Stability Test.

## Intake Links

- Feedback intake: `BETA_FEEDBACK_INTAKE.md`
- Triage rules: `FEEDBACK_TRIAGE_RULES.md`
- Feedback tracker: `BETA_FEEDBACK_TRACKER.md`
- Fix sprint workflow: `FIX_SPRINT_WORKFLOW.md`
- Label recommendations: `GITHUB_LABELS.md`

## Bug Bash Rules

- Log one issue per report.
- Include artifact/run number.
- Include standalone/VST3 and DAW details.
- Include module/template selected.
- Include output/OBS status.
- Escalate audio pass-through reports immediately.
- Defer feature requests unless they block private beta testing.

## Fix Sprint Hand-off

- P0/P1 confirmed issues should be handed to `FIX_SPRINT_WORKFLOW.md`.
- Select no more than 3 fixable issues per sprint.
- Update `BETA_FEEDBACK_TRACKER.md` after fix and retest.
- Keep feature requests in roadmap/TODO unless they block v0.1 testing.
