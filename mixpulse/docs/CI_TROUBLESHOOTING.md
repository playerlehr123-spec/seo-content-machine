# WaveFrame CI Troubleshooting

CI is the source of truth for merge readiness. Fix the first failing error only, rerun, then move to the next failure.

## Artifact Expectations
The Windows build should upload:
- `MixPulse-Windows-Beta`
- `MixPulse-Windows-Build-Folder`

Download `MixPulse-Windows-Beta` for normal private beta testing. Use `MixPulse-Windows-Build-Folder` as a developer/debug fallback.

Artifact names may still say MixPulse while the product is presented as WaveFrame. Do not rename targets, plugin IDs, or artifact names during beta hardening unless a dedicated compatibility pass is planned.

## Reading Failed Runs
- Ignore old red X runs if the latest relevant run for `main`, the PR, or the beta branch is green.
- If the latest run is red, open the first failed job and fix the first real compile, link, packaging, or upload error.
- If artifacts are missing after a green build, check the upload-artifact steps and the build summary before changing code.
- If the VST3 is missing from the beta artifact, inspect the build folder artifact and packaging step output.

## YAML Syntax Error In Workflow Here-String
Symptom: GitHub Actions reports YAML parsing or PowerShell block syntax errors around a here-string.

Fix:
- Avoid PowerShell here-strings in YAML.
- Use an array of strings piped to `Set-Content`.

## `createPluginFilter` Unresolved External
Symptom:

```text
juce_audio_plugin_client_Standalone.obj : error LNK2001: unresolved external symbol createPluginFilter()
```

Fix:
- Add exactly one global `createPluginFilter` implementation in `mixpulse/Source/PluginProcessor.cpp`.
- Confirm `PluginProcessor.cpp` is included in `mixpulse/CMakeLists.txt`.
- The implementation must not be `static` and must not be inside a class or namespace:

```cpp
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MixPulseAudioProcessor();
}
```

## JUCE `DynamicObject::getProperty` Default Overload Error
Symptom: Compile error reports that `getProperty` does not accept a default value argument.

Fix:
- JUCE 7 `getProperty` takes one argument.
- Use a helper such as `getPropertyOrDefault` that checks `hasProperty` before reading.

## Missing `getBuiltInCreatorTemplates`
Symptom: Compile or link error reports missing `getBuiltInCreatorTemplates`.

Fix:
- Include `CreatorTemplate.h`.
- Compile `CreatorTemplate.cpp`.
- Update `mixpulse/CMakeLists.txt` target sources if needed.

## MSBuild Help Target Failure
Symptom: CI fails while trying to print MSBuild help or target information.

Fix:
- Make the debug help target continue-on-error, or remove it.
- Do not let nonessential diagnostic commands fail the workflow.

## New `.cpp` File Added But Not Compiled
Symptom: Link errors appear for functions/classes implemented in a newly added source file.

Fix:
- Add the new `.cpp` file to `target_sources(MixPulse PRIVATE ...)` in `mixpulse/CMakeLists.txt`.
- Rerun configure/build after updating CMake.
