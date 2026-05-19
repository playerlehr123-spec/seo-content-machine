# MixPulse QA Checklist (Windows-first beta)

## Build artifacts
- [ ] `MixPulse-Windows-Beta` downloaded.
- [ ] `MixPulse-Windows-Build-Folder` downloaded.
- [ ] EXE and/or `MixPulse.vst3` present.

## Standalone smoke
- [ ] App launches.
- [ ] UI renders without overlap at default size.
- [ ] Peak/RMS ticks remain `0, -3, -6, -9, -12, -24`.
- [ ] LUFS refs remain `-6, -12, -14, -23`.
- [ ] Clip latch reset works (`R`).
- [ ] Tap tempo works (`T`).
- [ ] Creator Output opens/closes safely.
- [ ] Fullscreen toggle works (`F`, `Esc`).
- [ ] Export Frame works (`S`).

## VST3 smoke (if included)
- [ ] Copied `MixPulse.vst3` to VST3 folder.
- [ ] DAW rescanned plugin list.
- [ ] Plugin loads on audio track.
- [ ] Audio pass-through remains unchanged.
- [ ] Meters/visuals animate.
- [ ] Spectrum responds to voice/music input.
- [ ] Clip latch lights on high input and resets with R.
- [ ] No NaN/inf style display artifacts.

## Product honesty checks
- [ ] No mastering-grade LUFS claims.
- [ ] LUFS S/I shown as placeholders.
- [ ] True Peak labeled/treated as sample-peak placeholder.
- [ ] No public-release-ready language.


## CI smoke test coverage
- Configure/build on Windows.
- Clean beta artifact exists.
- README_INSTALL.txt exists.
- EXE and/or VST3 exists.
- Optional EXE start smoke test is attempted.
- VST3 package structure is printed when present.

Manual testing is still required for UI quality, audio devices, mic/input metering, Frame/HUD/Creator Output behavior, fullscreen flow, DAW VST3 loading, and pass-through verification.


## Frame export QA additions
- Export Current Window PNG.
- Export with Output window open/closed.
- Export while fullscreen toggled.
- Confirm files appear in `Documents/WaveFrame/Exports/` and names are unique over 3 runs.
- For enabled fixed sizes, verify dimensions: 1080x1920, 1080x1080, 1080x1350, 1920x1080.

- [ ] Save DAW project after changing scene/FX/HUD/brand; reopen and verify state recall.
- [ ] Save and load user preset; verify brand text and logo status handling.
- [ ] Reset Default restores base visual/export/HUD state.
- [ ] Loading missing/invalid preset does not crash.
