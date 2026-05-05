#pragma once
#include <JuceHeader.h>

class SpectrumBarsRenderer
{
public:
    void render(juce::Graphics&, juce::Rectangle<int>, const std::vector<float>& spectrum, float pulse);
};
