#include "SpectrumBarsRenderer.h"

void SpectrumBarsRenderer::render(juce::Graphics& g, juce::Rectangle<int> b, const std::vector<float>& s, float pulse)
{
    g.fillAll(juce::Colours::black);
    auto h = (float)b.getHeight();
    auto w = (float)b.getWidth() / (float)std::max<size_t>(1, s.size());
    for (size_t i=0;i<s.size();++i)
    {
        auto v = juce::jlimit(0.0f,1.0f,s[i]);
        auto barH = v * h * 0.45f;
        auto c = juce::Colour::fromFloatRGBA(0.0f + v, 0.8f + 0.2f * v, 1.0f - 0.2f * v, 1.0f);
        g.setColour(c.brighter(pulse * 0.4f));
        float x = (float)i * w;
        g.fillRect(x, h * 0.5f - barH, w * 0.8f, barH * 2.0f);
    }
}
