# MixPulse Pre-Live Checklist

## Build
- [ ] Windows CI green
- [ ] `MixPulse-Windows-Beta` artifact exists
- [ ] `MixPulse-Windows-Build-Folder` artifact exists
- [ ] `MixPulse.exe` or `MixPulse_Standalone.exe` or `MixPulse.vst3` present

## Standalone
- [ ] App opens
- [ ] Window resizes
- [ ] Meters render
- [ ] Tap tempo works
- [ ] HUD/compact mode does not crash
- [ ] Visual Rack panel renders
- [ ] Creator Output Window opens
- [ ] Fullscreen works
- [ ] Export Frame saves to `Documents/MixPulse/`
- [ ] Close/reopen output window does not crash

## VST3
- [ ] Copy `MixPulse.vst3` to `C:\Program Files\Common Files\VST3\`
- [ ] Rescan in Ableton
- [ ] Rescan in FL Studio
- [ ] Plugin loads
- [ ] Audio passes through unchanged
- [ ] Meters move
- [ ] Output window opens/closes
- [ ] Multiple instances do not crash

## Safety / honesty
- [ ] No claims of final LUFS accuracy
- [ ] No installer yet
- [ ] No signing yet
- [ ] Beta-only language in docs
- [ ] Known limitations listed

## Known limitations
- Unsigned build
- Windows-first CI
- macOS/AU deferred
- LUFS placeholders
- True peak placeholder
- Visual modules beyond Spectrum are placeholders
- No video import/export
- No NDI/Spout/Syphon
- No installer

## Product gate
- [ ] Beta limitations listed
- [ ] No final LUFS claims
- [ ] No installer claims
- [ ] No public launch language until tested


## Private Beta Release Candidate Checklist

### Must pass
- [ ] Windows CI green
- [ ] `MixPulse-Windows-Beta` artifact exists
- [ ] EXE launches
- [ ] Settings opens
- [ ] Mic/input moves meters
- [ ] Output opens and can close/reopen
- [ ] Fullscreen works
- [ ] Frame saves PNG or shows failure status
- [ ] HUD toggles visibly
- [ ] App survives 5-minute idle
- [ ] App survives repeated output open/close test
- [ ] Audio remains pass-through
- [ ] VST3 loads in at least one DAW before plugin sharing

### Acceptable limitations
- Internal build/artifacts still say MixPulse
- WaveFrame branding may be UI/docs only
- LUFS placeholder
- True peak placeholder
- Visual Rack partial
- No video export
- No NDI/Spout/Syphon
- No macOS/AU
- Unsigned Windows build


## CI smoke test coverage
- Configure/build on Windows.
- Clean beta artifact exists.
- README_INSTALL.txt exists.
- EXE and/or VST3 exists.
- Optional EXE start smoke test is attempted.
- VST3 package structure is printed when present.

Manual testing is still required for UI quality, audio devices, mic/input metering, Frame/HUD/Creator Output behavior, fullscreen flow, DAW VST3 loading, and pass-through verification.


## Before sharing VST3
- [ ] VST3 appears in Ableton or FL.
- [ ] Plugin loads on audio track.
- [ ] Audio passes through unchanged.
- [ ] Meters move.
- [ ] UI opens.
- [ ] Output opens or fails gracefully.
- [ ] Frame saves or shows failure.
- [ ] HUD toggles.
- [ ] Two instances do not crash.
- [ ] Removing plugin does not crash DAW.

- [ ] HUD values update without NaN/inf display.
- [ ] Spectrum decays gracefully at idle.


## Export readiness checks
- Verify PNG export writes to `Documents/WaveFrame/Exports/`.
- Verify Current Window export and fixed-size presets in beta UI.
- Confirm messaging states PNG-only and video export future.


## State/preset checks
- [ ] DAW project recall restores scene/module/FX/HUD/export selection.
- [ ] Preset load failure is visible and non-fatal.
- [ ] Missing logo path shows safe status without crash.
