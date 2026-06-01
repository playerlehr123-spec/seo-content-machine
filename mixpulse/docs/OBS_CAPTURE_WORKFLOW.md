# WaveFrame OBS Capture Workflow

WaveFrame's current creator capture path is the standalone/plugin output window plus OBS Window Capture. This keeps the app focused on live visual output and still PNG frame export while video recording stays outside the plugin.

## Implemented
- Use the `Output` button to open the WaveFrame output window.
- Capture that window in OBS with Window Capture.
- Use the output overlay to confirm the selected visual module, current aspect guide, and still-PNG-only export status.
- Resize the output window for capture tests.
- Use fullscreen output for a simple live capture setup.
- Use `Frame` to save the current output as a still PNG.

## Suggested OBS Setup
1. Open WaveFrame.
2. Click `Output`.
3. In OBS, add `Window Capture`.
4. Select the WaveFrame/MixPulse output window.
5. Crop or transform the source as needed.
6. Record or stream from OBS.

## Aspect Guides
- 9:16 is for reels, shorts, and vertical clips.
- 1:1 is for square posts.
- 4:5 is for feed posts.
- 16:9 is for YouTube, streams, and landscape visualizers.

## Future / TODO
- Built-in video export.
- NDI, Spout, or Syphon.
- Virtual camera output.
- Background render queue.
- Timeline or clip recorder.

## Safety Notes
- OBS capture is a UI workflow only.
- No file I/O is added to `processBlock`.
- Audio remains pass-through and analysis-only.
