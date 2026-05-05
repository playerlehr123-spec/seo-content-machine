#pragma once

class BeatPulseEngine
{
public:
    void trigger(double bpmHint = 0.0);
    void advance(double dtSeconds, bool beatSyncEnabled = true);

    float getPulse() const noexcept { return pulse; }
    bool getBeatJustTriggered() const noexcept { return beatJustTriggered; }
    float getSecondsSinceBeat() const noexcept { return secondsSinceBeat; }
    float getBeatPhase() const noexcept { return beatPhase; }

private:
    float pulse = 0.0f;
    bool beatJustTriggered = false;
    float secondsSinceBeat = 0.0f;
    float beatPhase = 0.0f;
    float beatDecay = 0.0f;
    float bpm = 0.0f;
};
