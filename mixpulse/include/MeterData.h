#pragma once
#include <atomic>

struct MeterData
{
    std::atomic<float> peakL { 0.0f }, peakR { 0.0f };
    std::atomic<float> rmsL { 0.0f }, rmsR { 0.0f };
    std::atomic<float> samplePeakL {0.0f}, samplePeakR {0.0f};
    std::atomic<float> truePeak { 0.0f };
    std::atomic<bool> clipLatchedL { false }, clipLatchedR { false }, clipLatched { false };
    std::atomic<float> lufsM { -23.0f }, lufsS { -23.0f }, lufsI { -23.0f };
    std::atomic<bool> hasLufsM { true }, hasLufsS { false }, hasLufsI { false };
    std::atomic<float> bassEnergy {0.0f}, lowMidEnergy {0.0f}, midEnergy {0.0f}, highMidEnergy {0.0f}, highEnergy {0.0f};
};
