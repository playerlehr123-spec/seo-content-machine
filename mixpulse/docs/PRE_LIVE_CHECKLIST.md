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
