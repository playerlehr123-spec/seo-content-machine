#include <cmath>
#include "SpectrumBarsRenderer.h"

void SpectrumBarsRenderer::render(juce::Graphics& g, juce::Rectangle<int> b, const std::array<float, AudioAnalyzer::spectrumBins>& s, float pulse, const VisualRackState& rack)
{
    g.fillAll(juce::Colour::fromRGB(4, 6, 14).withAlpha(rack.visualIntensity.load()));
    if (rack.fxScanlines.load()) { g.setColour(juce::Colours::black.withAlpha(0.15f * rack.scanlineAmount.load())); for (int y = b.getY(); y < b.getBottom(); y += 10) g.drawHorizontalLine(y, (float)b.getX(), (float)b.getRight()); }
    g.setColour(juce::Colour::fromRGB(15, 25, 40)); for (int y = b.getY(); y < b.getBottom(); y += 24) g.drawHorizontalLine(y, (float)b.getX(), (float)b.getRight());

    const float h = (float)b.getHeight(), mid = b.getCentreY(), halfW = b.getWidth() * 0.5f; const int bars = (int)s.size(); const float step = halfW / (float)bars;
    float activity = 0.0f; for (auto v : s) activity += v; activity /= (float)bars;
    auto scope = b.toFloat().reduced(24.0f, 18.0f);
    g.setColour(juce::Colour::fromRGB(32, 218, 255).withAlpha(0.09f + activity * 0.12f));
    g.drawRoundedRectangle(scope, 14.0f, 1.0f);
    g.setColour(juce::Colours::white.withAlpha(0.10f));
    g.drawLine(scope.getX(), mid, scope.getRight(), mid, 1.0f);

    for (int i = 0; i < bars; ++i)
    {
        const float n = (float)i / (float)bars; const float v = juce::jlimit(0.0f, 1.0f, s[(size_t)i]); const float eased = std::pow(v, 0.75f);
        const float barH = eased * h * (0.42f + 0.08f * pulse * rack.motionAmount.load()); const float thickness = step * (1.3f - n * 0.5f + pulse * 0.12f);
        auto hue = 0.62f - 0.45f * eased; if (rack.fxColorize.load()) hue -= 0.05f * pulse * rack.colorizeAmount.load();
        auto col = juce::Colour::fromHSV(hue, 0.9f, 0.3f + 0.7f * eased, 1.0f).withMultipliedAlpha(0.95f);
        if (rack.fxBloom.load()) { g.setColour(col.withAlpha(0.2f + 0.2f * rack.bloomAmount.load())); g.fillRoundedRectangle(b.getCentreX() - (i + 1) * step, mid - barH - 3.0f, thickness, barH * 2.0f + 6.0f, 2.5f); g.fillRoundedRectangle(b.getCentreX() + i * step, mid - barH - 3.0f, thickness, barH * 2.0f + 6.0f, 2.5f); }
        g.setColour(col.brighter(0.2f + pulse * 0.3f));
        if (rack.fxMirror.load()) {
            g.fillRoundedRectangle(b.getCentreX() - (i + 1) * step, mid - barH, thickness, barH * 2.0f, 2.0f);
            g.fillRoundedRectangle(b.getCentreX() + i * step, mid - barH, thickness, barH * 2.0f, 2.0f);
        } else {
            g.fillRoundedRectangle(b.getX() + i * (b.getWidth() / (float)bars), b.getBottom() - barH, thickness, barH, 2.0f);
        }
    }
    if (rack.fxChromaticSplit.load()) { g.setColour(juce::Colours::red.withAlpha(0.08f * rack.chromaticAmount.load())); g.fillRect(b.translated((int)(2.0f*pulse),0)); }
    g.setColour(juce::Colour::fromRGB(32, 218, 255).withAlpha(0.2f + pulse * 0.35f + activity * 0.25f)); g.drawLine((float)b.getX(), mid, (float)b.getRight(), mid, 1.5f);
    if (activity < 0.03f) { g.setColour(juce::Colour::fromRGB(70,120,160).withAlpha(0.22f + 0.08f * std::sin(pulse * 6.28f))); g.drawLine((float)b.getX(), mid + 8.0f, (float)b.getRight(), mid + 8.0f, 1.0f); }
}
