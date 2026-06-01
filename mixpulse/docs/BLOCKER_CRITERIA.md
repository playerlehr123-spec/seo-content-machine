# WaveFrame Blocker Criteria

Use this document to decide whether v0.1 private beta can proceed.

## P0 Blockers

- App will not launch.
- Plugin will not scan/load.
- CI cannot produce artifacts.
- `MixPulse-Windows-Beta` artifact is missing.
- Audio is muted or changed unexpectedly.
- `processBlock` modifies audio.
- Crash on open.
- Repeatable crash in a common basic workflow.

## P1 Major Issues

- Output window crashes.
- Module switching crashes.
- Frame/HUD crashes.
- Preset save/load/reset crashes.
- DAW remove/reload crashes.
- OBS capture is unusable.
- Major UI path is broken.

## Release Rule

- P0 issues block v0.1 private beta.
- P1 issues should be fixed before beta if reproducible in common workflows.
- P2/P3 issues can be deferred unless they create serious tester confusion.
- Feature requests go to `V0_2_PARKING_LOT.md` or roadmap unless they are required for v0.1 testing.
