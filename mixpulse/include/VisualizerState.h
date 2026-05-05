#pragma once
#include <atomic>

enum class VisualizerMode { SpectrumBars, Waveform, Vectorscope, ParticleBurst, Tunnel, Plasma, SpectrogramWaterfall, LogoReactor, TitleCard, HudOverlay };

struct VisualizerState
{
    std::atomic<VisualizerMode> mode { VisualizerMode::SpectrumBars };
    std::atomic<bool> beatSync { true };
    std::atomic<bool> alwaysOnTop { true };
};
