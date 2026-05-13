#pragma once
#include <string>
#include <vector>

namespace mixpulse {

enum class OutputAspectGuide { Free, Aspect16x9, Aspect1x1, Aspect9x16, Aspect4x5, Thumbnail16x9 };

enum class PlaceholderRenderMode { LogoReactor, ReleasePromoCard, MeterOverlay, Waveform, Vectorscope, GradientField, ParticleBurst, Tunnel, Plasma };

struct VisualFxSettings {
    bool bloom = true;
    bool mirror = false;
    bool colorize = true;
    bool grid = true;
    bool scanlines = false;
    bool chromaticSplit = false;
    bool vignette = true;
};

class VisualizerRenderer {
public:
    std::string getOutputTitle() const { return "WaveFrame Output"; }
};

} // namespace mixpulse
