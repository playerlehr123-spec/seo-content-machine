#include "VisualizerRenderer.h"

juce::String VisualizerRenderer::modeName(VisualizerMode mode)
{
    switch (mode)
    {
        case VisualizerMode::SpectrumBars: return "Spectrum Bars";
        case VisualizerMode::Waveform: return "Waveform";
        case VisualizerMode::Vectorscope: return "Vectorscope";
        case VisualizerMode::ParticleBurst: return "Particle Burst";
        case VisualizerMode::Tunnel: return "Tunnel";
        case VisualizerMode::Plasma: return "Plasma";
        case VisualizerMode::SpectrogramWaterfall: return "Spectrogram";
        case VisualizerMode::LogoReactor: return "Logo Pulse";
        case VisualizerMode::TitleCard: return "Text Card";
        case VisualizerMode::HudOverlay: return "HUD Overlay";
    }
    return "Mode";
}

void VisualizerRenderer::render(juce::Graphics& g, juce::Rectangle<int> b, const std::array<float, AudioAnalyzer::spectrumBins>& spectrumData, VisualizerMode mode, float pulse, const VisualRackState& rack)
{
    if (mode == VisualizerMode::SpectrumBars && rack.selectedModule.load() == (int)VisualModuleType::SpectrumBars) { spectrum.render(g, b, spectrumData, pulse, rack); return; }
    g.fillAll(juce::Colour::fromRGB(6, 9, 18));
    g.setColour(juce::Colour::fromRGB(34, 211, 238));
    g.drawRoundedRectangle(b.toFloat().reduced(20.0f), 8.0f, 1.0f);
    g.setFont(24.0f);
    g.drawText(modeName((VisualizerMode)rack.selectedModule.load()) + " placeholder", b, juce::Justification::centred);
}
