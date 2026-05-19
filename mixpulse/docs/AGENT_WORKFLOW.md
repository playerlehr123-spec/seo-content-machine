# WaveFrame Agent Workflow

Use these patterns to keep WaveFrame work small, reviewable, and compatible with JUCE 7.0.11.

## Compile-Fix Bot
- Purpose: Fix the first compile, link, or CI error only.
- Allowed files: The smallest file set needed for the reported failure, usually source/header/CMake/workflow files directly named by the error.
- Forbidden files: Unrelated UI, feature, docs, and audio behavior files.
- Final report format: files changed, exact error fixed, build/check result, CMake changes, whether `processBlock` changed, whether audio behavior changed, risks/TODOs.

## Main Integration Bot
- Purpose: Integrate module work, resolve conflicts, keep CI green, and preserve product constraints.
- Allowed files: Integration surfaces, docs, CMake, workflows, and module files needed for the integration.
- Forbidden files: Product behavior changes outside the integration scope, audio processing changes unless explicitly approved.
- Final report format: files changed, integration summary, build/check result, CMake changes, whether `processBlock` changed, whether audio behavior changed, risks/TODOs.

## 4x Feature Bot
- Purpose: Explore or scaffold one isolated module.
- Allowed files: New module files, isolated docs, focused tests or examples, and CMake only if a new `.cpp` must compile.
- Forbidden files: Shared UI/processor/workflow files unless the task explicitly names them.
- Final report format: files changed, module boundary, build/check result, CMake changes, whether `processBlock` changed, whether audio behavior changed, risks/TODOs.

## Docs-Only Bot
- Purpose: Update product, developer, QA, or support documentation.
- Allowed files: Markdown and docs assets only.
- Forbidden files: Source code, CMake, workflows, generated artifacts.
- Final report format: files changed, docs changed, build/check result if run, CMake changes, whether `processBlock` changed, whether audio behavior changed, risks/TODOs.

## UI-Polish Bot
- Purpose: Make small visual/layout fixes without changing audio behavior.
- Allowed files: Focused UI source/header files named in the task and supporting docs if needed.
- Forbidden files: `processBlock`, audio analyzer behavior, CMake/workflows unless needed for compilation.
- Final report format: files changed, UI behavior changed, build/check result, CMake changes, whether `processBlock` changed, whether audio behavior changed, risks/TODOs.

## Danger Files
- `mixpulse/Source/PluginEditor.cpp`
- `mixpulse/include/PluginEditor.h`
- `mixpulse/Source/PluginProcessor.cpp`
- `mixpulse/include/PluginProcessor.h`
- `mixpulse/CMakeLists.txt`
- `.github/workflows/mixpulse-build.yml`

Touch danger files only when the task requires it. Keep changes minimal and explain why in the final report.

## 4x Workflow
Good 4x lanes:
- Analyzer / Metering
- Renderer / Output
- Brand / Templates
- Docs / QA
- Export Presets
- Logo Reactor
- Promo Card
- Tool Suite Docs

Bad 4x lanes:
- Four bots editing `PluginEditor.cpp`
- Four bots editing workflow YAML
- Four bots editing CMake
- Four bots editing `processBlock`

## Suggested Prompt Patterns

### Compile-Fix Bot
```text
Fix only the first WaveFrame CI compile/link error. Do not add features. Keep JUCE 7.0.11 compatibility. Touch only files required by the error. Final report must include files changed, build/check result, CMake changes, whether processBlock changed, whether audio behavior changed, and risks/TODOs.
```

### Main Integration Bot
```text
Integrate this isolated WaveFrame module into PR #12. Preserve MixPulse target names, plugin IDs, and audio pass-through behavior. Update CMake only if new .cpp files must compile. Run the WaveFrame build doctor if JUCE exists locally.
```

### 4x Feature Bot
```text
Work only on this isolated WaveFrame module: <module>. Do not edit shared processor/UI/workflow files unless explicitly required. Produce scaffolding or a module PR, not a direct main merge.
```

### Docs-Only Bot
```text
Update WaveFrame docs only. Do not edit source code, CMake, workflows, or generated artifacts. Keep MixPulse as the internal codename and WaveFrame as the user-facing product name.
```

### UI-Polish Bot
```text
Make a focused WaveFrame UI polish change in the named UI files only. Do not change audio behavior, processBlock, CMake, or workflows. Keep meter refs and labels within the established rules.
```
