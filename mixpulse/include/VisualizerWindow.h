#pragma once
#include <JuceHeader.h>
#include "VisualizerRenderer.h"
#include "AudioAnalyzer.h"
#include "BeatPulseEngine.h"
#include "VisualizerState.h"
#include "VisualRack.h"
#include "BrandLayer.h"

class VisualizerComponent : public juce::Component, private juce::Timer
{
public:
    VisualizerComponent(AudioAnalyzer&, BeatPulseEngine&, VisualizerState&, VisualRackState&, BrandLayer::CreatorBrandState&);
    void paint(juce::Graphics&) override;
    void timerCallback() override;
private:
    void drawCaptureOverlay(juce::Graphics&);

    AudioAnalyzer& analyzer;
    BeatPulseEngine& pulse;
    VisualizerState& state;
    VisualRackState& rack;
    BrandLayer::CreatorBrandState& brand;
};

class VisualizerWindow : public juce::DocumentWindow
{
public:
    VisualizerWindow(AudioAnalyzer&, BeatPulseEngine&, VisualizerState&, VisualRackState&, BrandLayer::CreatorBrandState&);
    void closeButtonPressed() override;
    void prepareToShow();
    void toggleFullscreen();
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualizerWindow)
};
