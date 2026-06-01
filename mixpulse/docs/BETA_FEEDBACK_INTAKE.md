# WaveFrame Beta Feedback Intake

Purpose:
- Collect structured feedback from private testers.
- Separate bugs from feature ideas.
- Keep P0/P1 issues obvious during v0.1 testing.
- Prevent random feedback from derailing the private beta plan.

WaveFrame is the user-facing product name. MixPulse may still appear in artifact names, plugin names, and internals during this beta.

## Feedback Categories

1. Crash / Freeze
2. Audio pass-through issue
3. DAW scan/load issue
4. Output window issue
5. OBS capture issue
6. Frame/still capture issue
7. HUD/UI issue
8. Visual module issue
9. Template/brand/preset issue
10. Documentation issue
11. Feature request
12. General polish

## Required Tester Info

Every beta report should include:
- WaveFrame version or GitHub Actions artifact run number.
- Windows version.
- Standalone or VST3.
- DAW and DAW version, if applicable.
- Audio interface, if applicable.
- Selected module.
- Selected template.
- Output window open: yes/no.
- OBS involved: yes/no.
- Steps to reproduce.
- Expected result.
- Actual result.
- Reproducibility: always, often, sometimes, once, or cannot reproduce.
- Screenshot, video, or log when possible.

## Intake Flow

1. Confirm the tester used the latest intended private beta artifact.
2. Classify the feedback category.
3. Assign initial severity using `FEEDBACK_TRIAGE_RULES.md`.
4. Move the item into `BETA_FEEDBACK_TRACKER.md` or a GitHub issue.
5. Mark missing details as `Needs info`.
6. Route P0/P1 items into a focused fix sprint.
7. Route feature ideas to roadmap/TODO unless they block the core beta promise.

## Current Process Status

Implemented now:
- Manual feedback intake docs.
- GitHub issue templates for beta bugs and beta feedback.
- Markdown tracker template.
- Fix sprint workflow guidance.

Recommended process:
- Use GitHub labels listed in `GITHUB_LABELS.md`.
- Keep one feedback item per issue.
- Pick top 3 fixable issues per fix sprint.

Future/TODO:
- Automated label creation.
- Project board automation.
- Form-backed tester submissions.
