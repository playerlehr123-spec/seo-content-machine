# WaveFrame Creator Tool Layout

## Header

The header carries product identity and global actions.

- WaveFrame name is the strongest visual element.
- Version and beta status remain visible.
- MixPulse appears only as an internal codename note.
- Input/source status is a lightweight host placeholder.
- Output status shows whether the output window is open.
- Primary actions remain Output, Frame, HUD, Info, and Copy Info.

## Meter Rail

The meter rail stays always visible in the normal layout.

- Peak L/R and RMS L/R remain readable.
- Clip indicator is explicit and compact.
- Meter ticks stay fixed at `0`, `-3`, `-6`, `-9`, `-12`, `-24`.
- LUFS M and true peak readings stay descriptive and non-mastering-grade.
- LUFS refs stay `-6`, `-12`, `-14`, `-23`.

## Preview Canvas

The center canvas is the main creator surface.

- Shows the selected visual module.
- Shows the selected creator template.
- Displays aspect-ratio and safe-area guide placeholders.
- Shows current export preset and PNG-only status.
- Marks video export as future only.

## Right Control Panel

The right panel organizes creator workflow into predictable groups.

- Controls: visual module selector, selected template, selected export preset, output status, intensity, motion, beat sync, tap, fullscreen.
- Motion / Audio: beat pulse, bass/mid/high sensitivity, glow, and reactive scale placeholders.
- Brand: artist, track, label, CTA, color/logo placeholders.
- Templates: selected template, use case, recommended module, and status text.
- Export: PNG frame export, aspect/dimensions, OBS capture note, and video future/TODO status.

Interaction polish:

- Intensity is clamped to `0.0` through `2.0`.
- Motion is clamped to `0.0` through `1.0`.
- Selectors validate IDs before applying UI-side state.
- Buttons provide short tooltips and status messages.
- Reset restores default module, template, export, brand, intensity, motion, beat sync, theme, and HUD state.

## Templates Panel

Starter templates:

- Minimal Meter
- Logo Reactor
- Release Announcement
- Label Drop
- Stream Overlay
- Reel Visualizer
- Album Motion

Templates can safely set a visual module, CTA text, release text, and preferred still export preset.

## Export Panel

Current supported export scope:

- Current frame PNG.
- Social still presets for `9:16`, `1:1`, `4:5`, and `16:9`.
- OBS capture note for live output workflows.

Future/TODO only:

- MP4/WebM.
- Timeline.
- Background render queue.
- Social upload/cloud workflows.

## Future Creative Lab

The future creative lab can become a deeper authoring area for templates, brand kits, logo placement, animation presets, and reusable visual recipes. It should remain separate from the audio callback and should not introduce video export until the still-frame workflow is stable.
