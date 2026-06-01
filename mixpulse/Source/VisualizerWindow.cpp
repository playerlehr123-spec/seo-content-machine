#include "VisualizerWindow.h"
#include "Branding.h"

namespace
{
struct OutputGuideInfo
{
    float ratio = 16.0f / 9.0f;
    juce::String label { "16:9" };
    juce::String dimensions { "1920x1080" };
    bool fixedAspect = true;
};

OutputGuideInfo getOutputGuideInfo(OutputPreset preset)
{
    switch (preset)
    {
        case OutputPreset::Portrait9x16: return { 9.0f / 16.0f, "9:16 Reel", "1080x1920", true };
        case OutputPreset::Square1x1: return { 1.0f, "1:1 Square", "1080x1080", true };
        case OutputPreset::Portrait4x5: return { 4.0f / 5.0f, "4:5 Feed", "1080x1350", true };
        case OutputPreset::Thumbnail16x9: return { 16.0f / 9.0f, "16:9 Thumbnail", "1920x1080", true };
        case OutputPreset::Landscape16x9: return { 16.0f / 9.0f, "16:9 Output", "1920x1080", true };
        case OutputPreset::Free:
        default: return { 16.0f / 9.0f, "Current window", "current size", false };
    }
}
}

VisualizerComponent::VisualizerComponent(AudioAnalyzer& a, BeatPulseEngine& p, VisualizerState& s, VisualRackState& r, BrandLayer::CreatorBrandState& b) : analyzer(a), pulse(p), state(s), rack(r), brand(b) { startTimerHz(60); }
void VisualizerComponent::paint(juce::Graphics& g)
{
    static VisualizerRenderer renderer;
    renderer.render(g, getLocalBounds(), analyzer.getSpectrumSnapshot(), state.mode.load(), pulse.getPulse(), rack, &brand);
    drawCaptureOverlay(g);
}
void VisualizerComponent::timerCallback() { pulse.advance(1.0 / 60.0, state.beatSync.load()); repaint(); }

void VisualizerComponent::drawCaptureOverlay(juce::Graphics& g)
{
    const auto bounds = getLocalBounds().toFloat();
    if (bounds.getWidth() < 160.0f || bounds.getHeight() < 120.0f)
        return;

    const auto info = getOutputGuideInfo((OutputPreset) sanitizeOutputPresetIndex(rack.outputPreset.load()));
    auto guide = bounds.reduced(24.0f);
    if (info.fixedAspect)
    {
        float w = guide.getWidth();
        float h = w / info.ratio;
        if (h > guide.getHeight())
        {
            h = guide.getHeight();
            w = h * info.ratio;
        }
        guide = juce::Rectangle<float>(w, h).withCentre(guide.getCentre());
    }

    g.setColour(juce::Colours::white.withAlpha(0.11f));
    g.drawRoundedRectangle(guide, 8.0f, 1.2f);

    auto safeArea = guide.reduced(guide.getWidth() * 0.08f, guide.getHeight() * 0.08f);
    g.setColour(juce::Colour::fromRGB(80, 255, 160).withAlpha(0.18f));
    g.drawRoundedRectangle(safeArea, 6.0f, 1.0f);

    auto pill = getLocalBounds().reduced(18).removeFromTop(34).toFloat();
    g.setColour(juce::Colour::fromRGB(6, 9, 18).withAlpha(0.76f));
    g.fillRoundedRectangle(pill, 10.0f);
    g.setColour(juce::Colour::fromRGB(32, 218, 255).withAlpha(0.45f));
    g.drawRoundedRectangle(pill, 10.0f, 1.0f);
    g.setColour(juce::Colours::white.withAlpha(0.88f));
    g.setFont(13.0f);
    g.drawText("OBS Capture Mode  /  " + info.label + "  /  " + info.dimensions + "  /  Still PNG only",
               pill.toNearestInt().reduced(12, 0), juce::Justification::centredLeft);

    auto footer = getLocalBounds().reduced(18).removeFromBottom(28);
    g.setColour(juce::Colours::white.withAlpha(0.42f));
    g.setFont(12.0f);
    g.drawText("Use OBS Window Capture for motion. Video export, NDI, Spout/Syphon, and virtual camera are future/TODO.",
               footer, juce::Justification::centredRight);
}

VisualizerWindow::VisualizerWindow(AudioAnalyzer& a, BeatPulseEngine& p, VisualizerState& s, VisualRackState& r, BrandLayer::CreatorBrandState& b)
    : juce::DocumentWindow(juce::String(Branding::OutputWindowName), juce::Colours::black, juce::DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setResizable(true, true);
    setContentOwned(new VisualizerComponent(a, p, s, r, b), true);
    centreWithSize(960, 540);
    setAlwaysOnTop(true); // Better deployment workflow for OBS + DAWs.
    setVisible(true);
}
void VisualizerWindow::closeButtonPressed()
{
    if (isFullScreen())
        setFullScreen(false);

    setVisible(false);
}

void VisualizerWindow::prepareToShow()
{
    if (isFullScreen())
        setFullScreen(false);

    if (getWidth() < 320 || getHeight() < 180)
        centreWithSize(960, 540);

    setVisible(true);
    toFront(true);
}

void VisualizerWindow::toggleFullscreen()
{
    if (!isVisible())
        prepareToShow();

    setFullScreen(!isFullScreen());
}
