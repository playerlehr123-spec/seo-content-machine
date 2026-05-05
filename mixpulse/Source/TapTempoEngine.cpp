#include "TapTempoEngine.h"

void TapTempoEngine::tap(double now)
{
    taps[head] = now;
    head = (head + 1) % (int)taps.size();
    count = std::min(count + 1, (int)taps.size());
    if (count < 2) return;
    double sum = 0.0; int intervals = 0;
    for (int i = 1; i < count; ++i)
    {
        auto a = taps[(head - i + 4) % 4];
        auto b = taps[(head - i - 1 + 4) % 4];
        auto dt = a - b;
        if (dt > 0.0) { sum += dt; ++intervals; }
    }
    if (intervals == 0) return;
    auto b = 60.0 / (sum / intervals);
    bpm = (b >= 60.0 && b <= 200.0) ? std::optional<double>(b) : std::nullopt;
}
std::optional<double> TapTempoEngine::getBpm() const { return bpm; }
