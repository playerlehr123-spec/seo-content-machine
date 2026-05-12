# MixPulse Visual Rack Concept

MixPulse Visual Rack is a lightweight, creator-focused visual module scaffold that pairs audio metering with audio-reactive visual presets.

## Implemented now
- Visual rack state model with module selection, FX toggles, modulation source, output preset, and amounts.
- Built-in preset scaffolding (Dark Neon Meter, Stream Overlay, Reel Visualizer, Album Art Background, Minimal Meter).
- Spectrum Bars renderer hooks for Bloom, Mirror, Colorize, Scanlines, and Chromatic Split behavior.
- Safe placeholder rendering for non-Spectrum modules.
- Creator Output Window naming in UI/docs for detached visualizer context.

## Placeholder in this pass
- Waveform, Vectorscope, LogoPulse, TextCard, GradientField advanced visuals.
- Preset persistence (JSON save/load).
- Advanced modulation routing and per-module macro mapping.

## Intentionally not implemented
- Video timeline editing.
- Video import/export (MP4/WebM).
- NDI/Spout/Syphon transport.
- Full shader SDK/node graph.

MixPulse is not a replacement for OBS, Resolume, or full video engines. It is a fast audio-reactive creator visual + meter tool in staged development.

No affiliation with reference products.


## Modulation sources (current scaffold)
- FullAmplitude, BassEnergy, LowMidEnergy, MidEnergy, HighEnergy, BeatPulse, TapTempoBpm, LufsMPlaceholder.

## Creator Output Window
- Intended for OBS window capture, fullscreen visuals, and social preview in beta.

MixPulse is not a timeline editor and has no affiliation with other products.
