#pragma once
#include <JuceHeader.h>
#include <vector>

enum class WaveFrameToolStatus { Active, Beta, Planned, Research };

struct WaveFrameTool
{
    juce::String toolName;
    juce::String toolId;
    juce::String category;
    juce::String description;
    WaveFrameToolStatus status = WaveFrameToolStatus::Planned;
    bool supportsAudioReactivity = false;
    bool supportsPNGExport = false;
    bool supportsSVGExportFuture = false;
    bool supportsVideoExportFuture = false;
};

const std::vector<WaveFrameTool>& getBuiltInWaveFrameTools();
