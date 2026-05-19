#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ThemeManager.h"
#include "VisualizerWindow.h"
#include "ExportPreset.h"

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
    void saveUserPreset();
    void loadUserPreset();
    void resetDefaults();
    void syncUiToProcessorState();
    void applySelectedExportPresetToOutputGuide();
    void drawMeterColumn(juce::Graphics&, juce::Rectangle<int> area);
    void drawVerticalBar(juce::Graphics&, juce::Rectangle<float> area, float value, juce::Colour baseColor, const juce::String& label, float& holdDb);
    void setStatusMessage(const juce::String&);

    MixPulseAudioProcessor& processor;
    ThemeManager::Theme theme;
    juce::TextButton tapButton { "Tap" }, visualizerButton { "Output" }, screenshotButton { "Frame" }, hudButton { "HUD" }, fullscreenButton { "Full" }, infoButton { "Info" }, copyInfoButton { "Copy Info" }, savePresetButton { "Save Preset" }, loadPresetButton { "Load Preset" }, resetDefaultButton { "Reset Default" };
    juce::ToggleButton beatSyncButton { "Beat Sync" };
    juce::ComboBox themeBox, exportPresetBox, templateBox;

    float peakHoldL = -60.0f, peakHoldR = -60.0f, rmsHoldL = -60.0f, rmsHoldR = -60.0f;
    bool hudMode = false;
    juce::String statusMessage;
    double statusUntilSeconds = 0.0;
    std::unique_ptr<VisualizerWindow> visualizer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixPulseAudioProcessorEditor)
};
