#include "PluginProcessor.h"
#include "PluginEditor.h"

MixPulseAudioProcessor::MixPulseAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

void MixPulseAudioProcessor::prepareToPlay(double sr, int spb) { analyzer.prepare(sr, spb); }

bool MixPulseAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const
{
    return l.getMainInputChannelSet() == l.getMainOutputChannelSet();
}

void MixPulseAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const auto totalInputs = getTotalNumInputChannels();
    const auto totalOutputs = getTotalNumOutputChannels();
    for (int ch = totalInputs; ch < totalOutputs; ++ch)
        buffer.clear(ch, 0, buffer.getNumSamples());

    analyzer.analyze(buffer); // Realtime-safe analysis only: never modify valid input channels.
}

juce::AudioProcessorEditor* MixPulseAudioProcessor::createEditor() { return new MixPulseAudioProcessorEditor(*this); }

void MixPulseAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::ValueTree state("WaveFrameState");
    state.setProperty("stateVersion", 1, nullptr);
    state.setProperty("productDisplayName", juce::String(kProductDisplayName), nullptr);
    state.setProperty("internalCodename", juce::String(kProductCodename), nullptr);
    state.setProperty("selectedScene", (int)visualizerState.mode.load(), nullptr);
    state.setProperty("selectedModule", visualRackState.selectedModule.load(), nullptr);
    state.setProperty("selectedOutputPreset", visualRackState.outputPreset.load(), nullptr);
    state.setProperty("selectedExportPreset", selectedExportPreset, nullptr);
    state.setProperty("selectedTheme", selectedTheme, nullptr);
    state.setProperty("hudEnabled", hudEnabled, nullptr);
    state.setProperty("beatSyncEnabled", visualizerState.beatSync.load(), nullptr);
    state.setProperty("fxBloom", visualRackState.fxBloom.load(), nullptr);
    state.setProperty("fxMirror", visualRackState.fxMirror.load(), nullptr);
    state.setProperty("fxColorize", visualRackState.fxColorize.load(), nullptr);
    state.setProperty("fxScanlines", visualRackState.fxScanlines.load(), nullptr);
    state.setProperty("fxChromaticSplit", visualRackState.fxChromaticSplit.load(), nullptr);
    state.setProperty("visualIntensity", visualRackState.visualIntensity.load(), nullptr);
    state.setProperty("motionAmount", visualRackState.motionAmount.load(), nullptr);
    state.setProperty("primaryModSource", visualRackState.primaryModSource.load(), nullptr);
    state.setProperty("artistName", brandState.artistName, nullptr);
    state.setProperty("trackTitle", brandState.trackTitle, nullptr);
    state.setProperty("labelName", brandState.labelName, nullptr);
    state.setProperty("callToAction", brandState.callToAction, nullptr);
    state.setProperty("releaseStatusText", brandState.releaseStatusText, nullptr);
    state.setProperty("logoPath", brandState.logoPath, nullptr);
    state.setProperty("logoScale", brandState.logoScale, nullptr);
    state.setProperty("logoOpacity", brandState.logoOpacity, nullptr);
    state.setProperty("logoPositionMode", brandState.logoPositionMode, nullptr);
    if (auto xml = state.createXml())
        copyXmlToBinary(*xml, destData);
}

void MixPulseAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (!xmlState) return;
    auto state = juce::ValueTree::fromXml(*xmlState);
    if (!state.isValid()) return;

    visualizerState.mode.store((VisualizerMode)(int)state.getProperty("selectedScene", (int)visualizerState.mode.load()));
    visualRackState.selectedModule.store((int)state.getProperty("selectedModule", visualRackState.selectedModule.load()));
    visualRackState.outputPreset.store((int)state.getProperty("selectedOutputPreset", visualRackState.outputPreset.load()));
    selectedExportPreset = (int)state.getProperty("selectedExportPreset", selectedExportPreset);
    selectedTheme = (int)state.getProperty("selectedTheme", selectedTheme);
    hudEnabled = (bool)state.getProperty("hudEnabled", hudEnabled);
    visualizerState.beatSync.store((bool)state.getProperty("beatSyncEnabled", visualizerState.beatSync.load()));
    visualRackState.fxBloom.store((bool)state.getProperty("fxBloom", visualRackState.fxBloom.load()));
    visualRackState.fxMirror.store((bool)state.getProperty("fxMirror", visualRackState.fxMirror.load()));
    visualRackState.fxColorize.store((bool)state.getProperty("fxColorize", visualRackState.fxColorize.load()));
    visualRackState.fxScanlines.store((bool)state.getProperty("fxScanlines", visualRackState.fxScanlines.load()));
    visualRackState.fxChromaticSplit.store((bool)state.getProperty("fxChromaticSplit", visualRackState.fxChromaticSplit.load()));
    visualRackState.visualIntensity.store((float)state.getProperty("visualIntensity", visualRackState.visualIntensity.load()));
    visualRackState.motionAmount.store((float)state.getProperty("motionAmount", visualRackState.motionAmount.load()));
    visualRackState.primaryModSource.store((int)state.getProperty("primaryModSource", visualRackState.primaryModSource.load()));
    brandState.artistName = state.getProperty("artistName", brandState.artistName).toString();
    brandState.trackTitle = state.getProperty("trackTitle", brandState.trackTitle).toString();
    brandState.labelName = state.getProperty("labelName", brandState.labelName).toString();
    brandState.callToAction = state.getProperty("callToAction", brandState.callToAction).toString();
    brandState.releaseStatusText = state.getProperty("releaseStatusText", brandState.releaseStatusText).toString();
    brandState.logoPath = state.getProperty("logoPath", brandState.logoPath).toString();
    brandState.logoScale = (float)state.getProperty("logoScale", brandState.logoScale);
    brandState.logoOpacity = (float)state.getProperty("logoOpacity", brandState.logoOpacity);
    brandState.logoPositionMode = (int)state.getProperty("logoPositionMode", brandState.logoPositionMode);
    brandState.hasLogo = brandState.logoPath.isNotEmpty() && juce::File(brandState.logoPath).existsAsFile();
}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MixPulseAudioProcessor();
}
