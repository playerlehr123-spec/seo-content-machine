#include "../include/CreatorTemplate.h"

namespace mixpulse {
std::vector<CreatorTemplate> builtInCreatorTemplates()
{
    return {
        {"Release Announcement", "Launch card for track release", "Release Promo Card", "16:9", "Brand Layer", "Artist Name - Track Title | Out Now"},
        {"New Music Teaser", "Short visual teaser", "Gradient Field", "9:16", "Visualizer", "New Music Friday"},
        {"Label Drop", "Label identity splash", "Logo Reactor", "1:1", "Brand Layer", "WaveFrame Presents"},
        {"DJ Stream Overlay", "HUD style streaming overlay", "Meter Overlay", "16:9", "Meter Rack", "Live on Stream"},
        {"YouTube Thumbnail", "High contrast thumbnail layout", "Release Promo Card", "Thumbnail 16:9", "Brand Layer", "OUT NOW"},
        {"Minimal Meter", "Clean utility metering", "Waveform", "Free", "Analyzer", "Minimal Meter"},
    };
}
}
