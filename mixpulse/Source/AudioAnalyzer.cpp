#include "AudioAnalyzer.h"

void AudioAnalyzer::prepare(double, int)
{
    spectrum.assign(64, 0.0f);
}

void AudioAnalyzer::analyze(const juce::AudioBuffer<float>& buffer)
{
    auto n = buffer.getNumSamples();
    float pL = 0, pR = 0, eL = 0, eR = 0;
    for (int i=0;i<n;++i)
    {
        auto l = buffer.getSample(0, i);
        auto r = buffer.getNumChannels() > 1 ? buffer.getSample(1, i) : l;
        pL = std::max(pL, std::abs(l)); pR = std::max(pR, std::abs(r));
        eL += l*l; eR += r*r;
    }
    meter.peakL = pL; meter.peakR = pR;
    meter.rmsL = std::sqrt(eL / std::max(1,n)); meter.rmsR = std::sqrt(eR / std::max(1,n));
    meter.truePeak = std::max(pL,pR);
    if (pL >= 0.999f || pR >= 0.999f) meter.clipLatched = true;
    meter.lufsM = juce::Decibels::gainToDecibels(std::max(1.0e-6f, (meter.rmsL.load()+meter.rmsR.load())*0.5f));

    if (n >= 1024)
    {
        std::fill(fftData.begin(), fftData.end(), 0.0f);
        juce::FloatVectorOperations::copy(fftData.data(), buffer.getReadPointer(0), 1024);
        window.multiplyWithWindowingTable(fftData.data(), 1024);
        fft.performFrequencyOnlyForwardTransform(fftData.data());
        for (size_t i=0;i<spectrum.size();++i) spectrum[i]=juce::jlimit(0.0f,1.0f,fftData[i]/128.0f);
    }
}
