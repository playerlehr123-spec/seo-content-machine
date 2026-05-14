#include "AudioAnalyzer.h"

void AudioAnalyzer::prepare(double, int)
{
    fftFifo.fill(0.0f);
    fftFifoIndex = 0;
    for (auto& s : spectrumAtomic) s.store(0.0f, std::memory_order_relaxed);
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

    for (int i = 0; i < n; ++i)
    {
        const auto l = buffer.getSample(0, i);
        const auto r = channels > 1 ? buffer.getSample(1, i) : l;
        fftFifo[(size_t)fftFifoIndex++] = 0.5f * (l + r);
        if (fftFifoIndex >= fftSize)
        {
            fftFifoIndex = 0;
            std::fill(fftData.begin(), fftData.end(), 0.0f);
            juce::FloatVectorOperations::copy(fftData.data(), fftFifo.data(), fftSize);
            window.multiplyWithWindowingTable(fftData.data(), fftSize);
            fft.performFrequencyOnlyForwardTransform(fftData.data());

            float bass=0, lowMid=0, mid=0, highMid=0, high=0; int cb=0,cl=0,cm=0,chm=0,ch=0;
            for (int b = 0; b < spectrumBins; ++b)
            {
                const auto mag = juce::jlimit(0.0f, 1.0f, fftData[(size_t)b] / 128.0f);
                const auto prev = spectrumAtomic[(size_t)b].load(std::memory_order_relaxed);
                const auto smoothed = juce::jlimit(0.0f, 1.0f, mag > prev ? (prev + (mag - prev) * 0.45f) : (prev + (mag - prev) * 0.12f));
                spectrumAtomic[(size_t)b].store(smoothed, std::memory_order_relaxed);
                if (b < 8) { bass += smoothed; ++cb; }
                else if (b < 16) { lowMid += smoothed; ++cl; }
                else if (b < 28) { mid += smoothed; ++cm; }
                else if (b < 44) { highMid += smoothed; ++chm; }
                else { high += smoothed; ++ch; }
            }
            meter.bassEnergy.store(cb?bass/cb:0.0f, std::memory_order_relaxed);
            meter.lowMidEnergy.store(cl?lowMid/cl:0.0f, std::memory_order_relaxed);
            meter.midEnergy.store(cm?mid/cm:0.0f, std::memory_order_relaxed);
            meter.highMidEnergy.store(chm?highMid/chm:0.0f, std::memory_order_relaxed);
            meter.highEnergy.store(ch?high/ch:0.0f, std::memory_order_relaxed);
        }
    }
}

