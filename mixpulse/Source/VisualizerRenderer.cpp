#include "VisualizerRenderer.h"
#include <cmath>

namespace
{
float averageBins(const std::array<float, AudioAnalyzer::spectrumBins>& spectrumData, int start, int end)
{
    start = juce::jlimit(0, (int)AudioAnalyzer::spectrumBins - 1, start);
    end = juce::jlimit(start + 1, (int)AudioAnalyzer::spectrumBins, end);

    float sum = 0.0f;
    for (int i = start; i < end; ++i)
        sum += spectrumData[(size_t)i];

    return juce::jlimit(0.0f, 1.0f, sum / (float)(end - start));
}

juce::Point<float> logoCentreForMode(juce::Rectangle<float> guide, int mode)
{
    const auto inset = juce::jmin(guide.getWidth(), guide.getHeight()) * 0.18f;
    switch ((BrandLayer::LogoPositionMode)mode)
    {
        case BrandLayer::LogoPositionMode::CornerTopLeft: return { guide.getX() + inset, guide.getY() + inset };
        case BrandLayer::LogoPositionMode::CornerTopRight: return { guide.getRight() - inset, guide.getY() + inset };
        case BrandLayer::LogoPositionMode::CornerBottomLeft: return { guide.getX() + inset, guide.getBottom() - inset };
        case BrandLayer::LogoPositionMode::CornerBottomRight: return { guide.getRight() - inset, guide.getBottom() - inset };
        case BrandLayer::LogoPositionMode::Watermark: return { guide.getRight() - inset, guide.getBottom() - inset };
        case BrandLayer::LogoPositionMode::Center:
        default: return guide.getCentre();
    }
}
}

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
    const auto module = (VisualModuleType) sanitizeVisualModuleIndex(rack.selectedModule.load());
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
    const auto bass = averageBins(spectrumData, 0, 10);
    const auto mids = averageBins(spectrumData, 10, 34);
    const auto highs = averageBins(spectrumData, 34, (int)AudioAnalyzer::spectrumBins);
    const auto energy = juce::jlimit(0.0f, 1.0f, bass * 0.45f + mids * 0.35f + highs * 0.20f + pulseAmount * 0.25f);

    g.fillAll(juce::Colour::fromRGB(6, 9, 18));
    g.setColour(juce::Colour::fromRGB(16, 30, 44));
    for (int y = b.getY(); y < b.getBottom(); y += 22) g.drawHorizontalLine(y, (float)b.getX(), (float)b.getRight());

    auto guide = b.toFloat().reduced(24.0f);
    const auto preset = (OutputPreset) sanitizeOutputPresetIndex(rack.outputPreset.load());
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
        const auto placementMode = brand != nullptr ? brand->logoPositionMode : (int)BrandLayer::LogoPositionMode::Center;
        const auto centre = logoCentreForMode(guide, placementMode);
        const auto scale = juce::jmax(0.65f, brand != nullptr ? brand->logoScale : 1.0f);
        const auto opacity = juce::jlimit(0.2f, 1.0f, brand != nullptr ? brand->logoOpacity : 0.85f);
        const auto logoSize = (118.0f + 74.0f * energy) * scale;
        const auto mark = juce::Rectangle<float>(logoSize, logoSize * 0.72f).withCentre(centre);

        g.setColour(secondary.darker(0.6f).withAlpha(0.78f));
        g.fillRoundedRectangle(guide.reduced(18.0f), 18.0f);
        g.setColour(primary.withAlpha(0.10f + energy * 0.20f));
        g.fillEllipse(mark.withSizeKeepingCentre(logoSize + 84.0f, logoSize + 84.0f));
        g.setColour(accent.withAlpha(0.18f + pulseAmount * 0.34f));
        g.drawEllipse(mark.withSizeKeepingCentre(logoSize + 44.0f, logoSize + 44.0f), 2.0f + 3.0f * pulseAmount);
        g.setColour(primary.withAlpha((0.55f + energy * 0.28f) * opacity));
        g.fillRoundedRectangle(mark, 20.0f);
        g.setColour(accent.withAlpha(0.45f + pulseAmount * 0.35f));
        g.drawRoundedRectangle(mark.reduced(7.0f), 15.0f, 1.4f + pulseAmount * 1.4f);
        g.setColour(juce::Colours::white.withAlpha(0.82f * opacity));
        g.setFont(juce::Font(28.0f + 12.0f * energy, juce::Font::bold));
        g.drawText(label.substring(0, 18), mark.toNearestInt().reduced(10), juce::Justification::centred);

        auto lower = guide.reduced(28.0f).removeFromBottom(70.0f);
        g.setColour(juce::Colours::white.withAlpha(0.55f));
        g.setFont(13.0f + 2.0f * pulseAmount);
        g.drawText(artist.toUpperCase(), lower.removeFromTop(24.0f).toNearestInt(), juce::Justification::centred);
        g.setColour(juce::Colours::white.withAlpha(0.72f));
        g.setFont(17.0f);
        g.drawText(title, lower.removeFromTop(24.0f).toNearestInt(), juce::Justification::centred);
        g.setColour(accent.withAlpha(0.78f));
        g.setFont(12.0f);
        g.drawText("Logo import TODO / beat-reactive brand mark", lower.toNearestInt(), juce::Justification::centred);
    }
    else if (module == VisualModuleType::TypePulse)
    {
        auto textArea = guide.reduced(34.0f);
        const auto scale = 1.0f + (pulseAmount * 0.16f + energy * 0.10f) * motion;
        const auto repeated = (artist + "  /  " + title + "  /  " + cta).toUpperCase();

        for (int i = 0; i < 7; ++i)
        {
            const auto y = textArea.getY() + (float)i * textArea.getHeight() / 7.0f;
            const auto alpha = 0.08f + 0.10f * pulseAmount + 0.04f * (float)(i % 2);
            g.setColour((i % 2 == 0 ? primary : accent).withAlpha(alpha));
            g.setFont(15.0f + (float)(i % 3) * 3.0f);
            g.drawText(repeated, (int)textArea.getX(), (int)y, (int)textArea.getWidth(), 28, juce::Justification::centred);
        }

        auto headline = textArea.reduced(12.0f, 40.0f);
        g.setColour(primary.withAlpha(0.18f + energy * 0.22f));
        g.fillRoundedRectangle(headline.expanded(16.0f, 10.0f), 16.0f);
        g.setColour(juce::Colours::white.withAlpha(0.90f));
        g.setFont(juce::Font(34.0f * scale, juce::Font::bold));
        g.drawFittedText(title.toUpperCase(), headline.toNearestInt(), juce::Justification::centred, 2);
        g.setColour(accent.withAlpha(0.82f));
        g.setFont(15.0f + 2.0f * pulseAmount);
        g.drawText(artist + "  -  " + label, textArea.toNearestInt().reduced(8), juce::Justification::centredTop);
        g.setColour(juce::Colours::white.withAlpha(0.70f + pulseAmount * 0.18f));
        g.setFont(18.0f);
        g.drawText(cta.toUpperCase(), textArea.toNearestInt().reduced(8), juce::Justification::centredBottom);
    }
    else if (module == VisualModuleType::TextCard || module == VisualModuleType::PromoCard)
    {
        auto card = guide.reduced(42.0f, 34.0f);
        g.setColour(secondary.darker(0.55f));
        g.fillRoundedRectangle(guide.reduced(22.0f), 18.0f);
        g.setColour(secondary);
        g.fillRoundedRectangle(card, 12.0f);
        g.setColour(primary.withAlpha(0.30f + energy * 0.28f));
        g.drawRoundedRectangle(card, 12.0f, 2.0f + pulseAmount);
        auto content = card.reduced(24.0f, 20.0f);
        auto tag = content.removeFromTop(28.0f);
        auto releaseTag = tag.removeFromLeft(132.0f);
        g.setColour(accent.withAlpha(0.15f + pulseAmount * 0.16f));
        g.fillRoundedRectangle(releaseTag, 10.0f);
        g.setColour(accent);
        g.setFont(14.0f);
        g.drawText(release.toUpperCase(), releaseTag.toNearestInt().reduced(10, 0), juce::Justification::centredLeft);
        content.removeFromTop(12.0f);
        const auto artSize = juce::jlimit(72.0f, 155.0f, content.getHeight() - 58.0f);
        auto art = content.removeFromLeft(artSize).withTrimmedBottom(58.0f);
        g.setColour(primary.withAlpha(0.16f + energy * 0.18f));
        g.fillRoundedRectangle(art, 12.0f);
        g.setColour(accent.withAlpha(0.50f));
        g.drawRoundedRectangle(art.reduced(8.0f), 8.0f, 1.2f);
        g.setColour(juce::Colours::white.withAlpha(0.72f));
        g.setFont(juce::Font(25.0f + pulseAmount * 5.0f, juce::Font::bold));
        g.drawText(label.substring(0, 8), art.toNearestInt().reduced(10), juce::Justification::centred);
        content.removeFromLeft(24.0f);
        auto text = content.withTrimmedBottom(58.0f);
        g.setColour(juce::Colours::white);
        g.setFont(juce::Font(28.0f, juce::Font::bold));
        g.drawFittedText(artist, text.removeFromTop(44.0f).toNearestInt(), juce::Justification::left, 1);
        g.setColour(juce::Colours::white.withAlpha(0.82f));
        g.setFont(20.0f);
        g.drawFittedText(title, text.removeFromTop(34.0f).toNearestInt(), juce::Justification::left, 2);
        g.setColour(accent.withAlpha(0.86f));
        g.setFont(15.0f);
        g.drawText(cta.toUpperCase(), text.removeFromTop(28.0f).toNearestInt(), juce::Justification::left);
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
        g.drawText(label + " / PNG still", card.reduced(24.0f, 18.0f).toNearestInt(), juce::Justification::bottomLeft);
    }
    else if (module == VisualModuleType::Particles || module == VisualModuleType::ParticleBurstPlaceholder)
    {
        auto field = guide.reduced(28.0f);
        const int columns = 15;
        const int rows = 9;
        g.setColour(secondary.withAlpha(0.40f));
        g.fillRoundedRectangle(field.expanded(10.0f), 16.0f);
        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < columns; ++x)
            {
                const auto idx = (size_t)((x + y * columns) % (int)AudioAnalyzer::spectrumBins);
                const auto dotEnergy = juce::jlimit(0.0f, 1.0f, spectrumData[idx] * 1.65f + pulseAmount * 0.40f + energy * 0.28f);
                const auto phase = (float)(x * 19 + y * 11) * 0.17f;
                const auto spread = (8.0f + 24.0f * dotEnergy) * motion;
                const auto px = field.getX() + ((float)x + 0.5f) * field.getWidth() / (float)columns + std::sin(phase + pulseAmount * 3.4f) * spread;
                const auto py = field.getY() + ((float)y + 0.5f) * field.getHeight() / (float)rows + std::cos(phase * 0.8f + pulseAmount * 2.8f) * spread;
                const auto size = 2.0f + dotEnergy * 13.5f;
                g.setColour(primary.interpolatedWith(accent, dotEnergy).withAlpha(0.18f + dotEnergy * 0.62f));
                g.fillEllipse(px - size * 0.5f, py - size * 0.5f, size, size);
            }
        }
        g.setColour(primary.withAlpha(0.24f + pulseAmount * 0.20f));
        g.drawRoundedRectangle(field, 18.0f, 1.4f);
        g.setColour(juce::Colours::white.withAlpha(0.72f));
        g.setFont(18.0f);
        g.drawText("Particles v1 / audio-reactive dot field", guide.toNearestInt().reduced(12), juce::Justification::bottomLeft);
    }
    else {
        g.setColour(juce::Colour::fromRGB(34, 211, 238));
        g.drawRoundedRectangle(guide, 8.0f, 1.0f);
        g.setFont(24.0f);
        g.drawText(visualModuleName(module) + " placeholder", b, juce::Justification::centred);
    }

}
