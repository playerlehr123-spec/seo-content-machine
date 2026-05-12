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

## Product honesty checks
- [ ] No mastering-grade LUFS claims.
- [ ] LUFS S/I shown as placeholders.
- [ ] True Peak labeled/treated as sample-peak placeholder.
- [ ] No public-release-ready language.
