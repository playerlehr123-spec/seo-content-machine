#include "CreatorTemplate.h"

const std::vector<CreatorTemplatePreset>& getBuiltInCreatorTemplates()
{
    static const std::vector<CreatorTemplatePreset> templates {
        { "Minimal Meter", "Utility", "Meter Overlay", VisualModuleType::SpectrumBars, 0, "WaveFrame", "Meter", "Clean producer meter with creator overlay optional.", "Current / 16:9", "Meter utility still or OBS capture", false, CreatorTemplateStatus::Implemented },
        { "Logo Reactor", "Artist/label identity", "Logo Reactor", VisualModuleType::LogoPulse, 2, "Listen", "Logo Pulse", "Centered brand mark with beat-reactive scale and glow.", "1:1 Square", "Artist or label identity post", true, CreatorTemplateStatus::Implemented },
        { "Release Announcement", "IG post / reel cover", "Promo Card", VisualModuleType::PromoCard, 3, "Out Now", "New Release", "Release card with artist, title, CTA, and reactive accent strip.", "4:5 Feed", "Release announcement still", true, CreatorTemplateStatus::Implemented },
        { "Label Drop", "Label social", "Promo Card", VisualModuleType::PromoCard, 2, "Out Now", "Label Drop", "Label-forward social card for roster or single drops.", "1:1 Square", "Label social still", true, CreatorTemplateStatus::Implemented },
        { "Stream Overlay", "OBS", "Stream Overlay", VisualModuleType::SpectrumBars, 5, "Live", "Live Set", "OBS-friendly visualizer layout with brand overlay placeholders.", "16:9", "OBS window capture", true, CreatorTemplateStatus::Placeholder },
        { "Reel Visualizer", "Reels/TikTok", "Type Pulse", VisualModuleType::TypePulse, 1, "Presave", "New Music", "Vertical text pulse and audio-reactive visual starter.", "9:16 Reel", "Short-form social still", true, CreatorTemplateStatus::Implemented },
        { "Album Motion", "Cover motion concept", "Particles", VisualModuleType::Particles, 2, "Listen", "Album Motion", "Album-art-inspired particle layout, still-frame only for now.", "1:1 Square", "Album motion concept still", true, CreatorTemplateStatus::Placeholder },
        { "Type Pulse", "Typography", "Type Pulse", VisualModuleType::TypePulse, 1, "Watch", "New Music", "Typography-first text pulse for artist/title messaging.", "9:16 Reel", "Lyric/title social still", true, CreatorTemplateStatus::Implemented },
        { "Particle Card", "Visual art", "Particles", VisualModuleType::Particles, 3, "Listen", "Out Now", "Particle field with brand text and feed-safe aspect.", "4:5 Feed", "Reactive artwork still", true, CreatorTemplateStatus::Placeholder },
        { "Spectrum Promo", "Visualizer promo", "Spectrum Bars", VisualModuleType::SpectrumBars, 4, "Watch", "Visualizer", "Classic spectrum visualizer with promo text overlay.", "16:9", "YouTube visualizer still", true, CreatorTemplateStatus::Implemented }
    };
    return templates;
}

juce::String creatorTemplateStatusLabel(CreatorTemplateStatus status)
{
    switch (status)
    {
        case CreatorTemplateStatus::Implemented: return "implemented";
        case CreatorTemplateStatus::Placeholder: return "placeholder";
        case CreatorTemplateStatus::Future: return "future";
    }
    return "unknown";
}
