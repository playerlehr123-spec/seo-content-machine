#include "ExportPreset.h"

const std::vector<ExportPreset>& getBuiltInExportPresets()
{
    static const std::vector<ExportPreset> presets {
        { "Current Window", "Uses current output/editor size", 0, 0, "Current", "manual preview or OBS window capture", ExportPresetCategory::Current, true, false },
        { "Vertical Reel / Story", "Still PNG 1080x1920", 1080, 1920, "9:16", "reels, shorts, stories", ExportPresetCategory::Social, true, false },
        { "Square Post", "Still PNG 1080x1080", 1080, 1080, "1:1", "feed post or cover visual", ExportPresetCategory::Social, true, false },
        { "Feed Portrait", "Still PNG 1080x1350", 1080, 1350, "4:5", "Instagram feed portrait", ExportPresetCategory::Social, true, false },
        { "Wide / YouTube", "Still PNG 1920x1080", 1920, 1080, "16:9", "YouTube thumbnail or visualizer", ExportPresetCategory::Cover, true, false },
        { "Wide / Stream Overlay", "Still PNG 1920x1080", 1920, 1080, "16:9", "OBS and stream overlay", ExportPresetCategory::Stream, true, false },
        { "Album Art Still", "Future high-res still", 3000, 3000, "1:1", "future high-res cover still", ExportPresetCategory::Future, false, false },
        { "Canvas-style Motion", "Video export future/TODO", 1080, 1920, "9:16", "future motion export research", ExportPresetCategory::Future, false, true }
    };
    return presets;
}

juce::String exportPresetShortLabel(int index)
{
    switch (index)
    {
        case 0: return "Current";
        case 1: return "Reel";
        case 2: return "Square";
        case 3: return "Feed";
        case 4: return "Thumb";
        case 5: return "Stream";
        case 6: return "Album";
        case 7: return "Canvas";
        default: return "Preset";
    }
}

juce::String exportPresetDimensionLabel(const ExportPreset& preset)
{
    if (preset.width > 0 && preset.height > 0)
        return juce::String(preset.width) + "x" + juce::String(preset.height);

    return "current window";
}

juce::String exportPresetWorkflowLabel(const ExportPreset& preset)
{
    if (!preset.enabled)
        return preset.futureVideoSupported ? "Future video/TODO" : "Future/TODO";

    return "Still PNG";
}
