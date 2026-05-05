#pragma once
#include <JuceHeader.h>
#include "SpectrumBarsRenderer.h"
#include "VisualizerState.h"

class VisualizerRenderer
{
public:
    void render(juce::Graphics&, juce::Rectangle<int>, const std::vector<float>& spectrum, VisualizerMode mode, float pulse);
private:
    SpectrumBarsRenderer spectrum;
};
