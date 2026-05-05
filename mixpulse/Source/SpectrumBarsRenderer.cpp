#include "SpectrumBarsRenderer.h"

void SpectrumBarsRenderer::render(juce::Graphics& g, juce::Rectangle<int> b, const std::array<float, AudioAnalyzer::spectrumBins>& s, float pulse)
{
    g.fillAll(juce::Colours::black);
    const auto h = (float)b.getHeight();
    const auto w = (float)b.getWidth() / (float)s.size();

    for (size_t i = 0; i < s.size(); ++i)
    {
        const auto v = juce::jlimit(0.0f, 1.0f, s[i]);
        const auto barH = v * h * 0.45f;
        const auto c = juce::Colour::fromFloatRGBA(v, 0.8f + 0.2f * v, 1.0f - 0.2f * v, 1.0f);
        g.setColour(c.brighter(pulse * 0.4f));
        const auto x = (float)i * w;
        g.fillRect(x, h * 0.5f - barH, w * 0.8f, barH * 2.0f);
    }
}
