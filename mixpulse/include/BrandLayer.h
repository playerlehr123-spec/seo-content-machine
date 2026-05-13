#pragma once
#include <string>

namespace mixpulse {

enum class LogoPositionMode { Center, TopLeft, TopRight, BottomLeft, BottomRight, Watermark };

struct BrandLayerState {
    std::string artistName = "Artist Name";
    std::string trackTitle = "Track Title";
    std::string labelName = "WaveFrame";
    std::string callToAction = "Out Now";
    std::string releaseStatusText = "Out Now";
    std::string logoPath;
    bool hasLogo = false;
    float logoOpacity = 1.0f;
    float logoScale = 1.0f;
    LogoPositionMode logoPositionMode = LogoPositionMode::Watermark;
    std::string brandPrimaryColor = "#5B8CFF";
    std::string brandSecondaryColor = "#7C4DFF";
    std::string brandAccentColor = "#00E5FF";
};

}
