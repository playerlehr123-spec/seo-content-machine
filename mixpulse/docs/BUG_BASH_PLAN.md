# WaveFrame v0.1 Bug Bash Plan

## QA Levels
- Level 0: CI build and artifact check.
- Level 1: Standalone smoke test.
- Level 2: VST3 DAW smoke test.
- Level 3: Creator workflow test.
- Level 4: OBS workflow test.
- Level 5: Longer stability test.

## Focus Areas
- Standalone launch/close.
- VST3 scan/load/remove/reload.
- Audio pass-through.
- Meters.
- UI controls.
- Output window.
- OBS capture.
- Templates/modules.
- Preset save/load/reset.
- Frame button.
- Crash/freeze cases.
- Artifact packaging.

## Stop Conditions
Stop and file a blocker if app launch, CI artifact creation, plugin loading, audio pass-through, or crash-on-open fails.
