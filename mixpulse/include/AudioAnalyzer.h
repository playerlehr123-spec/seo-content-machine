#pragma once
#include <JuceHeader.h>
#include "MeterData.h"

class AudioAnalyzer
{
public:
    static constexpr int fftOrder = 10;
    static constexpr int fftSize = 1 << fftOrder;
    static constexpr int spectrumBins = 64;

    void prepare(double sampleRate, int samplesPerBlock);
    void analyze(const juce::AudioBuffer<float>&);

    MeterData& getMeterData() noexcept { return meter; }
    const MeterData& getMeterData() const noexcept { return meter; }

    std::array<float, spectrumBins> getSpectrumSnapshot() const noexcept;

private:
    MeterData meter;
    juce::dsp::FFT fft { fftOrder };
    juce::dsp::WindowingFunction<float> window { fftSize, juce::dsp::WindowingFunction<float>::hann };
    std::array<float, fftSize * 2> fftData{};
    std::array<std::atomic<float>, spectrumBins> spectrumAtomic{};
};
