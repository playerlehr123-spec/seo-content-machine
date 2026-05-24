#include "VisualizerWindow.h"
#include "Branding.h"

VisualizerComponent::VisualizerComponent(AudioAnalyzer& a, BeatPulseEngine& p, VisualizerState& s, VisualRackState& r, BrandLayer::CreatorBrandState& b) : analyzer(a), pulse(p), state(s), rack(r), brand(b) { startTimerHz(60); }
void VisualizerComponent::paint(juce::Graphics& g)
{
    static VisualizerRenderer renderer;
    renderer.render(g, getLocalBounds(), analyzer.getSpectrumSnapshot(), state.mode.load(), pulse.getPulse(), rack, &brand);
    drawCaptureOverlay(g, getLocalBounds());
}
void VisualizerComponent::timerCallback() { pulse.advance(1.0 / 60.0, state.beatSync.load()); repaint(); }

juce::String VisualizerComponent::aspectLabelForPreset(OutputPreset preset)
{
    switch (preset)
    {
        case OutputPreset::Portrait9x16: return "9:16 / 1080x1920";
        case OutputPreset::Square1x1: return "1:1 / 1080x1080";
        case OutputPreset::Portrait4x5: return "4:5 / 1080x1350";
        case OutputPreset::Landscape16x9:
        case OutputPreset::Thumbnail16x9: return "16:9 / 1920x1080";
        case OutputPreset::Free:
        default: return "Current window";
    }
}

void VisualizerComponent::drawCaptureOverlay(juce::Graphics& g, juce::Rectangle<int> bounds)
{
    const auto module = (VisualModuleType) rack.selectedModule.load();
    const auto preset = (OutputPreset) rack.outputPreset.load();
    auto top = bounds.reduced(18).removeFromTop(52).toFloat();

    g.setColour(juce::Colour::fromRGB(3, 7, 13).withAlpha(0.70f));
    g.fillRoundedRectangle(top, 10.0f);
    g.setColour(juce::Colour::fromRGB(34, 211, 238).withAlpha(0.45f));
    g.drawRoundedRectangle(top, 10.0f, 1.0f);

    auto text = top.toNearestInt().reduced(14, 7);
    auto left = text.removeFromLeft(260);
    g.setColour(juce::Colours::white.withAlpha(0.90f));
    g.setFont(juce::Font(15.0f, juce::Font::bold));
    g.drawText(juce::String(Branding::ProductDisplayName) + " Output", left.removeFromTop(20), juce::Justification::centredLeft);
    g.setColour(juce::Colour::fromRGB(160, 255, 120).withAlpha(0.86f));
    g.setFont(11.0f);
    g.drawText("OBS Window Capture ready", left, juce::Justification::centredLeft);

    g.setColour(juce::Colours::white.withAlpha(0.72f));
    g.setFont(12.0f);
    g.drawText(juce::String("Module: ") + visualModuleName(module), text.removeFromLeft(190), juce::Justification::centredLeft);
    g.drawText(juce::String("Aspect: ") + aspectLabelForPreset(preset), text.removeFromLeft(190), juce::Justification::centredLeft);
    g.drawText("Still PNG only / video export future", text, juce::Justification::centredLeft);
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
void VisualizerWindow::closeButtonPressed() { setVisible(false); }
void VisualizerWindow::toggleFullscreen() { setFullScreen(!isFullScreen()); }
