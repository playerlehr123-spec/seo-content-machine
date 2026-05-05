#include <cmath>
#include <JuceHeader.h>
#include "BeatPulseEngine.h"

void BeatPulseEngine::trigger(double bpmHint)
{
    pulse = 1.0f;
    beatJustTriggered = true;
    secondsSinceBeat = 0.0f;
    if (bpmHint > 0.0) bpm = (float)bpmHint;
}

void BeatPulseEngine::advance(double dt, bool beatSyncEnabled)
{
    beatJustTriggered = false;
    secondsSinceBeat += (float)dt;
    beatDecay += (float)dt;
    pulse *= std::exp((float)(-dt / 0.3));

    if (beatSyncEnabled && bpm > 0.0f)
    {
        const auto beatSeconds = 60.0f / bpm;
        if (secondsSinceBeat >= beatSeconds)
            trigger(bpm);
        beatPhase = juce::jlimit(0.0f, 1.0f, secondsSinceBeat / beatSeconds);
    }
}
