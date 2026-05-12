#include "VisualRack.h"
std::array<VisualRackPreset, 5> getBuiltInVisualRackPresets()
{
    return {{
        {"Dark Neon Meter", VisualModuleType::SpectrumBars, ModSource::FullAmplitude, OutputPreset::Landscape16x9, true, true, true, false, false},
        {"Stream Overlay", VisualModuleType::SpectrumBars, ModSource::BeatPulse, OutputPreset::Landscape16x9, true, true, true, true, false},
        {"Reel Visualizer", VisualModuleType::SpectrumBars, ModSource::BeatPulse, OutputPreset::Portrait9x16, true, true, true, false, true},
        {"Album Art Background", VisualModuleType::GradientField, ModSource::FullAmplitude, OutputPreset::Square1x1, true, true, true, false, false},
        {"Minimal Meter", VisualModuleType::SpectrumBars, ModSource::FullAmplitude, OutputPreset::Free, false, true, false, false, false}
    }};
}
