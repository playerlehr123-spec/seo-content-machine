# WaveFrame Feedback Triage Rules

Use these rules to sort private beta feedback without turning every idea into a release blocker.

## Severity

### P0 Blocker

Blocks private beta use or invalidates the core audio safety promise:
- App will not launch.
- Plugin will not scan/load.
- Audio is muted or changed unexpectedly.
- Crash on open.
- CI cannot build artifact.
- `processBlock` changes audio.
- Repeatable crash in a common basic workflow.

Default decision: fix now.

### P1 Major

Breaks an important beta workflow:
- Output window crashes.
- Module switching crashes.
- Frame/HUD crashes.
- Preset save/load/reset crashes.
- DAW remove/reload crashes.
- OBS capture unusable.
- Major UI path broken.

Default decision: fix before private beta when reproducible.

### P2 Minor

Non-blocking issue that hurts confidence or clarity:
- Confusing UI text.
- Unclear status.
- Visual glitch.
- Layout issue.
- Docs mismatch.
- Non-blocking control bug.
- Non-critical template issue.

Default decision: fix if small, otherwise defer to next beta.

### P3 Polish

Quality and taste improvements:
- Spacing.
- Color.
- Copy.
- Visual style.
- Animation feel.
- Tooltip improvements.

Default decision: defer unless already touching the same area.

### Feature Request

Anything not required for v0.1 private beta:
- New visual modules.
- Built-in video export.
- NDI, Spout, Syphon, shader SDK, or virtual camera.
- Cloud templates, account systems, marketplace features.
- Installer/signing work beyond current docs.

Default decision: roadmap/TODO. Feature requests should not block release unless required for the core beta promise.

## Triage Decisions

Use one of these decisions:
- Fix now.
- Fix before private beta.
- Defer to next beta.
- Add to roadmap.
- Needs more info.
- Cannot reproduce.

## Repro Rules

- Reproducible P0/P1 issues need immediate owner review.
- One-off crashes need environment details and retest.
- DAW-only issues need DAW name, version, plugin format, and remove/reload notes.
- Audio pass-through reports must be treated as P0 until disproven.
- Feature requests should include the user goal, not just the requested UI/control.
