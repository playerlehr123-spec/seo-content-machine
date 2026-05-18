# WaveFrame 4x Feature Workflow

Use 4x development for isolated lanes only. The goal is parallel exploration without creating integration chaos in shared UI, processor, CMake, or workflow files.

## Assigned Lanes
- Bot 1: Analyzer / Metering
- Bot 2: Renderer / Output
- Bot 3: Brand / Templates
- Bot 4: Docs / QA

## Rules
- Do not let all 4 bots edit `PluginEditor.cpp`.
- Do not let all 4 bots edit `PluginProcessor.cpp`.
- Do not let all 4 bots edit CMake.
- Do not let all 4 bots edit workflow YAML.
- Main bot integrates.
- CI decides.
- Feature PRs should be small.
- Each bot should identify its product pillar before starting.
- Prefer docs/scaffold first, then implementation.
- Keep WaveFrame as the user-facing name and MixPulse as the internal codename.
- Do not rename artifacts unless explicitly approved.

## Integration Pattern
1. Assign each bot one lane and a tight file boundary.
2. Let bots produce scaffold, docs, or module PRs.
3. Main bot reviews for overlap with danger files.
4. Main bot integrates one lane at a time.
5. Run CI after each integration.
6. Fix the first CI error only.
7. Merge only when CI is green and manual risk is understood.

## Next Recommended 4x Batch After PR #12 Merge
- Bot 1: Export Presets + Frame Export polish
- Bot 2: Logo Reactor + Brand Layer UI
- Bot 3: Promo Card + Social Template UI
- Bot 4: Meter/HUD polish + DAW smoke docs

## Avoid
- Four bots editing the same UI file.
- Four bots editing processor/audio code.
- Four bots adding `.cpp` files without coordinated CMake updates.
- Four bots changing workflow YAML.
- Large feature dumps without manual artifact validation.
