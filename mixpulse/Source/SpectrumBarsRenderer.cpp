#include <cmath>
#include "SpectrumBarsRenderer.h"

void SpectrumBarsRenderer::render(juce::Graphics& g, juce::Rectangle<int> b, const std::array<float, AudioAnalyzer::spectrumBins>& s, float pulse)
{
    g.fillAll(juce::Colour::fromRGB(4, 6, 14));
    g.setColour(juce::Colour::fromRGB(15, 25, 40));
    for (int y = b.getY(); y < b.getBottom(); y += 24) g.drawHorizontalLine(y, (float)b.getX(), (float)b.getRight());

    const float h = (float)b.getHeight();
    const float mid = b.getCentreY();
    const float halfW = b.getWidth() * 0.5f;
    const int bars = (int)s.size();
    const float step = halfW / (float)bars;

    for (int i = 0; i < bars; ++i)
    {
        const float n = (float)i / (float)bars;
        const float v = juce::jlimit(0.0f, 1.0f, s[(size_t)i]);
        const float eased = std::pow(v, 0.75f);
        const float barH = eased * h * (0.42f + 0.08f * pulse);
        const float thickness = step * (1.4f - n * 0.5f + pulse * 0.15f);

        auto col = juce::Colour::fromHSV(0.62f - 0.45f * eased, 0.9f, 0.3f + 0.7f * eased, 1.0f).withMultipliedAlpha(0.95f);
        g.setColour(col.withAlpha(0.25f));
        g.fillRect(b.getCentreX() - (i + 1) * step, mid - barH - 2.0f, thickness, barH * 2.0f + 4.0f);
        g.fillRect(b.getCentreX() + i * step, mid - barH - 2.0f, thickness, barH * 2.0f + 4.0f);
        g.setColour(col.brighter(0.3f + pulse * 0.3f));
        g.fillRect(b.getCentreX() - (i + 1) * step, mid - barH, thickness, barH * 2.0f);
        g.fillRect(b.getCentreX() + i * step, mid - barH, thickness, barH * 2.0f);
    }

    g.setColour(juce::Colour::fromRGB(32, 218, 255).withAlpha(0.35f + pulse * 0.3f));
    g.drawLine((float)b.getX(), mid, (float)b.getRight(), mid, 1.5f);
}
