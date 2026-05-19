#pragma once

#include <JuceHeader.h>
#include <vector>
#include "VisualRack.h"

struct CreatorTemplatePreset
{
    juce::String name;
    juce::String bestFor;
    juce::String moduleName;
    VisualModuleType module = VisualModuleType::SpectrumBars;
    int preferredExportPresetIndex = 0;
    juce::String ctaText;
    juce::String releaseStatusText;
};

const std::vector<CreatorTemplatePreset>& getBuiltInCreatorTemplates();
