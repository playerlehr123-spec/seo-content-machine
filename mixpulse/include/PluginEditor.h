#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ThemeManager.h"
#include "VisualizerWindow.h"

class MixPulseAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit MixPulseAudioProcessorEditor(MixPulseAudioProcessor&);
    ~MixPulseAudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void resized() override;
    bool keyPressed(const juce::KeyPress&) override;
    void timerCallback() override;
private:
    void openVisualizer();
    void exportScreenshot();
    MixPulseAudioProcessor& processor;
    ThemeManager::Theme theme;
    juce::TextButton tapButton { "Tap (T)" }, visualizerButton { "Open Visualizer" };
    juce::ToggleButton beatSyncButton { "Beat Sync (B)" };
    std::unique_ptr<VisualizerWindow> visualizer;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixPulseAudioProcessorEditor)
};
