# WaveFrame Interaction Control Polish

This pass makes the existing creator controls clearer and safer without adding a new control architecture or changing audio behavior.

## Implemented Now
- Controls section shows selected visual module, template, export preset, output status, beat sync, intensity, and motion.
- Intensity slider range is `0.0` to `2.0`.
- Motion slider range is `0.0` to `1.0`.
- Module, template, and export selectors clamp to safe choices before writing UI-side state.
- Existing buttons have short creator-focused tooltips.
- Output and fullscreen buttons are repeat-safe and do not create duplicate output windows.
- Export preset changes show a clear still-PNG status message.
- Reset restores default module, template, export preset, brand state, intensity, motion, beat sync, theme, and HUD state.
- Keyboard shortcuts include `O` for Output, `S` for still frame, `H` for HUD, `I` for Info, `F` for output fullscreen, and `Esc` to exit output fullscreen.

## Placeholder / Status Only
- Beat pulse amount is displayed as a placeholder.
- Bass/mid/high sensitivity is displayed as a TODO.
- Glow/scale controls remain placeholders.
- Brand text fields are displayed from current Brand Layer state; deeper inline text editing belongs to the Brand Kit pass.

## Button Behavior
- Output opens or focuses the existing output window.
- Frame remains a still PNG workflow only.
- HUD toggles the compact meter view.
- Fullscreen opens output first if needed, then toggles fullscreen.
- Save/Load Preset remain local-only.
- Reset returns to sane defaults and refreshes visible controls.

## Manual Test Checklist
- App launches.
- UI paints cleanly.
- Window resize works.
- Intensity and motion sliders update labels/status.
- Output opens repeatedly without duplicate-window behavior.
- Fullscreen works with and without a previously open output window.
- Frame does not crash and remains still-PNG only.
- HUD toggles.
- Info and Copy Info work.
- Module selector works.
- Template selector updates module/export recommendations.
- Export preset selector updates aspect/status.
- Reset does not crash and restores defaults.
- Meters still move.
- Audio passes through unchanged.

## Future / TODO
- Real beat pulse, glow, and audio sensitivity controls.
- Editable Brand Kit text fields in the right panel.
- Template status tags: implemented, placeholder, future.
- Optional shortcut/help overlay.
