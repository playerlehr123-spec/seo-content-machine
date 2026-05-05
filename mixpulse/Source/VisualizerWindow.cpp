#include "VisualizerWindow.h"

VisualizerComponent::VisualizerComponent(AudioAnalyzer& a, BeatPulseEngine& p, VisualizerState& s) : analyzer(a), pulse(p), state(s) { startTimerHz(60); }
void VisualizerComponent::paint(juce::Graphics& g)
{
    static VisualizerRenderer renderer;
    renderer.render(g, getLocalBounds(), analyzer.getSpectrumSnapshot(), state.mode.load(), pulse.getPulse());
}
void VisualizerComponent::timerCallback() { pulse.advance(1.0 / 60.0); repaint(); }

VisualizerWindow::VisualizerWindow(AudioAnalyzer& a, BeatPulseEngine& p, VisualizerState& s)
    : juce::DocumentWindow("MixPulse Visualizer", juce::Colours::black, juce::DocumentWindow::allButtons)
{
    setUsingNativeTitleBar(true);
    setResizable(true, true);
    setContentOwned(new VisualizerComponent(a, p, s), true);
    centreWithSize(960, 540);
    setAlwaysOnTop(true); // Better deployment workflow for OBS + DAWs.
    setVisible(true);
}
void VisualizerWindow::closeButtonPressed() { setVisible(false); }
void VisualizerWindow::toggleFullscreen() { setFullScreen(!isFullScreen()); }
