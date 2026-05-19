#pragma once
#include <JuceHeader.h>
#include "SpectrumBarsRenderer.h"
#include "VisualizerState.h"
#include "VisualRack.h"
#include "BrandLayer.h"

class VisualizerRenderer
{
public:
    void render(juce::Graphics&, juce::Rectangle<int>, const std::array<float, AudioAnalyzer::spectrumBins>& spectrum, VisualizerMode mode, float pulse, const VisualRackState&, const BrandLayer::CreatorBrandState* brand = nullptr);
    static juce::String modeName(VisualizerMode mode);
private:
    SpectrumBarsRenderer spectrum;
};
