#include "CreatorTemplate.h"

const std::vector<CreatorTemplatePreset>& getBuiltInCreatorTemplates()
{
    static const std::vector<CreatorTemplatePreset> templates {
        { "Release Announcement", "IG post / reel cover", "Release Promo Card", 3, "Out Now" },
        { "New Music Teaser", "Reels/TikTok", "Reel Visualizer", 1, "Presave / Out Now" },
        { "Label Drop", "Label social", "Logo Reactor", 2, "Out Now" },
        { "DJ Stream Overlay", "OBS", "Stream Overlay", 5, "Live" },
        { "YouTube Thumbnail", "YouTube", "Promo Card", 4, "Visualizer / Live Set" },
        { "Minimal Meter", "Utility", "Meter Overlay", 0, "WaveFrame" }
    };
    return templates;
}
