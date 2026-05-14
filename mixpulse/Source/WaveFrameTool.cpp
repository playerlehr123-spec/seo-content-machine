#include "WaveFrameTool.h"

const std::vector<WaveFrameTool>& getBuiltInWaveFrameTools()
{
    static const std::vector<WaveFrameTool> tools {
        { "Meter", "meter", "Meter", "Compact metering utility", WaveFrameToolStatus::Active, true, true, false, false },
        { "Spectrum Bars", "spectrum-bars", "React", "Audio-reactive spectrum bars", WaveFrameToolStatus::Active, true, true, false, false },
        { "Logo Reactor", "logo-reactor", "Brand", "Audio-reactive logo module", WaveFrameToolStatus::Beta, true, true, false, false },
        { "Promo Card", "promo-card", "Templates", "Release announcement card", WaveFrameToolStatus::Beta, true, true, false, false },
        { "Particles", "particles", "React", "Particle motion module", WaveFrameToolStatus::Planned, true, true, false, true },
        { "Pixelator", "pixelator", "React", "Pixel and halftone module", WaveFrameToolStatus::Planned, true, true, true, true },
        { "Type Pulse", "type-pulse", "React", "Text pulse generator", WaveFrameToolStatus::Planned, true, true, true, true },
        { "GeoSync", "geosync", "React", "Geometric modulation module", WaveFrameToolStatus::Planned, true, true, true, true },
        { "Halftone", "halftone", "React", "Halftone stylization module", WaveFrameToolStatus::Planned, true, true, true, true },
        { "Stream Overlay", "stream-overlay", "Templates", "OBS overlay module", WaveFrameToolStatus::Planned, true, true, false, true },
        { "Album Motion", "album-motion", "Templates", "Album art motion concept", WaveFrameToolStatus::Planned, true, true, false, true },
        { "Reel Visualizer", "reel-visualizer", "Templates", "Short-form visual template", WaveFrameToolStatus::Planned, true, true, false, true },
        { "Image to Audio-Reactive Visual", "image-audio-reactive", "Research", "Image-reactive pipeline concept", WaveFrameToolStatus::Research, true, false, true, true },
        { "Shader Tools", "shader-tools", "Research", "Shader-based effects research", WaveFrameToolStatus::Research, true, false, true, true }
    };
    return tools;
}
