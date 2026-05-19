# WaveFrame DAW Smoke Test Checklist

Use this short checklist for VST3 validation before sharing a beta build externally. Current plugin names may still appear as MixPulse.

## Ableton Live
- Install/scan: Copy `MixPulse.vst3` to `C:\Program Files\Common Files\VST3\`, then use `Preferences > Plug-Ins > Rescan`.
- Plugin load: Insert the plugin on an audio track.
- Audio pass-through: Play audio and confirm it passes through unchanged.
- Meter movement: Confirm meters respond to audio.
- UI open/close: Open and close the plugin UI without a crash.
- Output window: Confirm the Output button opens the output window.
- Remove/reload: Remove the plugin, then load it again.
- Crash check: Confirm no crash, hang, or DAW instability.

## FL Studio
- Install/scan: Copy `MixPulse.vst3` to `C:\Program Files\Common Files\VST3\`, then use `Options > Manage plugins > Find installed plugins`.
- Plugin load: Insert the plugin on a mixer/audio path.
- Audio pass-through: Play audio and confirm it passes through unchanged.
- Meter movement: Confirm meters respond to audio.
- UI open/close: Open and close the plugin UI without a crash.
- Output window: Confirm the Output button opens the output window.
- Remove/reload: Remove the plugin, then load it again.
- Crash check: Confirm no crash, hang, or DAW instability.

## Reaper
- Install/scan: Copy `MixPulse.vst3` to `C:\Program Files\Common Files\VST3\`, then rescan VST plugins in preferences.
- Plugin load: Insert the plugin on an audio track.
- Audio pass-through: Play audio and confirm it passes through unchanged.
- Meter movement: Confirm meters respond to audio.
- UI open/close: Open and close the plugin UI without a crash.
- Output window: Confirm the Output button opens the output window.
- Remove/reload: Remove the plugin, then load it again.
- Crash check: Confirm no crash, hang, or DAW instability.

## Bitwig Optional
- Install/scan: Copy `MixPulse.vst3` to `C:\Program Files\Common Files\VST3\`, then rescan plugins.
- Plugin load: Insert the plugin on an audio track.
- Audio pass-through: Play audio and confirm it passes through unchanged.
- Meter movement: Confirm meters respond to audio.
- UI open/close: Open and close the plugin UI without a crash.
- Output window: Confirm the Output button opens the output window.
- Remove/reload: Remove the plugin, then load it again.
- Crash check: Confirm no crash, hang, or host instability.
