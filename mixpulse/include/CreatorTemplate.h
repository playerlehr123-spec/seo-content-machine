#pragma once

#include <JuceHeader.h>
#include <vector>
#include "VisualRack.h"

struct CreatorTemplatePreset
{
    juce::String name;
    juce::String description;
    juce::String bestFor;
    juce::String moduleName;
    VisualModuleType module = VisualModuleType::SpectrumBars;
    int preferredExportPresetIndex = 0;
    juce::String ctaText;
    juce::String releaseStatusText;
    juce::String status;
};

const std::vector<CreatorTemplatePreset>& getBuiltInCreatorTemplates();
int sanitizeCreatorTemplateIndex(int value);
juce::String creatorTemplateStatusLabel(const CreatorTemplatePreset& preset);
