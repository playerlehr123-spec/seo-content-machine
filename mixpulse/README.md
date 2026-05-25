# WaveFrame

WaveFrame is a Windows-first VST + standalone creative tool for turning audio into polished, branded social content.

It combines:
- compact audio metering
- audio-reactive visual output
- creator templates
- branded promo layouts
- social export workflows

Current internal codename/build target: **MixPulse**

Current status:
- Windows-first beta foundation
- standalone and VST3 scaffolding
- metering/output foundation
- visual rack foundation
- creator/template roadmap
- not public release ready

## Private Beta Feedback

Feedback intake and triage docs:
- `docs/BETA_FEEDBACK_INTAKE.md`
- `docs/FEEDBACK_TRIAGE_RULES.md`
- `docs/BETA_FEEDBACK_TRACKER.md`
- `docs/BETA_BUG_REPORTING.md`
- `docs/FIX_SPRINT_WORKFLOW.md`
- `docs/GITHUB_LABELS.md`
- `docs/BETA_TESTER_MESSAGE_TEMPLATE.md`

Use these docs to classify P0/P1 blockers, route feature requests to roadmap/TODO, and keep private beta fix sprints focused.

# WaveFrame Phase 1.5 / Phase 2 Foundation

## Implemented
- Analysis-only pass-through processing (no gain/effects; extra output channels cleared only for safety)
- Peak/RMS meter system with dB ticks at `0, -3, -6, -9, -12, -24`
- LUFS panel with placeholder behavior (`LUFS S/I = --.-`)
- Integrated LUFS ref bar with neutral refs: `-6, -12, -14, -23`
- Spectrum Bars visualizer (primary implemented mode)
- Tap tempo + beat sync skeleton
- Screenshot export to `Documents/WaveFrame/`

## Placeholder / not implemented
- Full BS.1770 LUFS pipeline
- Oversampled true peak
- Auto BPM detection
- Non-spectrum visualizer modes (placeholders)
- Video import/export (MP4/WebM)
- NDI/Spout/Syphon transport
- Installer packaging / code signing

## Local build
### macOS (local-only, CI deferred)
```bash
cd mixpulse
cmake -S . -B build -DJUCE_DIR=/absolute/path/to/JUCE
cmake --build build --config Release
```

### Windows
```powershell
cd mixpulse
cmake -S . -B build -DJUCE_DIR=C:/path/to/JUCE
cmake --build build --config Release
```

### Local build doctor
If JUCE already exists locally, run the WaveFrame build doctor from the repo root:

```powershell
scripts/check_waveframe.ps1 -JuceDir C:/path/to/JUCE
```

The script configures the MixPulse project with Windows-first beta flags, builds the standalone target first, falls back to `ALL_BUILD` if needed, and prints discovered EXE/VST3 artifacts.

## Current CI status
- Windows-only CI is active.
- The immediate goal is to produce a testable standalone EXE and/or VST3 artifact from CI.
- macOS/AU are deferred; Windows artifact stability is prioritized first.
- Full build folder artifact is uploaded for debugging.
- Search downloaded artifacts for:
  - `MixPulse.exe`
  - `MixPulse_Standalone.exe`
  - `MixPulse.vst3`

## CI workflow
Workflow: `.github/workflows/mixpulse-build.yml`
- Runs on: `pull_request`, `workflow_dispatch`
- Builds on: `windows-latest` (temporary standalone-first scope)
- Uses pinned JUCE ref `7.0.11` (with `master` fallback)
- Windows builds: Standalone + VST3 attempt (`MIXPULSE_BUILD_VST3=ON`, `MIXPULSE_BUILD_STANDALONE=ON`, `MIXPULSE_BUILD_AU=OFF`)
- Uploads artifacts:
  - `MixPulse-Windows-Beta`
  - `MixPulse-Windows-Build-Folder`

## Expected output locations
Typical JUCE outputs:
- Windows Standalone: `mixpulse/build/MixPulse_artefacts/Release/Standalone/MixPulse.exe` (or `MixPulse_Standalone.exe` depending on generator/output layout)

## Install paths
- Windows standalone install is not automatic in CI artifacts; run the EXE directly from the extracted artifact output folder.

## QA checklist
See `mixpulse/docs/QA_CHECKLIST.md`.

## Known limitations
- LUFS refs are technical references only (not targets/recommendations).
- LUFS M is placeholder approximation.
- LUFS S/I are unavailable placeholders.
- True Peak is sample-peak placeholder.
- Builds are unsigned.


## Failure fix note
- CI failure fixed by updating the JUCE pin to `7.0.11` and normalizing Windows `JUCE_DIR` to use forward slashes (`${{ github.workspace }}/_deps/JUCE`) to avoid path parsing/configure errors.


## If CI fails
- First likely failure fixed in this pass: JUCE ref checkout/path robustness in workflow.
- Workflow now falls back to JUCE `master` if tag `7.0.11` is unavailable in the runner checkout path.
- Packaging now discovers artifacts dynamically instead of relying only on one hardcoded output path.


## Beta tester docs
- Install guide: `mixpulse/docs/BETA_INSTALL.md`
- Beta artifact test plan: `mixpulse/docs/BETA_ARTIFACT_TEST_PLAN.md`
- DAW smoke test checklist: `mixpulse/docs/DAW_SMOKE_TEST_CHECKLIST.md`
- QA checklist: `mixpulse/docs/QA_CHECKLIST.md`
- Roadmap: `mixpulse/docs/ROADMAP.md`

