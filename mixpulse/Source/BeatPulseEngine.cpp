#include "BeatPulseEngine.h"
void BeatPulseEngine::trigger() { pulse = 1.0f; }
void BeatPulseEngine::advance(double dt) { pulse *= std::exp((float)(-dt / 0.3)); }
