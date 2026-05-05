#pragma once
#include <JuceHeader.h>
#include "MeterData.h"

class AudioAnalyzer
{
public:
    void prepare(double sampleRate, int samplesPerBlock);
    void analyze(const juce::AudioBuffer<float>&);
    MeterData& getMeterData() noexcept { return meter; }
    const MeterData& getMeterData() const noexcept { return meter; }
    const std::vector<float>& getSpectrum() const noexcept { return spectrum; }
private:
    MeterData meter;
    std::vector<float> spectrum;
    juce::dsp::FFT fft { 10 };
    juce::dsp::WindowingFunction<float> window { 1024, juce::dsp::WindowingFunction<float>::hann };
    std::array<float, 2048> fftData{};
};
