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
3. Confirm the output overlay shows WaveFrame, OBS capture readiness, module, aspect, and still-PNG-only status.
4. Confirm capture works.
5. Confirm fullscreen capture works.
6. Resize the output window.
7. Confirm no crash occurs while resizing.
8. Click Frame and confirm a still PNG is saved or a clear failure status is shown.

## Known Limitations
- Unsigned beta.
- Windows warning is expected.
- VST3 is experimental.
- Artifact still uses MixPulse internal naming.
- User-facing product is WaveFrame.
- Video export is not implemented.
- NDI, Spout, and Syphon are not implemented.
- macOS/AU is not enabled.

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
| OBS status overlay | Output overlay shows module/aspect/still PNG status |  |  |  |
| OBS fullscreen | Fullscreen capture works |  |  |  |
| Resize stability | Output resize does not crash |  |  |  |
