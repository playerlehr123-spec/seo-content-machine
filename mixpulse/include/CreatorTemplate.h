#pragma once

#include <JuceHeader.h>
#include <vector>
#include "VisualRack.h"

enum class CreatorTemplateStatus { Implemented, Placeholder, Future };

struct CreatorTemplatePreset
{
    juce::String name;
    juce::String bestFor;
    juce::String moduleName;
    VisualModuleType module = VisualModuleType::SpectrumBars;
    int preferredExportPresetIndex = 0;
    juce::String ctaText;
    juce::String releaseStatusText;
    juce::String shortDescription;
    juce::String preferredAspectRatio;
    juce::String exportUseCase;
    bool brandTextVisible = true;
    CreatorTemplateStatus status = CreatorTemplateStatus::Placeholder;
};

const std::vector<CreatorTemplatePreset>& getBuiltInCreatorTemplates();
juce::String creatorTemplateStatusLabel(CreatorTemplateStatus status);
