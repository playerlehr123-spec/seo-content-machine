#pragma once

#include <JuceHeader.h>
#include <vector>

enum class ExportPresetCategory { Current, Social, Cover, Stream, Future };

struct ExportPreset
{
    juce::String name;
    juce::String description;
    int width = 0;
    int height = 0;
    juce::String aspectLabel;
    juce::String useCase;
    ExportPresetCategory category = ExportPresetCategory::Current;
    bool enabled = true;
    bool futureVideoSupported = false;
};


const std::vector<ExportPreset>& getBuiltInExportPresets();
juce::String exportPresetShortLabel(int index);
juce::String exportPresetDimensionLabel(const ExportPreset& preset);
juce::String exportPresetWorkflowLabel(const ExportPreset& preset);
