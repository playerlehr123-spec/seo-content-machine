#include "ExportPreset.h"

const std::vector<ExportPreset>& getBuiltInExportPresets()
{
    static const std::vector<ExportPreset> presets {
        { "Current Window", "Still PNG using current output/editor size", 0, 0, "Current", ExportPresetCategory::Current, true, false },
        { "9:16 Reel / TikTok / Shorts", "Still PNG 1080x1920", 1080, 1920, "9:16", ExportPresetCategory::Social, true, false },
        { "1:1 Square Post", "Still PNG 1080x1080", 1080, 1080, "1:1", ExportPresetCategory::Social, true, false },
        { "4:5 Feed Post", "Still PNG 1080x1350", 1080, 1350, "4:5", ExportPresetCategory::Social, true, false },
        { "16:9 YouTube / Visualizer", "Still PNG 1920x1080", 1920, 1080, "16:9", ExportPresetCategory::Cover, true, false },
        { "16:9 Stream Overlay", "Still PNG 1920x1080", 1920, 1080, "16:9", ExportPresetCategory::Stream, true, false },
        { "Album Art Still", "Future high-res still", 3000, 3000, "1:1", ExportPresetCategory::Future, false, false },
        { "Spotify Canvas-style 9:16", "Video export future", 1080, 1920, "9:16", ExportPresetCategory::Future, false, true }
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
