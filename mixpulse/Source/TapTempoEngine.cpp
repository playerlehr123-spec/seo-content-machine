#include "TapTempoEngine.h"

void TapTempoEngine::tap(double now)
{
    if (lastTap > 0.0 && (now - lastTap) > resetThresholdSeconds)
    {
        count = 0;
        head = 0;
    }

    lastTap = now;
    taps[(size_t)head] = now;
    head = (head + 1) % (int)taps.size();
    count = std::min(count + 1, (int)taps.size());

    if (count < 2)
    {
        bpm = std::nullopt;
        return;
    }

    double sum = 0.0;
    int intervals = 0;
    for (int i = 1; i < count; ++i)
    {
        const auto a = taps[(head - i + 4) % 4];
        const auto b = taps[(head - i - 1 + 4) % 4];
        const auto dt = a - b;
        if (dt > 0.0) { sum += dt; ++intervals; }
    }

    if (intervals == 0) { bpm = std::nullopt; return; }
    const auto candidate = 60.0 / (sum / intervals);
    bpm = (candidate >= 60.0 && candidate <= 200.0) ? std::optional<double>(candidate) : std::nullopt;
}
std::optional<double> TapTempoEngine::getBpm() const { return bpm; }
