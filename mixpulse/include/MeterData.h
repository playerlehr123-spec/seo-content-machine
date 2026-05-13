#pragma once

#include <atomic>

namespace mixpulse {

struct MeterData {
    std::atomic<float> peakL { 0.0f };
    std::atomic<float> peakR { 0.0f };
    std::atomic<float> rmsL { 0.0f };
    std::atomic<float> rmsR { 0.0f };

    // Placeholders until true implementation exists.
    std::atomic<float> samplePeak { 0.0f };
    std::atomic<float> truePeak { 0.0f };
    std::atomic<float> lufsM { -23.0f };

    std::atomic<bool> clipLatched { false };

    std::atomic<float> bassEnergy { 0.0f };
    std::atomic<float> lowMidEnergy { 0.0f };
    std::atomic<float> midEnergy { 0.0f };
    std::atomic<float> highMidEnergy { 0.0f };
    std::atomic<float> highEnergy { 0.0f };

    static constexpr float meterTicksDb[6] = { 0.0f, -3.0f, -6.0f, -9.0f, -12.0f, -24.0f };
    static constexpr float lufsRefDb[4] = { -6.0f, -12.0f, -14.0f, -23.0f };
};

} // namespace mixpulse
