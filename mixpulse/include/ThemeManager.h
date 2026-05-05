#pragma once
#include <JuceHeader.h>

class ThemeManager
{
public:
    struct Theme
    {
        juce::Colour background;
        juce::Colour panel;
        juce::Colour accent;
        juce::Colour secondary;
        juce::Colour left;
        juce::Colour right;
    };

    static Theme darkNeon();
};
