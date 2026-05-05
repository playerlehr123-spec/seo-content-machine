#include "VisualizerRenderer.h"
void VisualizerRenderer::render(juce::Graphics& g, juce::Rectangle<int> b, const std::vector<float>& spectrumData, VisualizerMode mode, float pulse)
{
    if (mode == VisualizerMode::SpectrumBars) spectrum.render(g,b,spectrumData,pulse);
    else { g.fillAll(juce::Colours::black); g.setColour(juce::Colours::white); g.drawText("TODO mode", b, juce::Justification::centred); }
}
