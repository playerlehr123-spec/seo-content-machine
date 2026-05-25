# WaveFrame Bug Bash Plan

Use this plan for a focused private beta QA session. WaveFrame is the user-facing name; MixPulse may still appear in artifacts, plugin names, and build output.

## Goals
- Find launch, crash, install, DAW, output, OBS, and audio pass-through blockers before private beta.
- Record reproducible bugs with artifact/run number and environment details.
- Separate product blockers from polish issues.
- Keep testing scoped to current features. Do not test future video export, NDI, Spout/Syphon, shader SDK, virtual camera, cloud upload, telemetry, macOS/AU, or installer flows as if they are implemented.

## QA Levels
| Level | Name | Purpose | Required before private beta? |
| --- | --- | --- | --- |
| Level 0 | CI Build Check | Confirm build and artifacts exist. | Yes |
| Level 1 | Standalone Smoke Test | Confirm app launches and core UI works. | Yes |
| Level 2 | VST3 DAW Smoke Test | Confirm scan/load/pass-through in at least one DAW. | Yes for plugin sharing |
| Level 3 | Creator Workflow Test | Confirm modules/templates/brand/presets/frame flow. | Yes |
| Level 4 | OBS Workflow Test | Confirm Output window capture path. | Yes for motion capture sharing |
| Level 5 | Longer Stability Test | Catch close/reopen, repeated actions, and idle crashes. | Recommended |

## Session Roles
- Driver: runs tests and records exact steps.
- Observer: watches for UI, audio, and output behavior.
- Triage owner: assigns severity and decides blocker status.

One person can cover all roles for a small internal pass.

## Test Order
1. Download the latest approved `MixPulse-Windows-Beta` artifact.
2. Record GitHub Actions run number and commit SHA.
3. Run Level 0 artifact checks.
4. Run Level 1 standalone smoke test.
5. Run Level 3 creator workflow test in standalone.
6. Run Level 4 OBS workflow test.
7. Run Level 2 VST3 DAW smoke tests.
8. Run Level 5 longer stability test if no P0/P1 issue blocks progress.
9. File bugs using severity and QA level.
10. Update `QA_MATRIX.md` and `DAW_TEST_MATRIX.md`.

## Coverage Areas
- Standalone app launch/close.
- VST3 scan/load/remove/reload.
- Audio pass-through.
- Peak/RMS meters and visual activity.
- UI controls and selectors.
- Output window open/close/reopen/fullscreen.
- OBS Window Capture.
- Template/module switching.
- Brand/template/preset save/load/reset.
- Export/Frame button.
- HUD toggle.
- Crash/freeze cases.
- Artifact packaging and README instructions.

## Stop Conditions
Stop broad testing and file a blocker if:
- The app will not launch.
- The plugin will not scan/load in any tested DAW.
- Audio is muted, clipped, processed, or changed unexpectedly.
- CI cannot produce `MixPulse-Windows-Beta`.
- A repeated crash prevents reaching core workflows.

## Reporting Rules
- Every bug needs artifact/run number.
- Every DAW bug needs DAW name/version and plugin format.
- Every audio bug must answer whether pass-through changed.
- Every visual bug should include selected module/template and Output window status.
- Every OBS bug should state whether OBS was involved and how the source was captured.
