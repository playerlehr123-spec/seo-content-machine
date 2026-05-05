#include "ThemeManager.h"

ThemeManager::Theme ThemeManager::darkNeon()
{
    return {
        juce::Colour::fromHSL(228.0f / 360.0f, 0.30f, 0.05f, 1.0f),
        juce::Colour::fromHSL(228.0f / 360.0f, 0.35f, 0.04f, 1.0f),
        juce::Colour::fromHSL(228.0f / 360.0f, 0.35f, 0.12f, 1.0f),
        juce::Colour::fromHSL(185.0f / 360.0f, 1.0f, 0.5f, 1.0f),
        juce::Colour::fromHSL(285.0f / 360.0f, 0.8f, 0.62f, 1.0f),
        juce::Colour::fromString("ff38bdf8"), juce::Colour::fromString("fffb923c"),
        juce::Colours::white, juce::Colours::lightgrey,
        juce::Colour::fromString("5538bdf8"), juce::Colour::fromString("aa22d3ee"), juce::Colours::red
    };
}
