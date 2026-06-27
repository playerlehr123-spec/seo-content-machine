# WaveFrame v0.1 Final Readiness Checklist

Use this checklist before treating WaveFrame v0.1 as a private beta candidate.

## Repository

- [ ] Main branch clean.
- [ ] Latest release PR green.
- [ ] No unexpected open feature PRs.
- [ ] Docs index updated.
- [ ] Known issues updated.
- [ ] Feedback/triage docs linked.

## CI

- [ ] GitHub Actions green.
- [ ] `MixPulse-Windows-Beta` artifact uploaded.
- [ ] `MixPulse-Windows-Build-Folder` artifact uploaded.
- [ ] `README_INSTALL.txt` present.
- [ ] Standalone EXE present if expected.
- [ ] VST3 present if expected.

## Safety

- [ ] `processBlock` unchanged.
- [ ] Audio pass-through unchanged.
- [ ] `PluginProcessor` untouched in release freeze.
- [ ] CMake unchanged in release freeze.
- [ ] Workflow unchanged in release freeze.
- [ ] `createPluginFilter` exists exactly once.

## Standalone

- [ ] Launches.
- [ ] UI paints.
- [ ] Meters move.
- [ ] Output opens.
- [ ] Output close/reopen works.
- [ ] Frame does not crash.
- [ ] Export preset dimensions/status are understandable.
- [ ] Frame remains still-PNG/current-frame only.
- [ ] HUD toggles.
- [ ] Fullscreen works.
- [ ] Module/template switching does not crash.
- [ ] Preset reset does not crash.
- [ ] App closes cleanly.

## DAW

- [ ] Ableton test.
- [ ] FL Studio test.
- [ ] Reaper test.
- [ ] Audio pass-through unchanged.
- [ ] UI opens/closes.
- [ ] Output opens.
- [ ] Remove/reload works.

## OBS

- [ ] Output window capture.
- [ ] Resize.
- [ ] Fullscreen capture.
- [ ] Short external recording.

## Docs

- [ ] Private beta README.
- [ ] Release notes.
- [ ] Known issues.
- [ ] Bug bash plan.
- [ ] QA matrix.
- [ ] Tester instructions.
- [ ] Feedback intake.
- [ ] Triage rules.
- [ ] Release checklist.

## Blockers

Do not call v0.1 beta ready if any of these are true:
- App will not launch.
- CI red.
- Artifacts missing.
- Plugin will not scan/load.
- Audio muted/changed.
- Crash on open.
- Output crash.
- `processBlock` changed.
