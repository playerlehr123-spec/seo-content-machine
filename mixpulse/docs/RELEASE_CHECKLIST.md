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
- [ ] Bug bash completed using `mixpulse/docs/BUG_BASH_PLAN.md`.
- [ ] QA matrix updated in `mixpulse/docs/QA_MATRIX.md`.
- [ ] DAW matrix updated in `mixpulse/docs/DAW_TEST_MATRIX.md`.
- [ ] Blockers checked against `mixpulse/docs/BLOCKER_CRITERIA.md`.
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

## Blocker Review
- [ ] No open P0 blockers.
- [ ] Repeated P1 issues are fixed, excluded from beta scope, or documented.
- [ ] P2/P3 issues are listed in known issues or release notes when relevant.