## CI status (important)
- This local environment cannot directly verify the latest remote GitHub Actions result.
- Use the latest `MixPulse Build` run in Actions as source of truth for pass/fail and artifact availability.
- Artifacts expected on success:
  - `MixPulse-Windows-Beta`
  - `MixPulse-Windows-Build-Folder`

## CI scope (temporary)
- GitHub Actions currently runs on **Windows only**.
- CI flags currently used:
  - `MIXPULSE_BUILD_VST3=ON`
  - `MIXPULSE_BUILD_STANDALONE=ON`
  - `MIXPULSE_BUILD_AU=OFF`
- Standalone and VST3 artifacts are both attempted; either is testable output in beta packaging.

- Visual Rack concept: `mixpulse/docs/VISUAL_RACK_CONCEPT.md`

## CI note
Current CI is intentionally **Windows-first**. Standalone remains the gating artifact, while VST3 is re-enabled experimentally; macOS will be restored later.


## Pre-live checklist
- See `mixpulse/docs/PRE_LIVE_CHECKLIST.md`.
- Visual Rack concept: `mixpulse/docs/VISUAL_RACK_CONCEPT.md`.


## Current beta focus
- Analysis-only pass-through
- Compact meter / HUD direction
- Peak/RMS meter
- Placeholder LUFS panel
- Spectrum visualizer
- Visual Rack scaffold
- Creator Output Window
- Export Frame screenshot
- Windows-first beta build

## Future direction
- VST3/macOS expansion after standalone artifact stability
- Logo/image layer
- Export presets
- Video capture/export investigation
- Spout/Syphon/NDI investigation
- True LUFS / true peak implementation

## Beta honesty
- Not mastering-grade yet
- Not a video timeline editor yet
- Not a finished public release yet


## Local validation status
- Standalone has launched in local Windows testing.
- Mic/input metering has worked in local Windows testing.
- Creator Output has opened in local Windows testing.
- Fullscreen has worked in local Windows testing.
- Frame/HUD should be re-tested after each UI pass.
- VST3 still needs DAW validation before plugin sharing.


## Docs index
- `mixpulse/docs/DEVELOPMENT_WORKFLOW.md`
- `mixpulse/docs/AGENT_WORKFLOW.md`
- `mixpulse/docs/CI_TROUBLESHOOTING.md`
- `mixpulse/docs/BETA_ARTIFACT_TEST_PLAN.md`
- `mixpulse/docs/DAW_SMOKE_TEST_CHECKLIST.md`
- `mixpulse/docs/SOCIAL_CONTENT_MODULES.md`
- `mixpulse/docs/UI_DIRECTION.md`
- `mixpulse/docs/REQUEST_TOOL_WORKFLOW.md`
- `mixpulse/docs/INSPIRATION_WALL.md`
- `mixpulse/docs/DESIGN_SYSTEM.md`
- `mixpulse/docs/SOCIAL_EXPORT_WORKFLOW.md`
- `mixpulse/docs/TEMPLATE_CLUB.md`
- `mixpulse/docs/TOOL_SUITE_ROADMAP.md`
- `mixpulse/docs/PRODUCT_VISION.md`
- `mixpulse/docs/BETA_INSTALL.md`
- `mixpulse/docs/QA_CHECKLIST.md`
- `mixpulse/docs/DAW_TEST_CHECKLIST.md`
- `mixpulse/docs/PRIVATE_BETA_TEST_SCRIPT.md`
- `mixpulse/docs/BUG_REPORT_TEMPLATE.md`
- `mixpulse/docs/OBS_CAPTURE_GUIDE.md`
- `mixpulse/docs/VISUAL_RACK_CONCEPT.md`
- `mixpulse/docs/COMPETITIVE_FEATURE_MAP.md`
- `mixpulse/docs/ROADMAP.md`
- `mixpulse/docs/PRE_LIVE_CHECKLIST.md`
- `mixpulse/docs/REFERENCE_FEATURE_MAP.md`
- `mixpulse/docs/ARCHITECTURE_FUTURE.md`
- `mixpulse/docs/FEATURE_BACKLOG.md`
- `mixpulse/docs/BRAND_LAYER.md`
- `mixpulse/docs/CREATOR_TEMPLATES.md`

## Privacy note
- WaveFrame does not send analytics or telemetry.
- Copy Info copies local debug text to clipboard only when clicked.
- Frame export saves locally to `Documents/WaveFrame/`.
- No network upload is performed by WaveFrame.


## WaveFrame Direction
WaveFrame is being built as a compact meter + audio-reactive visual rack + creator output tool.

**Current focus**
- Windows beta stability
- UI polish
- HUD/Frame fixes
- VST3 testing readiness
- Visual Rack scaffold stability

**Future direction**
- Logo Reactor
- Release Promo Card
- Mod Matrix Lite
- Export presets
- Recording/export investigation
- Pro I/O research


## Export presets (beta)
- Export presets: Current, Reel (9:16), Square (1:1), Feed (4:5), Thumb (16:9).
- PNG exports save to `Documents/WaveFrame/Exports/`.
- Current Window and fixed-size PNG exports are beta; video export is future work.
- OBS is recommended for motion capture; no built-in video export yet.

- `mixpulse/docs/STATE_AND_PRESETS.md`

## State + preset persistence (beta)
- DAW/plugin state now serializes core visual/export/HUD/brand metadata for project recall.
- User preset save/load currently targets local Brand Layer JSON foundation.
- Preset/state persistence is local-only and does not alter audio processing.
