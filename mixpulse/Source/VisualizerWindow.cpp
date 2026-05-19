#include "VisualizerWindow.h"
#include "Branding.h"

VisualizerComponent::VisualizerComponent(AudioAnalyzer& a, BeatPulseEngine& p, VisualizerState& s, VisualRackState& r, BrandLayer::CreatorBrandState& b) : analyzer(a), pulse(p), state(s), rack(r), brand(b) { startTimerHz(60); }
void VisualizerComponent::paint(juce::Graphics& g)
{
    static VisualizerRenderer renderer;
    renderer.render(g, getLocalBounds(), analyzer.getSpectrumSnapshot(), state.mode.load(), pulse.getPulse(), rack, &brand);
}
void VisualizerComponent::timerCallback() { pulse.advance(1.0 / 60.0, state.beatSync.load()); repaint(); }

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
