#pragma once
#include <atomic>

struct MeterData
{
    std::atomic<float> peakL { 0.0f }, peakR { 0.0f };
    std::atomic<float> rmsL { 0.0f }, rmsR { 0.0f };
    std::atomic<float> truePeak { 0.0f }; // TODO: replace with oversampled dBTP.
    std::atomic<bool> clipLatched { false };
    std::atomic<float> lufsM { -23.0f }, lufsS { -23.0f }, lufsI { -23.0f }; // TODO: BS.1770.
};
