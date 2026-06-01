# WaveFrame Fix Sprint Workflow

Fix sprints are small, stability-focused passes over private beta feedback.

## Fix Sprint Rules

- Pick top 3 issues only.
- P0/P1 first.
- No feature scope.
- No unrelated refactors.
- One PR per sprint.
- CI must be green.
- Update the tracker after each fix.
- Retest fixed issues before closing them.
- Do not merge if audio pass-through is at risk.
- Do not touch `processBlock` unless the explicit task is an audio safety bug and the change has been reviewed.

## Sprint Intake

1. Review `BETA_FEEDBACK_TRACKER.md` and open beta issues.
2. Select up to 3 highest-priority confirmed items.
3. Confirm each item has repro steps and environment details.
4. Mark selected items `In progress`.
5. Keep deferred feature requests out of the sprint.

## Fix Sprint PR Template

```md
## Issues fixed
- ID / issue link:
- Severity:
- Area:

## Files changed
-

## Safety
- processBlock unchanged:
- audio behavior unchanged:
- PluginProcessor touched:
- CMake/workflow changed:

## CI
- Build status:
- Artifacts:

## Retest notes
- Standalone:
- DAW:
- OBS/output:
```

## Closeout

- Mark fixed issues `Needs retest`.
- Add retest result and artifact/run number.
- Close only after verification.
- If not reproducible, mark `Cannot reproduce` and leave notes.
