#pragma once
#include <atomic>

enum class VisualizerMode { SpectrumBars, WaveformPlaceholder, VectorscopePlaceholder };

struct VisualizerState
{
    std::atomic<VisualizerMode> mode { VisualizerMode::SpectrumBars };
    std::atomic<bool> beatSync { true };
};
