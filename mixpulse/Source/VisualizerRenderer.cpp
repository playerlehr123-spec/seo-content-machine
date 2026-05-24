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

void drawWaveFrameBackground(juce::Graphics& g, juce::Rectangle<int> bounds, juce::Colour primary, juce::Colour secondary, float energy)
{
    g.fillAll(juce::Colour::fromRGB(4, 7, 14));

    auto area = bounds.toFloat();
    g.setColour(secondary.darker(0.72f).withAlpha(0.72f));
    g.fillRoundedRectangle(area.reduced(18.0f), 18.0f);

    g.setColour(primary.withAlpha(0.035f + energy * 0.035f));
    for (int x = bounds.getX(); x < bounds.getRight(); x += 34)
        g.drawVerticalLine(x, (float)bounds.getY(), (float)bounds.getBottom());

    g.setColour(juce::Colours::white.withAlpha(0.035f));
    for (int y = bounds.getY(); y < bounds.getBottom(); y += 34)
        g.drawHorizontalLine(y, (float)bounds.getX(), (float)bounds.getRight());
}

void drawCornerTicks(juce::Graphics& g, juce::Rectangle<float> r, juce::Colour colour, float alpha)
{
    const auto len = juce::jmin(34.0f, juce::jmin(r.getWidth(), r.getHeight()) * 0.12f);
    g.setColour(colour.withAlpha(alpha));
    g.drawLine(r.getX(), r.getY(), r.getX() + len, r.getY(), 1.4f);
    g.drawLine(r.getX(), r.getY(), r.getX(), r.getY() + len, 1.4f);
    g.drawLine(r.getRight(), r.getY(), r.getRight() - len, r.getY(), 1.4f);
    g.drawLine(r.getRight(), r.getY(), r.getRight(), r.getY() + len, 1.4f);
    g.drawLine(r.getX(), r.getBottom(), r.getX() + len, r.getBottom(), 1.4f);
    g.drawLine(r.getX(), r.getBottom(), r.getX(), r.getBottom() - len, 1.4f);
    g.drawLine(r.getRight(), r.getBottom(), r.getRight() - len, r.getBottom(), 1.4f);
    g.drawLine(r.getRight(), r.getBottom(), r.getRight(), r.getBottom() - len, 1.4f);
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
    const auto bass = averageBins(spectrumData, 0, 10);
    const auto mids = averageBins(spectrumData, 10, 34);
    const auto highs = averageBins(spectrumData, 34, (int)AudioAnalyzer::spectrumBins);
    const auto energy = juce::jlimit(0.0f, 1.0f, bass * 0.45f + mids * 0.35f + highs * 0.20f + pulseAmount * 0.25f);

    drawWaveFrameBackground(g, b, primary, secondary, energy);

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
        drawCornerTicks(g, guide.reduced(5.0f), primary, 0.22f);
    }

    if (module == VisualModuleType::LogoPulse)
    {
        const auto placementMode = brand != nullptr ? brand->logoPositionMode : (int)BrandLayer::LogoPositionMode::Center;
        const auto centre = logoCentreForMode(guide, placementMode);
        const auto scale = juce::jmax(0.65f, brand != nullptr ? brand->logoScale : 1.0f);
        const auto opacity = juce::jlimit(0.2f, 1.0f, brand != nullptr ? brand->logoOpacity : 0.85f);
        const auto logoSize = (122.0f + 82.0f * energy) * scale;
        const auto mark = juce::Rectangle<float>(logoSize, logoSize).withCentre(centre);

        auto stage = guide.reduced(22.0f);
        g.setColour(secondary.darker(0.50f).withAlpha(0.82f));
        g.fillRoundedRectangle(stage, 22.0f);
        g.setColour(primary.withAlpha(0.08f + energy * 0.12f));
        g.fillRoundedRectangle(stage.reduced(18.0f), 18.0f);

        for (int i = 3; i >= 0; --i)
        {
            const auto spread = logoSize + 54.0f + (float)i * 26.0f + pulseAmount * 18.0f;
            g.setColour((i % 2 == 0 ? primary : accent).withAlpha((0.035f + energy * 0.045f) * opacity));
            g.fillEllipse(mark.withSizeKeepingCentre(spread, spread));
        }

        g.setColour(juce::Colours::black.withAlpha(0.34f));
        g.fillEllipse(mark.translated(0.0f, 10.0f).expanded(10.0f));
        g.setColour(primary.withAlpha((0.70f + energy * 0.22f) * opacity));
        g.fillEllipse(mark);
        g.setColour(secondary.darker(0.72f).withAlpha(0.88f * opacity));
        g.fillEllipse(mark.reduced(12.0f));
        g.setColour(accent.withAlpha(0.48f + pulseAmount * 0.34f));
        g.drawEllipse(mark.reduced(8.0f), 1.6f + pulseAmount * 2.2f);

        auto initials = label.trim().substring(0, 2).toUpperCase();
        if (initials.isEmpty())
            initials = "WF";
        g.setColour(juce::Colours::white.withAlpha(0.92f * opacity));
        g.setFont(juce::Font(36.0f + 13.0f * energy, juce::Font::bold));
        g.drawText(initials, mark.toNearestInt().reduced(12), juce::Justification::centred);

        auto lower = guide.reduced(34.0f).removeFromBottom(92.0f);
        g.setColour(juce::Colours::white.withAlpha(0.58f));
        g.setFont(13.0f + 2.0f * pulseAmount);
        g.drawText(artist.toUpperCase(), lower.removeFromTop(24.0f).toNearestInt(), juce::Justification::centred);
        g.setColour(juce::Colours::white.withAlpha(0.88f));
        g.setFont(juce::Font(22.0f, juce::Font::bold));
        g.drawFittedText(title, lower.removeFromTop(34.0f).toNearestInt(), juce::Justification::centred, 1);
        g.setColour(accent.withAlpha(0.82f));
        g.setFont(12.0f);
        g.drawText("BEAT-REACTIVE BRAND MARK", lower.removeFromTop(22.0f).toNearestInt(), juce::Justification::centred);
    }
    else if (module == VisualModuleType::TypePulse)
    {
        auto textArea = guide.reduced(34.0f);
        const auto scale = 1.0f + (pulseAmount * 0.16f + energy * 0.10f) * motion;
        const auto repeated = (artist + "  /  " + title + "  /  " + cta).toUpperCase();

        g.setColour(secondary.darker(0.55f).withAlpha(0.68f));
        g.fillRoundedRectangle(textArea.expanded(10.0f), 18.0f);

        for (int i = 0; i < 8; ++i)
        {
            const auto y = textArea.getY() + (float)i * textArea.getHeight() / 8.0f;
            const auto alpha = 0.055f + 0.08f * pulseAmount + 0.035f * (float)(i % 2);
            g.setColour((i % 2 == 0 ? primary : accent).withAlpha(alpha));
            g.setFont(14.0f + (float)(i % 3) * 2.0f);
            g.drawText(repeated, (int)textArea.getX() - (i % 2) * 24, (int)y, (int)textArea.getWidth() + 48, 26, juce::Justification::centred);
        }

        auto headline = textArea.reduced(18.0f, 48.0f);
        g.setColour(primary.withAlpha(0.12f + energy * 0.18f));
        g.fillRoundedRectangle(headline.expanded(18.0f, 14.0f), 18.0f);
        g.setColour(accent.withAlpha(0.16f + pulseAmount * 0.14f));
        g.drawRoundedRectangle(headline.expanded(18.0f, 14.0f), 18.0f, 1.4f);
        g.setColour(juce::Colours::white.withAlpha(0.90f));
        g.setFont(juce::Font(38.0f * scale, juce::Font::bold));
        g.drawFittedText(title.toUpperCase(), headline.toNearestInt(), juce::Justification::centred, 2);
        g.setColour(accent.withAlpha(0.82f));
        g.setFont(15.0f + 2.0f * pulseAmount);
        g.drawText(artist.toUpperCase() + "  /  " + label.toUpperCase(), textArea.toNearestInt().reduced(10), juce::Justification::centredTop);
        g.setColour(juce::Colours::white.withAlpha(0.70f + pulseAmount * 0.18f));
        g.setFont(18.0f);
        g.drawText(cta.toUpperCase(), textArea.toNearestInt().reduced(8), juce::Justification::centredBottom);
    }
    else if (module == VisualModuleType::TextCard || module == VisualModuleType::PromoCard)
    {
        auto card = guide.reduced(42.0f, 34.0f);
        g.setColour(primary.withAlpha(0.055f + energy * 0.09f));
        g.fillRoundedRectangle(guide.reduced(20.0f), 22.0f);
        g.setColour(secondary.darker(0.55f));
        g.fillRoundedRectangle(guide.reduced(28.0f), 18.0f);
        g.setColour(secondary);
        g.fillRoundedRectangle(card, 12.0f);
        g.setColour(primary.withAlpha(0.30f + energy * 0.28f));
        g.drawRoundedRectangle(card, 12.0f, 2.0f + pulseAmount);
        auto content = card.reduced(24.0f, 20.0f);
        auto tag = content.removeFromTop(28.0f);
        auto releaseTag = tag.removeFromLeft(150.0f);
        g.setColour(accent.withAlpha(0.15f + pulseAmount * 0.16f));
        g.fillRoundedRectangle(releaseTag, 10.0f);
        g.setColour(accent);
        g.setFont(14.0f);
        g.drawText(release.toUpperCase(), releaseTag.toNearestInt().reduced(10, 0), juce::Justification::centredLeft);
        g.setColour(juce::Colours::white.withAlpha(0.38f));
        g.setFont(12.0f);
        g.drawText("WAVEFRAME STILL", tag.toNearestInt(), juce::Justification::centredRight);
        content.removeFromTop(12.0f);
        const auto artSize = juce::jlimit(72.0f, 155.0f, content.getHeight() - 58.0f);
        auto art = content.removeFromLeft(artSize).withTrimmedBottom(58.0f);
        g.setColour(primary.withAlpha(0.16f + energy * 0.18f));
        g.fillRoundedRectangle(art, 12.0f);
        g.setColour(secondary.darker(0.35f).withAlpha(0.45f));
        g.fillRoundedRectangle(art.reduced(12.0f), 9.0f);
        g.setColour(accent.withAlpha(0.50f));
        g.drawRoundedRectangle(art.reduced(8.0f), 8.0f, 1.2f);
        g.setColour(juce::Colours::white.withAlpha(0.72f));
        g.setFont(juce::Font(28.0f + pulseAmount * 5.0f, juce::Font::bold));
        g.drawText(label.substring(0, 8), art.toNearestInt().reduced(10), juce::Justification::centred);
        content.removeFromLeft(24.0f);
        auto text = content.withTrimmedBottom(58.0f);
        g.setColour(juce::Colours::white);
        g.setFont(juce::Font(15.0f, juce::Font::bold));
        g.drawFittedText(artist.toUpperCase(), text.removeFromTop(24.0f).toNearestInt(), juce::Justification::left, 1);
        g.setColour(juce::Colours::white.withAlpha(0.82f));
        g.setFont(juce::Font(28.0f, juce::Font::bold));
        g.drawFittedText(title, text.removeFromTop(54.0f).toNearestInt(), juce::Justification::left, 2);
        g.setColour(accent.withAlpha(0.86f));
        g.setFont(15.0f);
        g.drawText(cta.toUpperCase(), text.removeFromTop(28.0f).toNearestInt(), juce::Justification::left);
        g.setColour(primary.withAlpha(0.86f));
        auto strip = content.removeFromBottom(42);
        const auto binsToDraw = juce::jmin((int)AudioAnalyzer::spectrumBins, 28);
        const auto barW = juce::jmax(2.0f, strip.getWidth() / (float)binsToDraw);
        for (int i = 0; i < binsToDraw; ++i)
        {
            const auto value = juce::jlimit(0.0f, 1.0f, spectrumData[(size_t)i] * (0.8f + intensity));
            const auto h = 3.0f + value * strip.getHeight();
            g.fillRoundedRectangle(strip.getX() + i * barW, strip.getBottom() - h, barW * 0.62f, h, 2.0f);
        }
        g.setColour(juce::Colours::white.withAlpha(0.72f));
        g.setFont(15.0f);
        g.drawText(label + " / PNG still", card.reduced(24.0f, 18.0f).toNearestInt(), juce::Justification::bottomLeft);
    }
    else if (module == VisualModuleType::Particles || module == VisualModuleType::ParticleBurstPlaceholder)
    {
        auto field = guide.reduced(28.0f);
        const int columns = 17;
        const int rows = 10;
        g.setColour(secondary.darker(0.55f).withAlpha(0.52f));
        g.fillRoundedRectangle(field.expanded(12.0f), 18.0f);
        g.setColour(primary.withAlpha(0.12f + energy * 0.14f));
        g.drawRoundedRectangle(field.expanded(12.0f), 18.0f, 1.1f);
        for (int y = 0; y < rows; ++y)
        {
            for (int x = 0; x < columns; ++x)
            {
                const auto idx = (size_t)((x + y * columns) % (int)AudioAnalyzer::spectrumBins);
                const auto dotEnergy = juce::jlimit(0.0f, 1.0f, spectrumData[idx] * 1.65f + pulseAmount * 0.34f + energy * 0.24f);
                const auto phase = (float)(x * 19 + y * 11) * 0.17f;
                const auto spread = (8.0f + 24.0f * dotEnergy) * motion;
                const auto px = field.getX() + ((float)x + 0.5f) * field.getWidth() / (float)columns + std::sin(phase + pulseAmount * 3.4f) * spread;
                const auto py = field.getY() + ((float)y + 0.5f) * field.getHeight() / (float)rows + std::cos(phase * 0.8f + pulseAmount * 2.8f) * spread;
                const auto size = 2.0f + dotEnergy * 11.5f;
                g.setColour(primary.interpolatedWith(accent, dotEnergy).withAlpha(0.055f + dotEnergy * 0.12f));
                g.fillEllipse(px - size, py - size, size * 2.0f, size * 2.0f);
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
