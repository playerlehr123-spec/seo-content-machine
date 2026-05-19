#include "CreatorTemplate.h"

const std::vector<CreatorTemplatePreset>& getBuiltInCreatorTemplates()
{
    static const std::vector<CreatorTemplatePreset> templates {
        { "Minimal Meter", "Utility", "Meter Overlay", VisualModuleType::SpectrumBars, 0, "WaveFrame", "Meter" },
        { "Logo Reactor", "Artist/label identity", "Logo Reactor", VisualModuleType::LogoPulse, 2, "Listen", "Logo Pulse" },
        { "Release Announcement", "IG post / reel cover", "Promo Card", VisualModuleType::PromoCard, 3, "Out Now", "New Release" },
        { "Label Drop", "Label social", "Promo Card", VisualModuleType::PromoCard, 2, "Out Now", "Label Drop" },
        { "Stream Overlay", "OBS", "Stream Overlay", VisualModuleType::Particles, 5, "Live", "Live Set" },
        { "Reel Visualizer", "Reels/TikTok", "Type Pulse", VisualModuleType::TypePulse, 1, "Presave", "New Music" },
        { "Album Motion", "Cover motion concept", "Particles", VisualModuleType::Particles, 2, "Listen", "Album Motion" }
    };
    return templates;
}
