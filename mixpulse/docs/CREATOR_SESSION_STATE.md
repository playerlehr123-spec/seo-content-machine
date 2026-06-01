# WaveFrame Creator Session State

Status: v0.2 Sprint 4 clarifies which pieces of creator state are active in the editor, which pieces are saved locally, and which pieces are future/TODO.

## Current Session Fields

WaveFrame currently keeps these creator-session values in existing editor/processor-side state:

- selected visual module
- selected creator template
- selected export preset/aspect
- Brand Kit text/defaults
- brand color hints
- visual intensity
- motion amount
- bloom/glow amount
- beat sync state
- HUD state
- output window open/closed status

This state stays outside the audio callback. The audio path remains pass-through and analysis-only.

## Reset Defaults

Reset restores:

- Minimal Meter session preset
- Spectrum Bars module
- Current export preset
- default Brand Kit text
- default brand colors
- intensity `0.75`
- motion amount `0.65`
- beat sync on
- HUD off

## Built-in Session Preset Behavior

Selecting a built-in session preset safely composes:

- a creator template
- a recommended visual module
- a recommended export preset
- brand color hints
- visual intensity
- motion amount
- bloom/glow amount

This is a UI-side convenience layer, not a cloud/account preset system.

## Local Brand Preset Behavior

Save/Load Preset currently applies only to Brand Kit JSON:

- text fields
- logo path/placeholder settings
- brand colors

If a local preset is missing or malformed, WaveFrame keeps the current session and shows a failure status.

## Future/TODO

- Full creator-session JSON.
- Preset schema migration.
- File picker save/load.
- Recent preset menu.
- Template-specific editable fields.
- Cloud sync, public sharing, and marketplace features are out of scope.
