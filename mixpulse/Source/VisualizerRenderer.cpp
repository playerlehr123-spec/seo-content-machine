#include "VisualizerRenderer.h"

juce::String VisualizerRenderer::modeName(VisualizerMode mode)
{
    switch (mode)
    {
        case VisualizerMode::SpectrumBars: return "Spectrum Bars";
        case VisualizerMode::Waveform: return "Waveform (TODO)";
        case VisualizerMode::Vectorscope: return "Vectorscope (TODO)";
        case VisualizerMode::ParticleBurst: return "Particle Burst (TODO)";
        case VisualizerMode::Tunnel: return "Tunnel (TODO)";
        case VisualizerMode::Plasma: return "Plasma (TODO)";
        case VisualizerMode::SpectrogramWaterfall: return "Spectrogram (TODO)";
        case VisualizerMode::LogoReactor: return "Logo Reactor (TODO)";
        case VisualizerMode::TitleCard: return "Title Card (TODO)";
        case VisualizerMode::HudOverlay: return "HUD Overlay (TODO)";
    }
    return "Mode";
}

void VisualizerRenderer::render(juce::Graphics& g, juce::Rectangle<int> b, const std::array<float, AudioAnalyzer::spectrumBins>& spectrumData, VisualizerMode mode, float pulse)
{
    if (mode == VisualizerMode::SpectrumBars) { spectrum.render(g, b, spectrumData, pulse); return; }
    g.fillAll(juce::Colour::fromRGB(6, 9, 18));
    g.setColour(juce::Colour::fromRGB(34, 211, 238));
    g.drawRoundedRectangle(b.toFloat().reduced(20.0f), 8.0f, 1.0f);
    g.setFont(24.0f);
    g.drawText(modeName(mode), b, juce::Justification::centred);
}
