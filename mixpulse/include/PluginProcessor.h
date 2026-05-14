#pragma once
#include <JuceHeader.h>
#include "AudioAnalyzer.h"
#include "TapTempoEngine.h"
#include "BeatPulseEngine.h"
#include "VisualizerState.h"
#include "VisualRack.h"
#include "Branding.h"
#include "BrandLayer.h"

class MixPulseAudioProcessor : public juce::AudioProcessor
{
public:

static constexpr const char* kProductDisplayName = Branding::ProductDisplayName;
static constexpr const char* kProductCodename = Branding::ProductCodename;

    MixPulseAudioProcessor();
    ~MixPulseAudioProcessor() override = default;
    void prepareToPlay(double, int) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported(const BusesLayout&) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return kProductCodename; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }
    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}
    void getStateInformation(juce::MemoryBlock&) override;
    void setStateInformation(const void*, int) override;

    AudioAnalyzer analyzer;
    TapTempoEngine tapTempo;
    BeatPulseEngine beatPulse;
    VisualizerState visualizerState;
    VisualRackState visualRackState;
    BrandLayer::CreatorBrandState brandState;
    int selectedExportPreset = 0;
    int selectedTheme = 1;
    bool hudEnabled = false;
};
