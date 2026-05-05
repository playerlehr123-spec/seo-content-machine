#include "AudioAnalyzer.h"

void AudioAnalyzer::prepare(double, int)
{
    for (auto& s : spectrumAtomic)
        s.store(0.0f, std::memory_order_relaxed);
}

std::array<float, AudioAnalyzer::spectrumBins> AudioAnalyzer::getSpectrumSnapshot() const noexcept
{
    std::array<float, spectrumBins> out{};
    for (int i = 0; i < spectrumBins; ++i)
        out[(size_t)i] = spectrumAtomic[(size_t)i].load(std::memory_order_relaxed);
    return out;
}

void AudioAnalyzer::analyze(const juce::AudioBuffer<float>& buffer)
{
    const auto channels = buffer.getNumChannels();
    const auto n = buffer.getNumSamples();

    if (channels <= 0 || n <= 0)
    {
        meter.peakL.store(0.0f, std::memory_order_relaxed);
        meter.peakR.store(0.0f, std::memory_order_relaxed);
        meter.rmsL.store(0.0f, std::memory_order_relaxed);
        meter.rmsR.store(0.0f, std::memory_order_relaxed);
        meter.truePeak.store(0.0f, std::memory_order_relaxed);
        return;
    }

    float pL = 0.0f, pR = 0.0f, eL = 0.0f, eR = 0.0f;
    for (int i = 0; i < n; ++i)
    {
        const auto l = buffer.getSample(0, i);
        const auto r = channels > 1 ? buffer.getSample(1, i) : l;
        pL = std::max(pL, std::abs(l));
        pR = std::max(pR, std::abs(r));
        eL += l * l;
        eR += r * r;
    }

    meter.peakL.store(pL, std::memory_order_relaxed);
    meter.peakR.store(pR, std::memory_order_relaxed);
    meter.rmsL.store(std::sqrt(eL / (float)std::max(1, n)), std::memory_order_relaxed);
    meter.rmsR.store(std::sqrt(eR / (float)std::max(1, n)), std::memory_order_relaxed);
    meter.truePeak.store(std::max(pL, pR), std::memory_order_relaxed);

    if (pL >= 0.999f || pR >= 0.999f)
        meter.clipLatched.store(true, std::memory_order_relaxed);

    const auto avgRms = 0.5f * (meter.rmsL.load(std::memory_order_relaxed) + meter.rmsR.load(std::memory_order_relaxed));
    meter.lufsM.store(juce::Decibels::gainToDecibels(std::max(1.0e-6f, avgRms)), std::memory_order_relaxed);

    // TODO: rolling FFT input ring buffer for sub-fft block sizes.
    if (n >= fftSize)
    {
        std::fill(fftData.begin(), fftData.end(), 0.0f);
        juce::FloatVectorOperations::copy(fftData.data(), buffer.getReadPointer(0), fftSize);
        window.multiplyWithWindowingTable(fftData.data(), fftSize);
        fft.performFrequencyOnlyForwardTransform(fftData.data());

        for (int i = 0; i < spectrumBins; ++i)
        {
            const auto mag = juce::jlimit(0.0f, 1.0f, fftData[(size_t)i] / 128.0f);
            spectrumAtomic[(size_t)i].store(mag, std::memory_order_relaxed);
        }
    }
}
