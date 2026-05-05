#include "PluginProcessor.h"
#include "PluginEditor.h"

MixPulseAudioProcessor::MixPulseAudioProcessor()
: AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                 .withOutput("Output", juce::AudioChannelSet::stereo(), true)) {}

void MixPulseAudioProcessor::prepareToPlay(double sr, int spb) { analyzer.prepare(sr, spb); }
bool MixPulseAudioProcessor::isBusesLayoutSupported(const BusesLayout& l) const { return l.getMainInputChannelSet() == l.getMainOutputChannelSet(); }
void MixPulseAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    analyzer.analyze(buffer); // analysis only, no modification
}
juce::AudioProcessorEditor* MixPulseAudioProcessor::createEditor() { return new MixPulseAudioProcessorEditor(*this); }
