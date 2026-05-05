#pragma once
#include <JuceHeader.h>
#include "AudioAnalyzer.h"

class SpectrumBarsRenderer
{
public:
    void render(juce::Graphics&, juce::Rectangle<int>, const std::array<float, AudioAnalyzer::spectrumBins>& spectrum, float pulse);
};
