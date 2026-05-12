#pragma once
#include <array>
#include <optional>

class TapTempoEngine
{
public:
    void tap(double nowSeconds);
    std::optional<double> getBpm() const;
    bool isManualActive() const noexcept { return bpm.has_value(); }
private:
    static constexpr double resetThresholdSeconds = 2.5;
    std::array<double, 4> taps{};
    int count = 0;
    int head = 0;
    double lastTap = 0.0;
    std::optional<double> bpm;
};
