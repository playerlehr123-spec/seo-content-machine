#include "PluginEditor.h"

MixPulseAudioProcessorEditor::MixPulseAudioProcessorEditor(MixPulseAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p), theme(ThemeManager::darkNeon())
{
    setWantsKeyboardFocus(true);
    setSize(1200, 700);
    setResizeLimits(480, 300, 2000, 1400);

    addAndMakeVisible(tapButton);
    addAndMakeVisible(visualizerButton);
    addAndMakeVisible(beatSyncButton);

    tapButton.onClick = [this]
    {
        processor.tapTempo.tap(juce::Time::getMillisecondCounterHiRes() / 1000.0);
        processor.beatPulse.trigger();
    };

    beatSyncButton.onClick = [this] { processor.visualizerState.beatSync = beatSyncButton.getToggleState(); };
    visualizerButton.onClick = [this] { openVisualizer(); };

    startTimerHz(30);
}

MixPulseAudioProcessorEditor::~MixPulseAudioProcessorEditor() = default;

void MixPulseAudioProcessorEditor::drawVerticalBar(juce::Graphics& g, juce::Rectangle<float> area, float value, juce::Colour baseColor, const juce::String& label)
{
    g.setColour(juce::Colour(0xff10141f));
    g.fillRoundedRectangle(area, 4.0f);

    const auto clamped = juce::jlimit(0.0f, 1.0f, value);
    const auto fillHeight = area.getHeight() * clamped;
    auto fillArea = area.withY(area.getBottom() - fillHeight).withHeight(fillHeight);

    juce::ColourGradient meterGradient(baseColor.withBrightness(0.35f), fillArea.getBottomLeft(),
                                       juce::Colours::red.withAlpha(0.9f), fillArea.getTopLeft(), false);
    meterGradient.addColour(0.5, juce::Colours::yellow.withAlpha(0.9f));
    g.setGradientFill(meterGradient);
    g.fillRoundedRectangle(fillArea, 4.0f);

    g.setColour(juce::Colours::white.withAlpha(0.75f));
    g.drawText(label, area.withY(area.getBottom() + 4.0f).withHeight(16.0f).toNearestInt(), juce::Justification::centred);
}

void MixPulseAudioProcessorEditor::drawMeterColumn(juce::Graphics& g, juce::Rectangle<int> area)
{
    const auto& meter = processor.analyzer.getMeterData();
    auto panel = area.toFloat().reduced(10.0f);
    g.setColour(juce::Colour(0xff090d15));
    g.fillRoundedRectangle(panel, 8.0f);

    auto barsArea = panel.reduced(10.0f, 40.0f);
    const auto barW = barsArea.getWidth() / 4.5f;

    drawVerticalBar(g, { barsArea.getX(), barsArea.getY(), barW, barsArea.getHeight() }, meter.peakL.load(), theme.left, "Pk L");
    drawVerticalBar(g, { barsArea.getX() + barW * 1.15f, barsArea.getY(), barW, barsArea.getHeight() }, meter.peakR.load(), theme.right, "Pk R");
    drawVerticalBar(g, { barsArea.getX() + barW * 2.5f, barsArea.getY(), barW, barsArea.getHeight() }, meter.rmsL.load(), theme.left.darker(0.3f), "RMS L");
    drawVerticalBar(g, { barsArea.getX() + barW * 3.65f, barsArea.getY(), barW, barsArea.getHeight() }, meter.rmsR.load(), theme.right.darker(0.3f), "RMS R");

    const auto clip = meter.clipLatched.load();
    g.setColour(clip ? juce::Colours::red : juce::Colours::darkgrey);
    g.fillEllipse(panel.getX() + 12.0f, panel.getY() + 8.0f, 10.0f, 10.0f);
    g.fillEllipse(panel.getX() + 28.0f, panel.getY() + 8.0f, 10.0f, 10.0f);

    g.setColour(juce::Colours::white.withAlpha(0.8f));
    g.setFont(14.0f);
    g.drawText("LUFS M: " + juce::String(meter.lufsM.load(), 1), panel.removeFromBottom(22).toNearestInt(), juce::Justification::left);
    g.drawText("LUFS S: " + juce::String(meter.lufsS.load(), 1), panel.removeFromBottom(22).toNearestInt(), juce::Justification::left);
    g.drawText("LUFS I: " + juce::String(meter.lufsI.load(), 1), panel.removeFromBottom(22).toNearestInt(), juce::Justification::left);
    g.drawText("True Peak: " + juce::String(juce::Decibels::gainToDecibels(std::max(1.0e-6f, meter.truePeak.load())), 1) + " dB", panel.removeFromBottom(22).toNearestInt(), juce::Justification::left);

    auto refBar = panel.removeFromBottom(18.0f);
    g.setColour(juce::Colour(0xff1b2236));
    g.fillRoundedRectangle(refBar, 3.0f);
    auto markerX = [refBar](float lufs) {
        const float minL = -30.0f, maxL = -6.0f;
        return juce::jmap(lufs, minL, maxL, refBar.getX(), refBar.getRight());
    };
    g.setColour(juce::Colours::cyan.withAlpha(0.6f));
    g.drawVerticalLine((int)markerX(-14.0f), refBar.getY(), refBar.getBottom());
    g.setColour(juce::Colours::skyblue.withAlpha(0.6f));
    g.drawVerticalLine((int)markerX(-23.0f), refBar.getY(), refBar.getBottom());
}

void MixPulseAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(theme.background);
    auto bounds = getLocalBounds().reduced(12);
    g.setColour(theme.panel);
    g.fillRoundedRectangle(bounds.toFloat(), 8.0f);

    auto header = bounds.removeFromTop(72);
    g.setColour(theme.accent);
    g.setFont(24.0f);
    g.drawText("MixPulse", header.removeFromTop(36), juce::Justification::left);

    auto bpm = processor.tapTempo.getBpm();
    g.setFont(20.0f);
    g.drawText("BPM: " + (bpm ? juce::String(*bpm, 1) : "--"), header, juce::Justification::left);

    auto leftColumn = bounds.removeFromLeft(360);
    drawMeterColumn(g, leftColumn);

    g.setColour(juce::Colours::white.withAlpha(0.35f));
    g.drawRoundedRectangle(bounds.toFloat().reduced(8.0f), 6.0f, 1.0f);
    g.drawText("Mini visual panels and advanced controls: TODO", bounds.reduced(16), juce::Justification::centred);
}

void MixPulseAudioProcessorEditor::resized()
{
    auto r = getLocalBounds().reduced(20).removeFromTop(40);
    tapButton.setBounds(r.removeFromLeft(110));
    r.removeFromLeft(10);
    beatSyncButton.setBounds(r.removeFromLeft(140));
    r.removeFromLeft(10);
    visualizerButton.setBounds(r.removeFromLeft(170));
}

bool MixPulseAudioProcessorEditor::keyPressed(const juce::KeyPress& k)
{
    if (k.getTextCharacter() == 't' || k.getTextCharacter() == 'T') { tapButton.triggerClick(); return true; }
    if (k.getTextCharacter() == 'b' || k.getTextCharacter() == 'B') { beatSyncButton.setToggleState(!beatSyncButton.getToggleState(), juce::sendNotification); return true; }
    if (k.getTextCharacter() == 'v' || k.getTextCharacter() == 'V') { processor.visualizerState.mode = VisualizerMode::SpectrumBars; return true; }
    if (k.getTextCharacter() == 'r' || k.getTextCharacter() == 'R')
    {
        processor.analyzer.getMeterData().clipLatched = false;
        processor.analyzer.getMeterData().lufsI = -23.0f;
        return true;
    }
    if (k.getTextCharacter() == 's' || k.getTextCharacter() == 'S') { exportScreenshot(); return true; }
    if (k.getTextCharacter() == 'f' || k.getTextCharacter() == 'F') { if (visualizer) visualizer->toggleFullscreen(); return true; }
    if (k == juce::KeyPress::escapeKey) { if (visualizer) visualizer->setFullScreen(false); return true; }
    return false;
}

void MixPulseAudioProcessorEditor::timerCallback() { repaint(); }

void MixPulseAudioProcessorEditor::openVisualizer()
{
    if (!visualizer)
        visualizer = std::make_unique<VisualizerWindow>(processor.analyzer, processor.beatPulse, processor.visualizerState);
    visualizer->setVisible(true);
    visualizer->toFront(true);
}

void MixPulseAudioProcessorEditor::exportScreenshot()
{
    if (!visualizer)
        return;

    auto* c = visualizer->getContentComponent();
    if (!c)
        return;

    juce::Image img(juce::Image::ARGB, c->getWidth(), c->getHeight(), true);
    juce::Graphics g(img);
    c->paintEntireComponent(g, false);

    const auto t = juce::Time::getCurrentTime();
    const auto name = "MixPulse_Visualizer_" + t.formatted("%Y-%m-%d_%H-%M-%S") + ".png";
    const auto f = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile(name);

    juce::PNGImageFormat png;
    juce::FileOutputStream os(f);
    if (os.openedOk())
        png.writeImageToStream(img, os);
}
