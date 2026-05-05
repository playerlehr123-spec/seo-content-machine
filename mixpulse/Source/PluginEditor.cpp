#include "PluginEditor.h"

MixPulseAudioProcessorEditor::MixPulseAudioProcessorEditor(MixPulseAudioProcessor& p) : AudioProcessorEditor(&p), processor(p), theme(ThemeManager::darkNeon())
{
    setWantsKeyboardFocus(true);
    setSize(1200,700); setResizeLimits(480,300,2000,1400);
    addAndMakeVisible(tapButton); addAndMakeVisible(visualizerButton); addAndMakeVisible(beatSyncButton);
    tapButton.onClick = [this]{ processor.tapTempo.tap(juce::Time::getMillisecondCounterHiRes()/1000.0); processor.beatPulse.trigger(); };
    beatSyncButton.onClick = [this]{ processor.visualizerState.beatSync = beatSyncButton.getToggleState(); };
    visualizerButton.onClick = [this]{ openVisualizer(); };
    startTimerHz(30);
}
MixPulseAudioProcessorEditor::~MixPulseAudioProcessorEditor() = default;
void MixPulseAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(theme.background);
    auto b = getLocalBounds().reduced(12);
    g.setColour(theme.panel); g.fillRoundedRectangle(b.toFloat(), 8.0f);
    g.setColour(theme.accent); g.setFont(24.0f); g.drawText("MixPulse", b.removeFromTop(36), juce::Justification::left);
    auto bpm = processor.tapTempo.getBpm();
    g.setFont(20.0f); g.drawText("BPM: " + (bpm ? juce::String(*bpm,1) : "--"), b.removeFromTop(28), juce::Justification::left);
}
void MixPulseAudioProcessorEditor::resized()
{
    auto r = getLocalBounds().reduced(20).removeFromTop(40);
    tapButton.setBounds(r.removeFromLeft(110)); r.removeFromLeft(10);
    beatSyncButton.setBounds(r.removeFromLeft(140)); r.removeFromLeft(10);
    visualizerButton.setBounds(r.removeFromLeft(170));
}
bool MixPulseAudioProcessorEditor::keyPressed(const juce::KeyPress& k)
{
    if (k.getTextCharacter()=='t' || k.getTextCharacter()=='T') { tapButton.triggerClick(); return true; }
    if (k.getTextCharacter()=='b' || k.getTextCharacter()=='B') { beatSyncButton.setToggleState(!beatSyncButton.getToggleState(), juce::sendNotification); return true; }
    if (k.getTextCharacter()=='v' || k.getTextCharacter()=='V') { processor.visualizerState.mode = VisualizerMode::SpectrumBars; return true; }
    if (k.getTextCharacter()=='r' || k.getTextCharacter()=='R') { processor.analyzer.getMeterData().clipLatched = false; return true; }
    if (k.getTextCharacter()=='s' || k.getTextCharacter()=='S') { exportScreenshot(); return true; }
    if (k.getTextCharacter()=='f' || k.getTextCharacter()=='F') { if (visualizer) visualizer->toggleFullscreen(); return true; }
    if (k == juce::KeyPress::escapeKey) { if (visualizer) visualizer->setFullScreen(false); return true; }
    return false;
}
void MixPulseAudioProcessorEditor::timerCallback() { repaint(); }
void MixPulseAudioProcessorEditor::openVisualizer() { if (!visualizer) visualizer = std::make_unique<VisualizerWindow>(processor.analyzer, processor.beatPulse, processor.visualizerState); visualizer->setVisible(true); visualizer->toFront(true); }
void MixPulseAudioProcessorEditor::exportScreenshot()
{
    if (!visualizer) return;
    auto* c = visualizer->getContentComponent(); if (!c) return;
    juce::Image img(juce::Image::ARGB, c->getWidth(), c->getHeight(), true);
    juce::Graphics g(img); c->paintEntireComponent(g, false);
    auto t = juce::Time::getCurrentTime();
    auto name = "MixPulse_Visualizer_" + t.formatted("%Y-%m-%d_%H-%M-%S") + ".png";
    auto f = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile(name);
    juce::PNGImageFormat png; juce::FileOutputStream os(f); if (os.openedOk()) png.writeImageToStream(img, os);
}
