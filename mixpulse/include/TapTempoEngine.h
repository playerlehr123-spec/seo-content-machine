#pragma once
#include <array>
#include <optional>

class TapTempoEngine
{
public:
    void tap(double nowSeconds);
    std::optional<double> getBpm() const;
private:
    std::array<double, 4> taps{};
    int count = 0;
    int head = 0;
    std::optional<double> bpm;
};
