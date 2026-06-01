# WaveFrame v0.1 Private Beta RC Checklist

## CI
- [ ] Main branch is green.
- [ ] Release candidate PR is green.
- [ ] `MixPulse-Windows-Beta` artifact uploaded.
- [ ] `MixPulse-Windows-Build-Folder` artifact uploaded.
- [ ] `README_INSTALL.txt` present in beta artifact.
- [ ] Standalone EXE present if expected.
- [ ] VST3 bundle present if expected.

## Standalone
- [ ] App launches.
- [ ] UI paints cleanly.
- [ ] Meters move.
- [ ] Output opens.
- [ ] Output close/reopen works.
- [ ] Fullscreen works.
- [ ] HUD toggles.
- [ ] Frame does not crash.
- [ ] Module switching does not crash.
- [ ] Template switching does not crash.
- [ ] Preset reset does not crash.
- [ ] App closes cleanly.

## DAW
- [ ] Ableton scans/loads plugin.
- [ ] FL Studio scans/loads plugin.
- [ ] Reaper scans/loads plugin.
- [ ] Audio pass-through is unchanged.
- [ ] Meters move.
- [ ] UI opens/closes.
- [ ] Output opens.
- [ ] Remove/reload does not crash.

## OBS
- [ ] Output window captures in OBS.
- [ ] Resize capture works.
- [ ] Fullscreen capture works.
- [ ] Short external test clip records.

## Docs
- [ ] `RELEASE_NOTES_v0.1.md` exists.
- [ ] `PRIVATE_BETA_README.md` exists.
- [ ] `PRIVATE_BETA_GUIDE.md` exists.
- [ ] `KNOWN_ISSUES.md` exists.
- [ ] `QA_MATRIX.md` exists.
- [ ] Bug report template asks for artifact/run and repro details.
- [ ] Tester instructions exist.

## Blockers
- [ ] App will not launch.
- [ ] CI red.
- [ ] Artifacts missing.
- [ ] Plugin will not scan.
- [ ] Audio muted/changed unexpectedly.
- [ ] Crash on open.
- [ ] Output crash.
- [ ] `processBlock` changed.

Any checked blocker item means v0.1 is not ready to share.
