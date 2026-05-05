#pragma once

class BeatPulseEngine
{
public:
    void trigger();
    void advance(double dtSeconds);
    float getPulse() const noexcept { return pulse; }
private:
    float pulse = 0.0f;
};
