# WaveFrame Release Checklist

Use this checklist before sharing a WaveFrame private beta build. Current artifact names may still use the MixPulse internal codename.

## Required Checks
- [ ] Main branch CI is green.
- [ ] Latest PR CI is green.
- [ ] `MixPulse-Windows-Beta` artifact downloaded.
- [ ] `MixPulse-Windows-Build-Folder` artifact available for debugging.
- [ ] Artifact upload names are unchanged.
- [ ] Standalone EXE exists if expected for the build.
- [ ] VST3 exists if expected for the build.
- [ ] `README_INSTALL.txt` checked.
- [ ] `mixpulse/docs/PRIVATE_BETA_GUIDE.md` checked.
- [ ] `mixpulse/docs/KNOWN_ISSUES.md` checked.
- [ ] `mixpulse/docs/BETA_BUG_REPORTING.md` checked.
- [ ] Standalone smoke test completed.
- [ ] VST3 DAW test completed.
- [ ] OBS capture test completed.
- [ ] No audio behavior changes.
- [ ] `processBlock` pass-through behavior unchanged.
- [ ] Known limitations listed.
- [ ] Version/tag decision made.
- [ ] Do not share externally until manual DAW test passes.

## Standalone Smoke Test
- [ ] App launches.
- [ ] Settings opens.
- [ ] Meters move with input/audio.
- [ ] Output window opens.
- [ ] Output close/reopen works.
- [ ] Fullscreen works.
- [ ] Frame does not crash.
- [ ] HUD toggles.
- [ ] Module/template switching does not crash.
- [ ] Preset reset works.
- [ ] App closes cleanly.

## VST3 DAW Test
- [ ] VST3 copied to `C:\Program Files\Common Files\VST3\`.
- [ ] Ableton Live scans and loads the plugin.
- [ ] FL Studio scans and loads the plugin.
- [ ] Reaper scans and loads the plugin.
- [ ] Plugin loads on an audio track.
- [ ] Audio pass-through is unchanged.
- [ ] Meters move.
- [ ] UI opens and closes.
- [ ] Output window opens.
- [ ] Plugin can be removed and reloaded.
- [ ] No crash/freeze observed.

## OBS Capture Test
- [ ] Output window captured in OBS Window Capture.
- [ ] Fullscreen capture workflow works.
- [ ] Aspect guide/status text is understandable.
- [ ] Resizing the output window does not crash.
- [ ] Short clip can be recorded externally in OBS.

## Blocking Issues
- [ ] App does not launch.
- [ ] Plugin does not scan.
- [ ] Audio is muted or changed unexpectedly.
- [ ] `processBlock` modifies valid audio samples.
- [ ] UI crashes on load.
- [ ] Output window crashes.
- [ ] CI artifact is missing.

## Known Limitations To Confirm
- [ ] Unsigned beta.
- [ ] Windows warning expected.
- [ ] VST3 experimental.
- [ ] Artifact may still use MixPulse naming.
- [ ] Video export not implemented.
- [ ] NDI/Spout/Syphon not implemented.
- [ ] macOS/AU not enabled.
- [ ] No installer or auto-update.
