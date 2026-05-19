#include "VisualizerRenderer.h"
#include <cmath>

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
        case VisualizerMode::LogoReactor: return "Logo Reactor";
        case VisualizerMode::TitleCard: return "Text Card";
        case VisualizerMode::HudOverlay: return "HUD Overlay";
    }
    return "Mode";
}

void VisualizerRenderer::render(juce::Graphics& g, juce::Rectangle<int> b, const std::array<float, AudioAnalyzer::spectrumBins>& spectrumData, VisualizerMode mode, float pulse, const VisualRackState& rack, const BrandLayer::CreatorBrandState* brand)
{
    const auto module = (VisualModuleType) rack.selectedModule.load();
    if (mode == VisualizerMode::SpectrumBars && module == VisualModuleType::SpectrumBars) { spectrum.render(g, b, spectrumData, pulse, rack); return; }
    const auto primary = brand != nullptr ? brand->brandPrimaryColor : juce::Colour::fromRGB(32, 218, 255);
    const auto secondary = brand != nullptr ? brand->brandSecondaryColor : juce::Colour::fromRGB(20, 30, 50);
    const auto accent = brand != nullptr ? brand->brandAccentColor : juce::Colour::fromRGB(160, 255, 120);
    const auto artist = brand != nullptr ? brand->artistName : juce::String("Artist Name");
    const auto title = brand != nullptr ? brand->trackTitle : juce::String("Track Title");
    const auto label = brand != nullptr ? brand->labelName : juce::String("WaveFrame");
    const auto cta = brand != nullptr ? brand->callToAction : juce::String("Out Now");
    const auto release = brand != nullptr ? brand->releaseStatusText : juce::String("New Release");
    const auto intensity = rack.visualIntensity.load();
    const auto motion = rack.motionAmount.load();
    const auto pulseAmount = juce::jlimit(0.0f, 1.0f, pulse);

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
        const auto logoSize = (140.0f + 58.0f * pulseAmount) * juce::jmax(0.65f, brand != nullptr ? brand->logoScale : 1.0f);
        g.setColour(primary.withAlpha(0.16f + pulseAmount * 0.24f));
        g.fillEllipse(guide.withSizeKeepingCentre(logoSize + 52.0f, logoSize + 52.0f));
        g.setColour(accent.withAlpha(0.20f + pulseAmount * 0.30f));
        g.drawEllipse(guide.withSizeKeepingCentre(logoSize + 28.0f, logoSize + 28.0f), 2.0f + 3.0f * pulseAmount);
        g.setColour(primary.withAlpha(0.70f));
        g.fillRoundedRectangle(guide.withSizeKeepingCentre(logoSize, logoSize * 0.72f), 18.0f);
        g.setColour(juce::Colours::white.withAlpha(0.7f));
        g.setFont(26.0f + 6.0f * pulseAmount);
        g.drawText(label, guide.toNearestInt(), juce::Justification::centred);
        g.setColour(juce::Colours::white.withAlpha(0.55f));
        g.setFont(13.0f);
        g.drawText(artist + " - " + title, guide.reduced(20.0f).toNearestInt(), juce::Justification::centredBottom);
    }
    else if (module == VisualModuleType::TypePulse)
    {
        auto textArea = guide.reduced(34.0f);
        const auto scale = 1.0f + pulseAmount * 0.18f * motion;
        g.setColour(primary.withAlpha(0.14f + pulseAmount * 0.18f));
        for (int i = 0; i < 5; ++i)
        {
            const auto y = textArea.getY() + (float)i * textArea.getHeight() / 5.0f;
            g.setFont(18.0f + i * 4.0f);
            g.drawText((i % 2 == 0 ? artist : title).toUpperCase(), (int)textArea.getX(), (int)y, (int)textArea.getWidth(), 28, juce::Justification::centred);
        }
        g.setColour(juce::Colours::white.withAlpha(0.88f));
        g.setFont(36.0f * scale);
        g.drawText(title.toUpperCase(), textArea.toNearestInt(), juce::Justification::centred);
        g.setColour(accent.withAlpha(0.82f));
        g.setFont(16.0f);
        g.drawText(cta, textArea.toNearestInt().reduced(8), juce::Justification::centredBottom);
    }
    else if (module == VisualModuleType::TextCard || module == VisualModuleType::PromoCard)
    {
        auto card = guide.reduced(42.0f, 34.0f);
        g.setColour(secondary);
        g.fillRoundedRectangle(card, 12.0f);
        g.setColour(primary.withAlpha(0.38f + pulseAmount * 0.22f));
        g.drawRoundedRectangle(card, 12.0f, 2.0f);
        auto content = card.reduced(24.0f, 20.0f);
        g.setColour(accent);
        g.setFont(14.0f);
        g.drawText(release.toUpperCase(), content.removeFromTop(24).toNearestInt(), juce::Justification::left);
        g.setColour(juce::Colours::white);
        g.setFont(30.0f);
        g.drawText(artist, content.removeFromTop(42).toNearestInt(), juce::Justification::left);
        g.setFont(20.0f);
        g.drawText(title, content.removeFromTop(32).toNearestInt(), juce::Justification::left);
        g.setColour(primary.withAlpha(0.82f));
        auto strip = content.removeFromBottom(42);
        const auto binsToDraw = juce::jmin((int)AudioAnalyzer::spectrumBins, 28);
        const auto barW = juce::jmax(2.0f, strip.getWidth() / (float)binsToDraw);
        for (int i = 0; i < binsToDraw; ++i)
        {
            const auto value = juce::jlimit(0.0f, 1.0f, spectrumData[(size_t)i] * (0.8f + intensity));
            const auto h = 4.0f + value * strip.getHeight();
            g.fillRoundedRectangle(strip.getX() + i * barW, strip.getBottom() - h, barW * 0.62f, h, 2.0f);
        }
        g.setColour(juce::Colours::white.withAlpha(0.72f));
        g.setFont(15.0f);
        g.drawText(label + " / " + cta, content.toNearestInt(), juce::Justification::bottomLeft);
    }
    else if (module == VisualModuleType::Particles || module == VisualModuleType::ParticleBurstPlaceholder)
    {
        auto field = guide.reduced(28.0f);
        const int columns = 11;
        const int rows = 7;
        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < columns; ++x)
            {
                const auto idx = (size_t)((x + y * columns) % (int)AudioAnalyzer::spectrumBins);
                const auto energy = juce::jlimit(0.0f, 1.0f, spectrumData[idx] * 1.5f + pulseAmount * 0.45f);
                const auto spread = 10.0f * motion * pulseAmount;
                const auto px = field.getX() + ((float)x + 0.5f) * field.getWidth() / (float)columns + std::sin((float)y + pulseAmount * 2.0f) * spread;
                const auto py = field.getY() + ((float)y + 0.5f) * field.getHeight() / (float)rows + std::cos((float)x + pulseAmount * 2.0f) * spread;
                const auto size = 3.0f + energy * 12.0f;
                g.setColour(primary.interpolatedWith(accent, energy).withAlpha(0.25f + energy * 0.58f));
                g.fillEllipse(px - size * 0.5f, py - size * 0.5f, size, size);
            }
        }
        g.setColour(juce::Colours::white.withAlpha(0.72f));
        g.setFont(18.0f);
        g.drawText("Particles v1", guide.toNearestInt().reduced(12), juce::Justification::bottomLeft);
    }
    else {
        g.setColour(juce::Colour::fromRGB(34, 211, 238));
        g.drawRoundedRectangle(guide, 8.0f, 1.0f);
        g.setFont(24.0f);
        g.drawText(visualModuleName(module) + " placeholder", b, juce::Justification::centred);
    }

}
