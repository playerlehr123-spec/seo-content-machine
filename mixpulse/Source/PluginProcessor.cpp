#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ExportPreset.h"

namespace
{
juce::var getStatePropertyOrDefault(const juce::ValueTree& state, const juce::Identifier& key, juce::var fallback)
{
    if (state.hasProperty(key))
        return state.getProperty(key);

    return fallback;
}

VisualizerMode sanitizeVisualizerMode(int value)
{
    switch ((VisualizerMode)value)
    {
        case VisualizerMode::SpectrumBars:
        case VisualizerMode::Waveform:
        case VisualizerMode::Vectorscope:
        case VisualizerMode::ParticleBurst:
        case VisualizerMode::Tunnel:
        case VisualizerMode::Plasma:
        case VisualizerMode::SpectrogramWaterfall:
        case VisualizerMode::LogoReactor:
        case VisualizerMode::TitleCard:
        case VisualizerMode::HudOverlay:
            return (VisualizerMode)value;
    }
    return VisualizerMode::SpectrumBars;
}

int sanitizeLogoPositionMode(int value)
{
    switch ((BrandLayer::LogoPositionMode)value)
    {
        case BrandLayer::LogoPositionMode::Center:
        case BrandLayer::LogoPositionMode::CornerTopLeft:
        case BrandLayer::LogoPositionMode::CornerTopRight:
        case BrandLayer::LogoPositionMode::CornerBottomLeft:
        case BrandLayer::LogoPositionMode::CornerBottomRight:
        case BrandLayer::LogoPositionMode::Watermark:
            return value;
    }
    return (int)BrandLayer::LogoPositionMode::Center;
}

int sanitizeExportPresetIndex(int value)
{
    const auto& presets = getBuiltInExportPresets();
    if (presets.empty())
        return 0;

    return juce::jlimit(0, (int)presets.size() - 1, value);
}
}

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

    visualizerState.mode.store(sanitizeVisualizerMode((int)getStatePropertyOrDefault(state, "selectedScene", (int)visualizerState.mode.load())));
    visualRackState.selectedModule.store(sanitizeVisualModuleIndex((int)getStatePropertyOrDefault(state, "selectedModule", visualRackState.selectedModule.load())));
    visualRackState.outputPreset.store(sanitizeOutputPresetIndex((int)getStatePropertyOrDefault(state, "selectedOutputPreset", visualRackState.outputPreset.load())));
    selectedExportPreset = sanitizeExportPresetIndex((int)getStatePropertyOrDefault(state, "selectedExportPreset", selectedExportPreset));
    selectedTheme = juce::jmax(1, (int)getStatePropertyOrDefault(state, "selectedTheme", selectedTheme));
    hudEnabled = (bool)getStatePropertyOrDefault(state, "hudEnabled", hudEnabled);
    visualizerState.beatSync.store((bool)getStatePropertyOrDefault(state, "beatSyncEnabled", visualizerState.beatSync.load()));
    visualRackState.fxBloom.store((bool)getStatePropertyOrDefault(state, "fxBloom", visualRackState.fxBloom.load()));
    visualRackState.fxMirror.store((bool)getStatePropertyOrDefault(state, "fxMirror", visualRackState.fxMirror.load()));
    visualRackState.fxColorize.store((bool)getStatePropertyOrDefault(state, "fxColorize", visualRackState.fxColorize.load()));
    visualRackState.fxScanlines.store((bool)getStatePropertyOrDefault(state, "fxScanlines", visualRackState.fxScanlines.load()));
    visualRackState.fxChromaticSplit.store((bool)getStatePropertyOrDefault(state, "fxChromaticSplit", visualRackState.fxChromaticSplit.load()));
    visualRackState.visualIntensity.store(juce::jlimit(0.0f, 2.0f, (float)getStatePropertyOrDefault(state, "visualIntensity", visualRackState.visualIntensity.load())));
    visualRackState.motionAmount.store(juce::jlimit(0.0f, 1.0f, (float)getStatePropertyOrDefault(state, "motionAmount", visualRackState.motionAmount.load())));
    visualRackState.primaryModSource.store((int)getStatePropertyOrDefault(state, "primaryModSource", visualRackState.primaryModSource.load()));
    brandState.artistName = getStatePropertyOrDefault(state, "artistName", brandState.artistName).toString();
    brandState.trackTitle = getStatePropertyOrDefault(state, "trackTitle", brandState.trackTitle).toString();
    brandState.labelName = getStatePropertyOrDefault(state, "labelName", brandState.labelName).toString();
    brandState.callToAction = getStatePropertyOrDefault(state, "callToAction", brandState.callToAction).toString();
    brandState.releaseStatusText = getStatePropertyOrDefault(state, "releaseStatusText", brandState.releaseStatusText).toString();
    brandState.logoPath = getStatePropertyOrDefault(state, "logoPath", brandState.logoPath).toString();
    brandState.logoScale = juce::jlimit(0.1f, 3.0f, (float)getStatePropertyOrDefault(state, "logoScale", brandState.logoScale));
    brandState.logoOpacity = juce::jlimit(0.0f, 1.0f, (float)getStatePropertyOrDefault(state, "logoOpacity", brandState.logoOpacity));
    brandState.logoPositionMode = sanitizeLogoPositionMode((int)getStatePropertyOrDefault(state, "logoPositionMode", brandState.logoPositionMode));
    brandState.hasLogo = brandState.logoPath.isNotEmpty() && juce::File(brandState.logoPath).existsAsFile();
}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MixPulseAudioProcessor();
}
