# WaveFrame Beta Artifact Test Plan

Use this checklist before sharing any Windows beta artifact externally. Current artifact and binary names may still use the internal MixPulse name; WaveFrame is the user-facing product name.

## Artifact Download
1. Go to GitHub Actions for `playerlehr123-spec/seo-content-machine`.
2. Open the latest successful `MixPulse Build` run.
3. Download `MixPulse-Windows-Beta`.
4. Unzip the artifact.
5. Locate `README_INSTALL.txt`.
6. Locate `MixPulse.exe` if present.
7. Locate `MixPulse.vst3` if present.

If older workflow runs show a red X, ignore them unless they are the latest run for the branch or PR being tested. Private beta readiness is based on the latest relevant green run and its artifacts.

## Artifact Names
- `MixPulse-Windows-Beta`: primary tester download.
- `MixPulse-Windows-Build-Folder`: debug fallback for developers.

Artifact, binary, and plugin names may still say MixPulse. WaveFrame is the user-facing product name.

## Standalone Smoke Test
1. Run `MixPulse.exe`.
2. Confirm the app launches.
3. Confirm settings opens.
4. Confirm mic/input can move meters if enabled.
5. Confirm meters move with input/audio.
6. Confirm the Output button opens the output window.
7. Confirm Fullscreen works.
8. Confirm the Frame button does not crash.
9. Confirm the HUD button does not crash.
10. Confirm the theme dropdown works.
11. Confirm the app closes cleanly.

## Audio Safety Test
1. Run audio through the plugin or standalone app if applicable.
2. Confirm audio pass-through is unchanged.
3. Confirm there is no gain, EQ, compression, limiting, saturation, widening, normalization, or other audio effect behavior.
4. Confirm there is no unwanted muting except intentional feedback-loop mute in standalone.

## DAW VST3 Install Test
1. Copy `MixPulse.vst3` to:

```text
C:\Program Files\Common Files\VST3\
```

2. Open Ableton Live.
3. Go to `Preferences > Plug-Ins > Rescan`.
4. Insert the plugin on an audio track.
5. Play audio through the track.
6. Confirm audio passes through unchanged.
7. Confirm meters move.
8. Open and close the plugin UI.
9. Test the Output button.
10. Test Frame.
11. Test HUD.
12. Remove the plugin.
13. Reload the plugin.

## FL Studio Test
1. Open `Options > Manage plugins`.
2. Click `Find installed plugins`.
3. Insert the plugin.
4. Confirm audio passes through unchanged.
5. Confirm meters move.
6. Open and close the plugin UI.
7. Test the Output button.
8. Test Frame.
9. Test HUD.
10. Remove and reload the plugin.
11. Confirm no crash occurs.

## OBS / Content Test
1. Open the Output window.
2. Use OBS Window Capture.
3. Confirm capture works.
4. Confirm fullscreen capture works.
5. Resize the output window.
6. Confirm no crash occurs while resizing.

## Known Limitations
- Unsigned beta.
- Windows warning is expected.
- VST3 is experimental.
- Artifact still uses MixPulse internal naming.
- User-facing product is WaveFrame.
- Video export is not implemented.
- NDI, Spout, and Syphon are not implemented.
- macOS/AU is not enabled.

## If An Artifact Is Missing
1. Confirm the workflow run completed successfully.
2. Confirm the branch or PR is the one intended for testing.
3. Check whether `MixPulse-Windows-Beta` and `MixPulse-Windows-Build-Folder` both appear under run artifacts.
4. If the VST3 is missing inside the beta artifact, inspect the build summary and `MixPulse-Windows-Build-Folder`.
5. Do not share a private beta build until the expected artifact contents are confirmed.

## Pass / Fail Table
| Test | Expected result | Actual result | Pass/fail | Notes |
| --- | --- | --- | --- | --- |
| Artifact download | `MixPulse-Windows-Beta` downloads and unzips |  |  |  |
| README present | `README_INSTALL.txt` is present |  |  |  |
| Standalone launch | `MixPulse.exe` launches if present |  |  |  |
| Settings | Settings opens |  |  |  |
| Input meters | Meters move with mic/input if enabled |  |  |  |
| Audio meters | Meters move with audio |  |  |  |
| Output window | Output button opens output window |  |  |  |
| Fullscreen | Fullscreen works |  |  |  |
| Frame | Frame button does not crash |  |  |  |
| HUD | HUD button does not crash |  |  |  |
| Theme dropdown | Theme dropdown works |  |  |  |
| Clean close | App closes cleanly |  |  |  |
| Audio pass-through | Audio remains unchanged |  |  |  |
| No audio effects | No gain/EQ/compression/limiting behavior |  |  |  |
| Ableton scan | VST3 scans and appears |  |  |  |
| Ableton load | Plugin loads on audio track |  |  |  |
| Ableton pass-through | Audio passes through unchanged |  |  |  |
| Ableton reload | Remove/reload succeeds |  |  |  |
| FL Studio scan | VST3 scans and appears |  |  |  |
| FL Studio load | Plugin loads |  |  |  |
| FL Studio pass-through | Audio passes through unchanged |  |  |  |
| OBS capture | Output window captures in OBS |  |  |  |
| OBS fullscreen | Fullscreen capture works |  |  |  |
| Resize stability | Output resize does not crash |  |  |  |
