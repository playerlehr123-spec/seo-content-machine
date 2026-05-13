#pragma once
#include <string>
namespace mixpulse {
class VisualizerWindow {
public:
    std::string getWindowTitle() const { return "WaveFrame Output"; }
    bool supportsEscapeExit() const { return true; }
    bool supportsFullscreen() const { return true; }
};
}
