#pragma once
#include <JuceHeader.h>

class ThemeManager
{
public:
    struct Theme
    {
        juce::Colour background, panel, panelBorder, accent, secondary;
        juce::Colour left, right, text, mutedText, grid, glow, warningDot;
    };

    static Theme darkNeon();
};
