#pragma once
#include <JuceHeader.h>

namespace BrandLayer
{
    enum class LogoPositionMode { Center, CornerTopLeft, CornerTopRight, CornerBottomLeft, CornerBottomRight, Watermark };

    struct CreatorBrandState
    {
        juce::String artistName { "Artist Name" };
        juce::String trackTitle { "Track Title" };
        juce::String labelName { "Label Name" };
        juce::String callToAction { "Out Now" };
        juce::String releaseStatusText { "Out Now" };
        juce::String logoPath;
        bool hasLogo = false;
        bool showLogoPlaceholder = true;
        bool showTextOverlay = true;
        float logoOpacity = 0.85f;
        float logoScale = 1.0f;
        int logoPositionMode = (int) LogoPositionMode::Center;
        juce::Colour brandPrimaryColor { juce::Colour::fromRGB(32, 218, 255) };
        juce::Colour brandSecondaryColor { juce::Colour::fromRGB(20, 30, 50) };
        juce::Colour brandAccentColor { juce::Colour::fromRGB(255, 220, 120) };
        juce::Colour brandBackgroundColor { juce::Colour::fromRGB(6, 9, 18) };
        juce::Colour brandTextColor { juce::Colours::white };
    };

    bool savePreset(const CreatorBrandState&, const juce::File&);
    bool loadPreset(CreatorBrandState&, const juce::File&);
    juce::File defaultPresetFile();
}
