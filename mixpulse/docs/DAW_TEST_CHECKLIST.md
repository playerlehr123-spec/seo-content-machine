# WaveFrame / MixPulse DAW Test Checklist

## Windows VST3 install
- Download `MixPulse-Windows-Beta` artifact.
- Extract ZIP and locate `MixPulse.vst3`.
- Copy full folder to `C:\Program Files\Common Files\VST3\`.
- Restart or rescan DAW plugin list.

## Ableton test
- Preferences > Plug-Ins > Rescan.
- Create audio track and load audio/input.
- Insert MixPulse/WaveFrame VST3.
- Confirm audio passes through unchanged.
- Confirm meters move.
- Open Output, toggle Full, click Frame, toggle HUD.
- Close/reopen plugin UI.
- Add second instance and confirm no crash.

## FL Studio test
- Options > Manage plugins > Find installed plugins.
- Load plugin on mixer insert.
- Confirm audio passes through unchanged and meters move.
- Test Output/Full/Frame/HUD.
- Add second instance and confirm no crash.

## Failure notes to capture
- Plugin discovered?
- Plugin name shown as MixPulse or WaveFrame?
- Scan/load crash?
- UI opens?
- Output opens?
- Frame saves?
- HUD toggles?

## Known beta limitations
- Plugin may still appear as MixPulse internally.
- WaveFrame branding may be UI/docs only.
- LUFS placeholder.
- True peak placeholder.
- No video export.
- No macOS/AU.
- Unsigned build.
