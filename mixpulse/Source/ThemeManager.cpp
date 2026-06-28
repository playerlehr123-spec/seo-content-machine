#include "ThemeManager.h"

ThemeManager::Theme ThemeManager::darkNeon()
{
    return {
        juce::Colour::fromString("ff07090d"),
        juce::Colour::fromString("ff0d1118"),
        juce::Colour::fromString("ff252c38"),
        juce::Colour::fromString("ff31d7ff"),
        juce::Colour::fromString("ffff3d9a"),
        juce::Colour::fromString("ff39e6c6"), juce::Colour::fromString("ffff6a2a"),
        juce::Colour::fromString("fff2f5f8"), juce::Colour::fromString("ff8793a3"),
        juce::Colour::fromString("ff1b2633"), juce::Colour::fromString("ffff8a24"), juce::Colour::fromString("ffff304f")
    };
}
