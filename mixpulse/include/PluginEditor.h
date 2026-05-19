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
    void syncModuleBoxToProcessor();
    void drawHeader(juce::Graphics&, juce::Rectangle<int> area);
    void drawPreviewCanvas(juce::Graphics&, juce::Rectangle<int> area);
    void drawRightControlPanel(juce::Graphics&, juce::Rectangle<int> area);
    void drawHudPanel(juce::Graphics&, juce::Rectangle<int> area);
    void drawPanel(juce::Graphics&, juce::Rectangle<int> area, const juce::String& title);
    void drawSectionTitle(juce::Graphics&, juce::Rectangle<int> area, const juce::String& text);
    void drawLabelValue(juce::Graphics&, juce::Rectangle<int> area, const juce::String& label, const juce::String& value);
    void drawPill(juce::Graphics&, juce::Rectangle<int> area, const juce::String& text, juce::Colour colour);
    void drawMeterColumn(juce::Graphics&, juce::Rectangle<int> area);
    void drawVerticalBar(juce::Graphics&, juce::Rectangle<float> area, float value, juce::Colour baseColor, const juce::String& label, float& holdDb);
    void setStatusMessage(const juce::String&);

    MixPulseAudioProcessor& processor;
    ThemeManager::Theme theme;
    juce::TextButton tapButton { "Tap" }, visualizerButton { "Output" }, screenshotButton { "Frame" }, hudButton { "HUD" }, fullscreenButton { "Full" }, infoButton { "Info" }, copyInfoButton { "Copy Info" }, savePresetButton { "Save Preset" }, loadPresetButton { "Load Preset" }, resetDefaultButton { "Reset Default" };
    juce::ToggleButton beatSyncButton { "Beat Sync" };
    juce::ComboBox themeBox, exportPresetBox, templateBox, moduleBox;

    float peakHoldL = -60.0f, peakHoldR = -60.0f, rmsHoldL = -60.0f, rmsHoldR = -60.0f;
    bool hudMode = false;
    juce::String statusMessage;
    double statusUntilSeconds = 0.0;
    std::unique_ptr<VisualizerWindow> visualizer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MixPulseAudioProcessorEditor)
};
