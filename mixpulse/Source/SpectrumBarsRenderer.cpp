#include <cmath>
#include "SpectrumBarsRenderer.h"

void SpectrumBarsRenderer::render(juce::Graphics& g, juce::Rectangle<int> b, const std::array<float, AudioAnalyzer::spectrumBins>& s, float pulse, const VisualRackState& rack)
{
    const auto intensity = juce::jlimit(0.0f, 2.0f, rack.visualIntensity.load());
    const auto motion = juce::jlimit(0.0f, 1.0f, rack.motionAmount.load());
    g.fillAll(juce::Colour::fromString("ff030407"));

    const float h = (float)b.getHeight(), mid = b.getCentreY(), halfW = b.getWidth() * 0.5f; const int bars = (int)s.size(); const float step = halfW / (float)bars;
    float activity = 0.0f; for (auto v : s) activity += v; activity /= (float)bars;

    auto scope = b.toFloat().reduced(26.0f, 20.0f);
    g.setColour(juce::Colour::fromString("ff080b10"));
    g.fillRect(scope.expanded(8.0f));
    g.setColour(juce::Colour::fromString("ff31d7ff").withAlpha(0.06f + activity * 0.10f));
    g.fillRect(scope);
    g.setColour(juce::Colour::fromString("ff252c38"));
    g.drawRect(scope, 1.0f);

    if (rack.fxScanlines.load())
    {
        g.setColour(juce::Colours::black.withAlpha(0.13f * rack.scanlineAmount.load()));
        for (int y = b.getY(); y < b.getBottom(); y += 10)
            g.drawHorizontalLine(y, (float)b.getX(), (float)b.getRight());
    }

    g.setColour(juce::Colour::fromRGB(32, 218, 255).withAlpha(0.055f));
    for (int y = (int)scope.getY(); y < (int)scope.getBottom(); y += 28)
        g.drawHorizontalLine(y, scope.getX(), scope.getRight());
    g.setColour(juce::Colours::white.withAlpha(0.045f));
    for (int x = (int)scope.getX(); x < (int)scope.getRight(); x += 34)
        g.drawVerticalLine(x, scope.getY(), scope.getBottom());
    g.setColour(juce::Colours::white.withAlpha(0.10f));
    g.drawLine(scope.getX(), mid, scope.getRight(), mid, 1.0f);

    for (int i = 0; i < bars; ++i)
    {
        const float n = (float)i / (float)bars; const float v = juce::jlimit(0.0f, 1.0f, s[(size_t)i]); const float eased = std::pow(v, 0.75f);
        const float barH = eased * h * (0.38f + 0.08f * pulse * motion) * (0.72f + 0.18f * intensity); const float thickness = juce::jmax(2.0f, step * (1.08f - n * 0.38f + pulse * 0.10f));
        const auto cyan = juce::Colour::fromString("ff31d7ff");
        const auto magenta = juce::Colour::fromString("ffff3d9a");
        const auto orange = juce::Colour::fromString("ffff6a2a");
        auto col = n < 0.58f ? cyan.interpolatedWith(magenta, n / 0.58f)
                             : magenta.interpolatedWith(orange, (n - 0.58f) / 0.42f);
        col = col.withMultipliedBrightness(0.34f + 0.66f * eased).withMultipliedAlpha(0.96f);
        if (rack.fxBloom.load()) { g.setColour(col.withAlpha(0.12f + 0.18f * rack.bloomAmount.load())); g.fillRoundedRectangle(b.getCentreX() - (i + 1) * step - 1.0f, mid - barH - 5.0f, thickness + 2.0f, barH * 2.0f + 10.0f, 3.0f); g.fillRoundedRectangle(b.getCentreX() + i * step - 1.0f, mid - barH - 5.0f, thickness + 2.0f, barH * 2.0f + 10.0f, 3.0f); }
        g.setColour(col.brighter(0.2f + pulse * 0.3f));
        if (rack.fxMirror.load()) {
            g.fillRoundedRectangle(b.getCentreX() - (i + 1) * step, mid - barH, thickness, barH * 2.0f, 2.0f);
            g.fillRoundedRectangle(b.getCentreX() + i * step, mid - barH, thickness, barH * 2.0f, 2.0f);
        } else {
            g.fillRoundedRectangle(b.getX() + i * (b.getWidth() / (float)bars), b.getBottom() - barH, thickness, barH, 2.0f);
        }
    }
    if (rack.fxChromaticSplit.load()) { g.setColour(juce::Colours::red.withAlpha(0.08f * rack.chromaticAmount.load())); g.fillRect(b.translated((int)(2.0f*pulse),0)); }
    g.setColour(juce::Colour::fromRGB(32, 218, 255).withAlpha(0.2f + pulse * 0.32f + activity * 0.25f)); g.drawLine(scope.getX(), mid, scope.getRight(), mid, 1.5f);
    g.setColour(juce::Colours::white.withAlpha(0.42f));
    g.setFont(12.0f);
    g.drawText("SPECTRUM BARS", scope.toNearestInt().reduced(14), juce::Justification::topLeft);
    if (activity < 0.03f) { g.setColour(juce::Colour::fromRGB(70,120,160).withAlpha(0.22f + 0.08f * std::sin(pulse * 6.28f))); g.drawLine(scope.getX(), mid + 8.0f, scope.getRight(), mid + 8.0f, 1.0f); }
}
