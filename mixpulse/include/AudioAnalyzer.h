#pragma once

#include <vector>
#include <cmath>

#include "MeterData.h"

namespace mixpulse {

class AudioAnalyzer {
public:
    explicit AudioAnalyzer(MeterData& meterDataRef);

    void analyzeBlock(const float* left, const float* right, int numSamples) noexcept;

    static float clamp01(float value) noexcept;
    static float sanitizeFinite(float value, float fallback = 0.0f) noexcept;
    static float safeGainToDb(float gain, float floorDb = -120.0f) noexcept;

private:
    MeterData& meterData;
    float peakDecay = 0.96f;
};

} // namespace mixpulse
