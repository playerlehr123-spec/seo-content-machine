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
    const auto module = (VisualModuleType) rack.selectedModule.load();
    if (mode == VisualizerMode::SpectrumBars && module == VisualModuleType::SpectrumBars) { spectrum.render(g, b, spectrumData, pulse, rack); return; }
        g.fillAll(juce::Colour::fromRGB(6, 9, 18));
    g.setColour(juce::Colour::fromRGB(16, 30, 44));
    for (int y = b.getY(); y < b.getBottom(); y += 22) g.drawHorizontalLine(y, (float)b.getX(), (float)b.getRight());

    auto guide = b.toFloat().reduced(24.0f);
    const auto preset = (OutputPreset) rack.outputPreset.load();
    float ratio = 0.0f;
    if (preset == OutputPreset::Landscape16x9 || preset == OutputPreset::Thumbnail16x9) ratio = 16.0f / 9.0f;
    else if (preset == OutputPreset::Square1x1) ratio = 1.0f;
    else if (preset == OutputPreset::Portrait9x16) ratio = 9.0f / 16.0f;
    else if (preset == OutputPreset::Portrait4x5) ratio = 4.0f / 5.0f;
    if (ratio > 0.0f)
    {
        float w = guide.getWidth(); float h = w / ratio;
        if (h > guide.getHeight()) { h = guide.getHeight(); w = h * ratio; }
        guide = juce::Rectangle<float>(0,0,w,h).withCentre(guide.getCentre());
        g.setColour(juce::Colours::white.withAlpha(0.12f));
        g.drawRoundedRectangle(guide, 6.0f, 1.0f);
    }

    if (module == VisualModuleType::LogoPulse)
    {
        g.setColour(juce::Colour::fromRGB(34, 211, 238).withAlpha(0.22f + pulse * 0.25f));
        g.fillEllipse(guide.withSizeKeepingCentre(160.0f, 160.0f));
        g.setColour(juce::Colours::white.withAlpha(0.7f));
        g.drawText("Logo layer coming soon", guide.toNearestInt(), juce::Justification::centred);
    }
    else if (module == VisualModuleType::TextCard)
    {
        auto card = guide.reduced(40.0f, 32.0f);
        g.setColour(juce::Colour::fromRGB(14, 18, 30)); g.fillRoundedRectangle(card, 10.0f);
        g.setColour(juce::Colour::fromRGB(32, 218, 255).withAlpha(0.35f + pulse * 0.2f)); g.drawRoundedRectangle(card, 10.0f, 1.5f);
        g.setColour(juce::Colours::white); g.setFont(24.0f); g.drawText("Artist Name", card.removeFromTop(36).toNearestInt(), juce::Justification::left);
        g.setFont(18.0f); g.drawText("Track Title", card.removeFromTop(28).toNearestInt(), juce::Justification::left);
        g.drawText("Out Now", card.removeFromTop(24).toNearestInt(), juce::Justification::left);
        g.setFont(14.0f); g.drawText("Text editing coming soon", card.toNearestInt(), juce::Justification::bottomLeft);
    }
    else {
        g.setColour(juce::Colour::fromRGB(34, 211, 238));
        g.drawRoundedRectangle(guide, 8.0f, 1.0f);
        g.setFont(24.0f);
        g.drawText(visualModuleName(module) + " placeholder", b, juce::Justification::centred);
    }

}
