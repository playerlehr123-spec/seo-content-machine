# WaveFrame Release Checklist

Use this checklist before sharing a WaveFrame beta build outside the development loop. Current artifact names may still use the MixPulse internal codename.

## Required Checks
- [ ] CI is green.
- [ ] `MixPulse-Windows-Beta` artifact downloaded.
- [ ] `MixPulse-Windows-Build-Folder` artifact available for debugging.
- [ ] Standalone smoke test completed.
- [ ] VST3 DAW test completed.
- [ ] `README_INSTALL.txt` checked.
- [ ] No audio behavior changes.
- [ ] `processBlock` pass-through behavior unchanged.
- [ ] Known limitations listed.
- [ ] Version/tag decision made.
- [ ] Release notes created from `mixpulse/docs/RELEASE_NOTES_TEMPLATE.md`.
- [ ] Installer/signing status checked against `mixpulse/docs/INSTALLER_SIGNING_RESEARCH.md`.
- [ ] Distribution level checked against `mixpulse/docs/DISTRIBUTION_PLAN.md`.
- [ ] Feedback intake checked against `mixpulse/docs/BETA_FEEDBACK_INTAKE.md`.
- [ ] Triage rules checked against `mixpulse/docs/FEEDBACK_TRIAGE_RULES.md`.
- [ ] Feedback tracker ready: `mixpulse/docs/BETA_FEEDBACK_TRACKER.md`.
- [ ] Bug report flow ready: `mixpulse/docs/BETA_BUG_REPORTING.md`.
- [ ] Fix sprint workflow ready: `mixpulse/docs/FIX_SPRINT_WORKFLOW.md`.
- [ ] Tester message ready: `mixpulse/docs/BETA_TESTER_MESSAGE_TEMPLATE.md`.
- [ ] Do not share externally until manual DAW test passes.

## Standalone Smoke Test
- [ ] App launches.
- [ ] Settings opens.
- [ ] Meters move with input/audio.
- [ ] Output window opens.
- [ ] Fullscreen works.
- [ ] Frame does not crash.
- [ ] HUD does not crash.
- [ ] App closes cleanly.

## VST3 DAW Test
- [ ] VST3 copied to `C:\Program Files\Common Files\VST3\`.
- [ ] Plugin scans in at least one DAW.
- [ ] Plugin loads on an audio track.
- [ ] Audio pass-through is unchanged.
- [ ] Meters move.
- [ ] UI opens and closes.
- [ ] Output window opens.
- [ ] Plugin can be removed and reloaded.
- [ ] No crash/freeze observed.

## Known Limitations To Confirm
- [ ] Unsigned beta.
- [ ] Windows warning expected.
- [ ] VST3 experimental.
- [ ] Artifact may still use MixPulse naming.
- [ ] Video export not implemented.
- [ ] NDI/Spout/Syphon not implemented.
- [ ] macOS/AU not enabled.
- [ ] Installer not implemented yet.
- [ ] Code signing not implemented yet.

## Feedback / Triage Readiness
- [ ] GitHub beta bug template exists.
- [ ] GitHub beta feedback template exists.
- [ ] Feature request template separates beta blocker, next beta, future roadmap, and nice-to-have.
- [ ] Recommended label system documented in `mixpulse/docs/GITHUB_LABELS.md`.
- [ ] P0/P1 issues have an owner before beta sharing.
