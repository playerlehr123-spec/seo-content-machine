# WaveFrame Development Workflow

WaveFrame is the user-facing product name. MixPulse is the internal codename, CMake target, and current artifact name.

## Branch Strategy
- `main` is stable.
- PR #12 and integration branches are active WaveFrame work.
- 4x branches are module experiments.
- Never merge directly to `main` until CI is green.
- Use small PRs.
- Fix compile errors before adding features.
- Main bot owns integration.
- 4x bots own isolated modules.
- CI is the source of truth.
- Artifacts must be tested manually before sharing.
- Current artifact names may still say MixPulse.

## Recommended Loop
1. Make an isolated change.
2. Update `mixpulse/CMakeLists.txt` if new `.cpp` files were added.
3. Run `scripts/check_waveframe.ps1` if local JUCE exists.
4. Push the PR.
5. Wait for GitHub Actions.
6. Fix the first error only.
7. Download the artifact.
8. Manual smoke test the standalone app and any relevant VST3 output.
9. Merge only when green.

## Local Build Doctor
Use the build doctor when JUCE already exists locally:

```powershell
scripts/check_waveframe.ps1 -JuceDir C:/path/to/JUCE
```

The script does not download JUCE. It checks the local CMake project, configures Windows-first targets, builds standalone first, falls back to `ALL_BUILD`, and prints discovered EXE/VST3 artifacts.

## Manual Smoke Test
- Launch the standalone artifact.
- Confirm input/metering works.
- Confirm audio pass-through is unchanged.
- Confirm creator output windows still open.
- Confirm no unexpected file/network behavior occurs.

## Integration Notes
- Treat Windows CI as the merge gate.
- Keep product feature work separate from compile fixes.
- Keep WaveFrame user-facing language in docs and user-visible surfaces.
- Keep MixPulse internal target, IDs, and current artifacts stable unless explicitly approved.
