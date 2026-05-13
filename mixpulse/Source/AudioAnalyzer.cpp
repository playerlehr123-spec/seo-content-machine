#include "../include/AudioAnalyzer.h"

#include <algorithm>
#include <array>
#include <limits>

namespace mixpulse {

namespace {
constexpr std::array<int, 6> kBandEdges { 0, 16, 48, 96, 160, 256 };

float bandAverage(const std::vector<float>& bins, int start, int end) noexcept
{
    const int safeStart = std::max(0, start);
    const int safeEnd = std::min(static_cast<int>(bins.size()), end);
    if (safeEnd <= safeStart)
        return 0.0f;

    float sum = 0.0f;
    for (int i = safeStart; i < safeEnd; ++i)
        sum += bins[static_cast<std::size_t>(i)];

    return sum / static_cast<float>(safeEnd - safeStart);
}
} // namespace

AudioAnalyzer::AudioAnalyzer(MeterData& meterDataRef)
    : meterData(meterDataRef)
{
}

float AudioAnalyzer::clamp01(float value) noexcept
{
    return std::clamp(value, 0.0f, 1.0f);
}

float AudioAnalyzer::sanitizeFinite(float value, float fallback) noexcept
{
    return std::isfinite(value) ? value : fallback;
}

float AudioAnalyzer::safeGainToDb(float gain, float floorDb) noexcept
{
    const float safeGain = std::max(sanitizeFinite(gain, 0.0f), std::numeric_limits<float>::min());
    const float db = 20.0f * std::log10(safeGain);
    return std::max(db, floorDb);
}

void AudioAnalyzer::analyzeBlock(const float* left, const float* right, int numSamples) noexcept
{
    if (left == nullptr || right == nullptr || numSamples <= 0)
        return;

    float maxL = 0.0f;
    float maxR = 0.0f;
    double rmsAccumL = 0.0;
    double rmsAccumR = 0.0;

    static thread_local std::vector<float> pseudoBins(256, 0.0f);

    for (int i = 0; i < numSamples; ++i) {
        const float l = sanitizeFinite(left[i]);
        const float r = sanitizeFinite(right[i]);
        const float absL = std::abs(l);
        const float absR = std::abs(r);

        maxL = std::max(maxL, absL);
        maxR = std::max(maxR, absR);
        rmsAccumL += static_cast<double>(l) * static_cast<double>(l);
        rmsAccumR += static_cast<double>(r) * static_cast<double>(r);

        const float mono = 0.5f * (absL + absR);
        const std::size_t idx = static_cast<std::size_t>(i) % pseudoBins.size();
        pseudoBins[idx] = 0.80f * pseudoBins[idx] + 0.20f * mono;
    }

    const float rmsL = std::sqrt(static_cast<float>(rmsAccumL / static_cast<double>(numSamples)));
    const float rmsR = std::sqrt(static_cast<float>(rmsAccumR / static_cast<double>(numSamples)));

    const float prevPeakL = meterData.peakL.load(std::memory_order_relaxed);
    const float prevPeakR = meterData.peakR.load(std::memory_order_relaxed);

    meterData.peakL.store(std::max(maxL, prevPeakL * peakDecay), std::memory_order_relaxed);
    meterData.peakR.store(std::max(maxR, prevPeakR * peakDecay), std::memory_order_relaxed);
    meterData.rmsL.store(rmsL, std::memory_order_relaxed);
    meterData.rmsR.store(rmsR, std::memory_order_relaxed);

    meterData.samplePeak.store(std::max(maxL, maxR), std::memory_order_relaxed);
    meterData.truePeak.store(meterData.samplePeak.load(std::memory_order_relaxed), std::memory_order_relaxed);
    meterData.lufsM.store(-23.0f + 9.0f * clamp01((rmsL + rmsR) * 0.5f), std::memory_order_relaxed);
    meterData.clipLatched.store(maxL >= 1.0f || maxR >= 1.0f, std::memory_order_relaxed);

    meterData.bassEnergy.store(clamp01(bandAverage(pseudoBins, kBandEdges[0], kBandEdges[1])), std::memory_order_relaxed);
    meterData.lowMidEnergy.store(clamp01(bandAverage(pseudoBins, kBandEdges[1], kBandEdges[2])), std::memory_order_relaxed);
    meterData.midEnergy.store(clamp01(bandAverage(pseudoBins, kBandEdges[2], kBandEdges[3])), std::memory_order_relaxed);
    meterData.highMidEnergy.store(clamp01(bandAverage(pseudoBins, kBandEdges[3], kBandEdges[4])), std::memory_order_relaxed);
    meterData.highEnergy.store(clamp01(bandAverage(pseudoBins, kBandEdges[4], kBandEdges[5])), std::memory_order_relaxed);
}

} // namespace mixpulse
