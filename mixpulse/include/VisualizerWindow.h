#pragma once
#include <JuceHeader.h>
#include "VisualizerRenderer.h"
#include "AudioAnalyzer.h"
#include "BeatPulseEngine.h"
#include "VisualizerState.h"
#include "VisualRack.h"

class VisualizerComponent : public juce::Component, private juce::Timer
{
public:
    VisualizerComponent(AudioAnalyzer&, BeatPulseEngine&, VisualizerState&, VisualRackState&);
    void paint(juce::Graphics&) override;
    void timerCallback() override;
private:
    AudioAnalyzer& analyzer;
    BeatPulseEngine& pulse;
    VisualizerState& state;
    VisualRackState& rack;
};

class VisualizerWindow : public juce::DocumentWindow
{
public:
    VisualizerWindow(AudioAnalyzer&, BeatPulseEngine&, VisualizerState&, VisualRackState&);
    void closeButtonPressed() override;
    void toggleFullscreen();
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualizerWindow)
};
