#include "CreatorTemplate.h"

const std::vector<CreatorTemplatePreset>& getBuiltInCreatorTemplates()
{
    static const std::vector<CreatorTemplatePreset> templates {
        { "Release Announcement", "IG post / reel cover", "Release Promo Card", VisualModuleType::TextCard, 3, "Out Now", "New Release" },
        { "New Music Teaser", "Reels/TikTok", "Reel Visualizer", VisualModuleType::SpectrumBars, 1, "Presave / Out Now", "Teaser" },
        { "Label Drop", "Label social", "Logo Reactor", VisualModuleType::LogoPulse, 2, "Out Now", "Label Drop" },
        { "DJ Stream Overlay", "OBS", "Stream Overlay", VisualModuleType::SpectrumBars, 5, "Live", "Live Set" },
        { "YouTube Thumbnail", "YouTube", "Promo Card", VisualModuleType::TextCard, 4, "Visualizer / Live Set", "Watch Now" },
        { "Minimal Meter", "Utility", "Meter Overlay", VisualModuleType::SpectrumBars, 0, "WaveFrame", "Meter" }
    };
    return templates;
}
