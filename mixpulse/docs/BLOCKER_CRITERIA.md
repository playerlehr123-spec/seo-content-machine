# WaveFrame Blocker Criteria

Use this document to decide whether a bug blocks private beta sharing.

## P0 Blocker
P0 issues block private beta until fixed or explicitly accepted.

- App will not launch.
- Plugin will not scan or load in any tested DAW.
- Audio is muted, clipped, processed, delayed, or changed unexpectedly.
- `processBlock` modifies valid audio samples beyond pass-through/analysis expectations.
- Crash on open.
- CI cannot build the artifact.
- `MixPulse-Windows-Beta` is missing from the latest relevant green run.

## P1 Major
P1 issues may block sharing depending on frequency and affected workflow.

- Output window crashes.
- Module switching crashes.
- Frame crashes.
- HUD crashes.
- Preset save/load/reset crashes.
- DAW remove/reload crashes.
- OBS capture workflow cannot be completed.
- Artifact README gives materially wrong install instructions.

## P2 Minor
P2 issues should be logged and prioritized but usually do not block private beta alone.

- UI layout issue.
- Text unclear.
- Visual artifact.
- Docs mismatch.
- Missing status message.
- A non-core template/module looks incomplete but does not crash.

## P3 Polish
P3 issues are cleanup candidates.

- Spacing.
- Wording.
- Visual style.
- Tooltip improvements.
- Minor consistency issues.

## Release Decision Rule
- Any open P0 blocks private beta.
- Any repeated P1 should block unless the affected workflow is explicitly excluded from the beta.
- P2/P3 issues can ship if documented in known issues or release notes.
