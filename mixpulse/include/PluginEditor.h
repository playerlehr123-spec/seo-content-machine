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
    void drawMeterColumn(juce::Graphics&, juce::Rectangle<int> area);
    void drawVerticalBar(juce::Graphics&, juce::Rectangle<float> area, float value, juce::Colour baseColor, const juce::String& label, float& holdDb);

    MixPulseAudioProcessor& processor;
    ThemeManager::Theme theme;
    juce::TextButton tapButton { "Tap" }, visualizerButton { "Visualizer" }, screenshotButton { "Shot" }, hudButton { "HUD" }, fullscreenButton { "Full" };
    juce::ToggleButton beatSyncButton { "Beat Sync" };
    juce::ComboBox themeBox;

    float peakHoldL = -60.0f, peakHoldR = -60.0f, rmsHoldL = -60.0f, rmsHoldR = -60.0f;
    std::unique_ptr<VisualizerWindow> visualizer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixPulseAudioProcessorEditor)
};
