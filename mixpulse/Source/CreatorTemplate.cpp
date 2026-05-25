#include "CreatorTemplate.h"

const std::vector<CreatorTemplatePreset>& getBuiltInCreatorTemplates()
{
    static const std::vector<CreatorTemplatePreset> templates {
        { "Minimal Meter", "Clean metering overlay with brand text kept subtle.", "Producer utility / quick level check", "Spectrum Bars", VisualModuleType::SpectrumBars, 0, "WaveFrame", "Meter", "implemented" },
        { "Logo Reactor", "Centered brand mark that pulses with the beat.", "Artist or label identity post", "Logo Reactor", VisualModuleType::LogoPulse, 2, "Listen", "Logo Pulse", "implemented" },
        { "Release Announcement", "Social release card with title, label, CTA, and reactive accent.", "IG feed / reel cover", "Promo Card", VisualModuleType::PromoCard, 3, "Out Now", "New Release", "implemented" },
        { "Label Drop", "Label-forward promo card for catalog or compilation posts.", "Label social post", "Promo Card", VisualModuleType::PromoCard, 2, "Out Now", "Label Drop", "implemented" },
        { "Stream Overlay", "Wide layout for OBS capture with music status visible.", "OBS / livestream capture", "Spectrum Bars", VisualModuleType::SpectrumBars, 5, "Live", "Live Set", "placeholder" },
        { "Reel Visualizer", "Vertical social visualizer recommendation for short clips.", "Reels / TikTok / Shorts", "Particles", VisualModuleType::Particles, 1, "Presave", "New Music", "placeholder" },
        { "Album Motion", "Square cover-motion concept using text and particles.", "Album art motion concept", "Type Pulse", VisualModuleType::TypePulse, 2, "Listen", "Album Motion", "placeholder" },
        { "Type Pulse", "Large audio-reactive text treatment for artist and title.", "Lyric/title teaser", "Type Pulse", VisualModuleType::TypePulse, 1, "Listen / Watch", "Type Pulse", "implemented" },
        { "Particle Card", "Particle field with simple brand overlay and CTA.", "Visualizer card / teaser", "Particles", VisualModuleType::Particles, 2, "Watch", "Particle Card", "placeholder" },
        { "Spectrum Promo", "Spectrum bars with promo text and still-frame framing.", "Classic visualizer promo", "Spectrum Bars", VisualModuleType::SpectrumBars, 4, "Listen", "Spectrum Promo", "implemented" }
    };
    return templates;
}

int sanitizeCreatorTemplateIndex(int value)
{
    const auto& templates = getBuiltInCreatorTemplates();
    if (templates.empty())
        return 0;

    return juce::jlimit(0, (int)templates.size() - 1, value);
}

juce::String creatorTemplateStatusLabel(const CreatorTemplatePreset& preset)
{
    if (preset.status.equalsIgnoreCase("implemented"))
        return "Implemented";

    if (preset.status.equalsIgnoreCase("placeholder"))
        return "Placeholder";

    return "Future/TODO";
}
