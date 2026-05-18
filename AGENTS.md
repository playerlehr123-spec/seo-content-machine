# Agent Instructions

## Project Identity
- User-facing product name: WaveFrame
- Internal codename / CMake target: MixPulse
- Internal folder: `mixpulse/`
- Platform focus: Windows-first beta
- JUCE version target: 7.0.11

## Non-Negotiable Audio Rules
- `processBlock` must not modify valid input audio samples.
- Audio pass-through must remain unchanged.
- Only clear unused output channels.
- No gain, EQ, compression, limiting, saturation, widening, normalization, or audio effects.
- No file IO in `processBlock`.
- No locks in `processBlock`.
- No heap allocation in `processBlock`.
- No GUI calls in `processBlock`.
- No logging spam in `processBlock`.

## Build Rules
- Use JUCE 7.0.11-compatible APIs only.
- Do not assume newer JUCE overloads exist.
- Always update `mixpulse/CMakeLists.txt` when adding new `.cpp` files.
- Keep `createPluginFilter()` present exactly once.
- `createPluginFilter()` must be global namespace, not static, and not inside a class or namespace:

```cpp
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MixPulseAudioProcessor();
}
```

- Keep Windows CI workflow functional.
- Never merge unless CI is green or explicitly approved.

## Danger Files
- `mixpulse/Source/PluginEditor.cpp`
- `mixpulse/include/PluginEditor.h`
- `mixpulse/Source/PluginProcessor.cpp`
- `mixpulse/include/PluginProcessor.h`
- `mixpulse/CMakeLists.txt`
- `.github/workflows/mixpulse-build.yml`

## 4x Bot Rules
- 4x bots should work on isolated modules only.
- Avoid shared UI, processor, and workflow files in 4x tasks.
- Main bot handles integration.
- 4x outputs should become scaffolding or module PRs, not direct main merges.
- For any feature branch, identify the product pillar before implementation.
- Prefer docs/scaffold first, then implementation.
- Use the PR template checklist before final report.
- For any UI change, include screenshot/testing notes.

## Forbidden Unless Explicitly Requested
- Video export
- Video import
- NDI
- Spout/Syphon
- Shader SDK
- Webcam input
- Timeline editor
- macOS/AU
- Installer/signing
- Telemetry
- Cloud/network calls

## Meter Rules
- Peak/RMS ticks stay: `0, -3, -6, -9, -12, -24`
- LUFS refs stay: `-6, -12, -14, -23`
- No subjective mix labels.
- No mastering-grade claims.

## Final Report Required For All Agents
- Files changed
- Build/check result
- CMake changes
- Whether `processBlock` changed
- Whether audio behavior changed
- Risks/TODOs
