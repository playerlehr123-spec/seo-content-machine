#pragma once

#include <JuceHeader.h>
#include <vector>

struct CreatorTemplatePreset
{
    juce::String name;
    juce::String bestFor;
    juce::String moduleName;
    int preferredExportPresetIndex = 0;
    juce::String ctaText;
};

const std::vector<CreatorTemplatePreset>& getBuiltInCreatorTemplates();
