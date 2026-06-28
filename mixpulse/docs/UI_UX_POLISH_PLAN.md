# WaveFrame UI/UX Polish Plan

## Current UI Problems

- Global actions, presets, template controls, and utility buttons were crowded into one row.
- The output/preview area did not feel like the main product surface.
- Brand, template, motion, and export concepts were present but hard to scan.
- Metering worked, but the hierarchy between peak/RMS, clip, LUFS placeholder, and true peak placeholder needed more structure.
- Creator/social workflow needed clearer labels without adding video export or risky new engines.

## Target Layout

WaveFrame should read as a creator tool with four stable zones:

- Top header: product name, beta/version status, host/input placeholder, output status, and the core Output, Frame, HUD, Info actions.
- Left meter rail: peak/RMS meters, clip state, LUFS M placeholder/reading, true peak placeholder/reading, and fixed meter ticks.
- Main preview canvas: large visual focus with selected module/template, aspect guide placeholder, safe-area placeholder, export status, OBS note, and video export marked future only.
- Right control panel: grouped Controls, Motion / Audio, Brand, Templates, and Export sections.

## UI/UX Polish Pass 1 Implemented

- Reorganized the editor into header, meter rail, preview canvas, and right-side creator controls.
- Added a visual module selector for the safe module set already present in the visual rack.
- Kept Output, Frame, HUD, Info, Fullscreen, template selection, export preset selection, and preset save/load/reset wired.
- Made WaveFrame branding more prominent while keeping MixPulse as an internal note.
- Made the preview canvas larger and more central with aspect/safe-area guide placeholders.
- Kept export messaging limited to PNG still frames.

## Modular UI Foundation Pass A

- Replaces the static guide-heavy preview with the live audio-reactive renderer.
- Compacts the command bar and creator inspector so signal content dominates.
- Replaces rounded dashboard cards with sharper modular panels and narrow separators.
- Adds live Peak, RMS, LUFS M, and True Peak metric tiles beneath the workspace.
- Introduces an original WaveFrame signal palette built around cyan, magenta, orange, and graphite.
- Applies a dark compact popup/control theme while preserving current workflows.
- Uses MiniMeters-class density and modularity as category inspiration without copying its branding, assets, code, or exact layout.

## Implementation Phases

1. Polish Pass 1: layout hierarchy, grouped controls, larger preview, clearer WaveFrame identity.
2. Polish Pass 2: editable brand fields, safer control widgets for intensity/motion, and refined compact meter spacing.
3. Polish Pass 3: template thumbnails, richer preview rendering in the editor, and improved accessibility/keyboard focus.
4. Future creator lab: template editing, logo import review, animation presets, and video export research.

## Danger Files

- `mixpulse/Source/PluginProcessor.cpp`
- `mixpulse/include/PluginProcessor.h`
- `mixpulse/CMakeLists.txt`
- `.github/workflows/mixpulse-build.yml`

Polish Pass 1 should not need these files.

## Manual Test Checklist

Standalone:

- App launches.
- UI paints cleanly.
- Window resize works at minimum and large sizes.
- Output button opens the output window.
- Frame button exports or reports a safe PNG status.
- HUD toggles.
- Fullscreen works once Output is open.
- Info and Copy Info work.
- Meters still move.
- Module/template switching does not crash.
- App closes cleanly.

DAW:

- Plugin opens.
- UI opens and closes.
- Audio passes through unchanged.
- Meters move.
- Output opens.
- Removing/reloading plugin does not crash.

## Should Wait Until Later

- Editable text fields for artist, track, label, and CTA.
- Real image/logo import.
- Timeline, recorder, MP4/WebM export, or background render engine.
- Shader SDK, NDI, Spout/Syphon, macOS/AU, or cloud/social upload features.
