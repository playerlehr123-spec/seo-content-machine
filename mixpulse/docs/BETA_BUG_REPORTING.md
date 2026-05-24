# WaveFrame Beta Bug Reporting

Use this format for private beta bugs so crashes, DAW issues, visual problems, and audio safety issues can be triaged quickly.

## Minimum Report
- Artifact name and GitHub Actions run number.
- Standalone or VST3.
- Windows version.
- DAW name/version if using VST3.
- Audio interface, sample rate, and buffer size if relevant.
- Module and template selected.
- Whether Output window was open.
- Whether OBS was involved.
- Steps to reproduce.
- Expected behavior.
- Actual behavior.
- Screenshot, short video, or log if available.

## Crash Reports
Include:
- What was clicked immediately before the crash.
- Whether it happened on launch, output open, fullscreen, Frame, HUD, module/template switching, preset load/reset, DAW scan, or DAW remove/reload.
- Whether it reproduces after restart.
- Whether it happens in standalone, VST3, or both.

## DAW Issues
Include:
- DAW name and version.
- Whether the plugin scanned.
- Whether the plugin loaded on a track.
- Whether the UI opened and closed.
- Whether meters moved.
- Whether audio passed through unchanged.
- Whether removing/reloading the plugin caused a crash.

## Visual / Output Issues
Include:
- Selected visual module.
- Selected template/export preset.
- Output window open/closed status.
- Fullscreen status.
- OBS Window Capture status if used.
- Screenshot or short capture if possible.

## Audio Pass-Through Issues
Audio safety bugs are highest priority. Include:
- Whether audio became louder, quieter, muted, clipped, delayed, distorted, filtered, compressed, widened, or otherwise changed.
- Whether the issue happens in standalone, VST3, or both.
- DAW track routing and plugin slot position.
- Whether bypassing/removing WaveFrame restores the original audio.

WaveFrame beta builds should remain analysis-only and pass-through for valid audio samples.
