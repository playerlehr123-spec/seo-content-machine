#include <atomic>
#include "PluginEditor.h"
#include "VisualizerRenderer.h"

namespace {
float gainToDb(float g) { return juce::jlimit(-60.0f, 0.0f, juce::Decibels::gainToDecibels(std::max(1.0e-6f, g))); }
float dbToY(float db, const juce::Rectangle<float>& r) { return juce::jmap(db, -60.0f, 0.0f, r.getBottom(), r.getY()); }
}

MixPulseAudioProcessorEditor::MixPulseAudioProcessorEditor(MixPulseAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p), theme(ThemeManager::darkNeon())
{
    setWantsKeyboardFocus(true); setSize(1200, 700); setResizeLimits(480, 300, 2000, 1400);
    addAndMakeVisible(tapButton); addAndMakeVisible(visualizerButton); addAndMakeVisible(beatSyncButton); addAndMakeVisible(screenshotButton); addAndMakeVisible(hudButton); addAndMakeVisible(fullscreenButton); addAndMakeVisible(themeBox);
    tapButton.onClick = [this]{ processor.tapTempo.tap(juce::Time::getMillisecondCounterHiRes()/1000.0); processor.beatPulse.trigger(processor.tapTempo.getBpm().value_or(0.0)); };
    beatSyncButton.onClick = [this]{ processor.visualizerState.beatSync.store(beatSyncButton.getToggleState()); };
    visualizerButton.onClick = [this]{ openVisualizer(); };
    screenshotButton.onClick = [this]{ exportScreenshot(); };
    fullscreenButton.onClick = [this]{ if(visualizer) visualizer->toggleFullscreen(); };
    hudButton.onClick = []{}; // TODO: HUD overlay mode.
    themeBox.addItem("Dark Neon", 1); themeBox.addItem("Lo-Fi Warm (TODO)", 2); themeBox.setSelectedId(1);
    startTimerHz(30);
}
MixPulseAudioProcessorEditor::~MixPulseAudioProcessorEditor() = default;

void MixPulseAudioProcessorEditor::drawVerticalBar(juce::Graphics& g, juce::Rectangle<float> r, float v, juce::Colour c, const juce::String& label, float& holdDb)
{
    const auto db = gainToDb(v);
    holdDb = std::max(db, holdDb - 0.6f);

    g.setColour(theme.panelBorder); g.drawRoundedRectangle(r, 4.0f, 1.0f);
    auto y = dbToY(db, r);
    auto fill = juce::Rectangle<float>(r.getX()+1.0f, y, r.getWidth()-2.0f, r.getBottom()-y);
    g.setColour(c.withAlpha(0.22f)); g.fillRoundedRectangle(fill.expanded(2.0f), 3.0f);
    g.setColour(c); g.fillRoundedRectangle(fill, 3.0f);
    g.setColour(juce::Colours::white.withAlpha(0.9f));
    auto holdY = dbToY(holdDb, r); g.fillRect(r.getX()+1.0f, holdY-1.0f, r.getWidth()-2.0f, 2.0f);
    g.setColour(theme.mutedText); g.drawText(label, r.withY(r.getBottom()+4).withHeight(14).toNearestInt(), juce::Justification::centred);
}

void MixPulseAudioProcessorEditor::drawMeterColumn(juce::Graphics& g, juce::Rectangle<int> area)
{
    auto panel = area.toFloat().reduced(8.0f); g.setColour(theme.panel); g.fillRoundedRectangle(panel, 8.0f); g.setColour(theme.panelBorder); g.drawRoundedRectangle(panel, 8.0f, 1.0f);
    auto ticks = panel.reduced(10.0f, 26.0f);
    for (auto db : {0,-3,-6,-9,-12,-24}) { auto y=dbToY((float)db,ticks); g.setColour(theme.grid); g.drawHorizontalLine((int)y,ticks.getX(),ticks.getRight()); g.setColour(theme.mutedText); g.drawText(juce::String(db),(int)ticks.getRight()-30,(int)y-8,28,14,juce::Justification::right); }

    const auto& m = processor.analyzer.getMeterData(); auto bw=ticks.getWidth()/5.2f;
    drawVerticalBar(g,{ticks.getX()+bw*0.2f,ticks.getY(),bw,ticks.getHeight()},m.peakL.load(),theme.left,"Pk L",peakHoldL);
    drawVerticalBar(g,{ticks.getX()+bw*1.3f,ticks.getY(),bw,ticks.getHeight()},m.peakR.load(),theme.right,"Pk R",peakHoldR);
    drawVerticalBar(g,{ticks.getX()+bw*2.7f,ticks.getY(),bw,ticks.getHeight()},m.rmsL.load(),theme.left.withAlpha(0.7f),"RMS L",rmsHoldL);
    drawVerticalBar(g,{ticks.getX()+bw*3.8f,ticks.getY(),bw,ticks.getHeight()},m.rmsR.load(),theme.right.withAlpha(0.7f),"RMS R",rmsHoldR);
    g.setColour(m.clipLatched.load()?theme.warningDot:juce::Colours::darkgrey); g.fillEllipse(panel.getX()+10,panel.getY()+8,7,7); g.fillEllipse(panel.getX()+22,panel.getY()+8,7,7);
}

void MixPulseAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(theme.background); auto b=getLocalBounds().reduced(10);
    auto header=b.removeFromTop(76); g.setColour(theme.panel); g.fillRoundedRectangle(header.toFloat(),8.0f); g.setColour(theme.panelBorder); g.drawRoundedRectangle(header.toFloat(),8.0f,1.0f);
    g.setColour(theme.accent); g.setFont(24.0f); g.drawText("MixPulse", header.removeFromLeft(190), juce::Justification::centredLeft);
    g.setColour(theme.mutedText); g.setFont(12.0f); g.drawText("v0.1 beta", header.removeFromLeft(80), juce::Justification::centredLeft);
    auto bpm=processor.tapTempo.getBpm(); g.setColour(theme.text); g.setFont(18.0f); g.drawText("BPM " + (bpm?juce::String(*bpm,1):"--.-"), header.removeFromLeft(120), juce::Justification::centredLeft);
    g.setColour(theme.mutedText); g.drawText("SR/Buffer host", header.removeFromLeft(150), juce::Justification::centredLeft);

    auto left=b.removeFromLeft(390); drawMeterColumn(g,left);
    auto right=b.reduced(4);
    g.setColour(theme.panel); g.fillRoundedRectangle(right.toFloat(),8); g.setColour(theme.panelBorder); g.drawRoundedRectangle(right.toFloat(),8,1);
    auto loud = right.removeFromTop(160).reduced(12); auto& m=processor.analyzer.getMeterData(); g.setColour(theme.text); g.setFont(14);
    g.drawText("LUFS M  " + juce::String(m.lufsM.load(),1), loud.removeFromTop(24), juce::Justification::left);
    g.drawText("LUFS S  --.-", loud.removeFromTop(24), juce::Justification::left);
    g.drawText("LUFS I  --.-", loud.removeFromTop(24), juce::Justification::left);
    g.drawText("TP      " + juce::String(gainToDb(m.truePeak.load()),1), loud.removeFromTop(24), juce::Justification::left);

    auto ref=right.removeFromTop(26).reduced(12,5).toFloat(); g.setColour(theme.grid); g.fillRoundedRectangle(ref,3);
    auto mx=[ref](float l){return juce::jmap(l,-30.0f,-6.0f,ref.getX(),ref.getRight());}; g.setColour(theme.secondary.withAlpha(0.45f)); g.drawVerticalLine((int)mx(-6),ref.getY(),ref.getBottom()); g.drawVerticalLine((int)mx(-12),ref.getY(),ref.getBottom()); g.drawVerticalLine((int)mx(-14),ref.getY(),ref.getBottom()); g.drawVerticalLine((int)mx(-23),ref.getY(),ref.getBottom()); g.setColour(theme.mutedText); g.drawText("LUFS refs", (int)ref.getX(), (int)ref.getY()-12, 80, 10, juce::Justification::left);

    auto preview=right.removeFromTop(124).reduced(12); g.setColour(theme.grid); g.drawRoundedRectangle(preview.toFloat(),6,1); g.drawText("Spectrum Preview", preview.removeFromTop(22), juce::Justification::left); g.drawText("Waveform placeholder", preview.removeFromTop(18), juce::Justification::left); g.drawText("Vectorscope placeholder", preview.removeFromTop(18), juce::Justification::left);
    auto visCtl=right.reduced(12); g.setColour(theme.grid); g.drawRoundedRectangle(visCtl.toFloat(),6,1); g.drawText("Visualizer mode: " + VisualizerRenderer::modeName(processor.visualizerState.mode.load()), visCtl.removeFromTop(22), juce::Justification::left); g.drawText("Beat Sync: " + juce::String(processor.visualizerState.beatSync.load()?"ON":"OFF"), visCtl.removeFromTop(18), juce::Justification::left); g.drawText("Theme: Dark Neon (dropdown placeholder)", visCtl.removeFromTop(18), juce::Justification::left); g.drawText("FX toggles placeholder", visCtl.removeFromTop(18), juce::Justification::left);
}

void MixPulseAudioProcessorEditor::resized()
{
    auto r=getLocalBounds().reduced(16).removeFromTop(34);
    tapButton.setBounds(r.removeFromLeft(58)); r.removeFromLeft(6); beatSyncButton.setBounds(r.removeFromLeft(96)); r.removeFromLeft(6);
    visualizerButton.setBounds(r.removeFromLeft(84)); r.removeFromLeft(6); fullscreenButton.setBounds(r.removeFromLeft(56)); r.removeFromLeft(6);
    screenshotButton.setBounds(r.removeFromLeft(56)); r.removeFromLeft(6); hudButton.setBounds(r.removeFromLeft(52)); r.removeFromLeft(6); themeBox.setBounds(r.removeFromLeft(170));
}

bool MixPulseAudioProcessorEditor::keyPressed(const juce::KeyPress& k)
{
    if(k.getTextCharacter()=='t'||k.getTextCharacter()=='T'){tapButton.triggerClick();return true;}
    if(k.getTextCharacter()=='b'||k.getTextCharacter()=='B'){beatSyncButton.setToggleState(!beatSyncButton.getToggleState(),juce::sendNotification);return true;}
    if(k.getTextCharacter()=='v'||k.getTextCharacter()=='V'){ auto m=(int)processor.visualizerState.mode.load(); processor.visualizerState.mode.store((VisualizerMode)((m+1)%10)); return true;}
    if(k.getTextCharacter()=='r'||k.getTextCharacter()=='R'){processor.analyzer.getMeterData().clipLatched.store(false,std::memory_order_relaxed); return true;}
    if(k.getTextCharacter()=='s'||k.getTextCharacter()=='S'){exportScreenshot();return true;}
    if(k.getTextCharacter()=='f'||k.getTextCharacter()=='F'){ if(visualizer) visualizer->toggleFullscreen(); return true;}
    if(k==juce::KeyPress::escapeKey){ if(visualizer) visualizer->setFullScreen(false); return true;}
    return false;
}
void MixPulseAudioProcessorEditor::timerCallback(){ repaint(); }
void MixPulseAudioProcessorEditor::openVisualizer(){ if(!visualizer) visualizer=std::make_unique<VisualizerWindow>(processor.analyzer,processor.beatPulse,processor.visualizerState); visualizer->setVisible(true); visualizer->toFront(true);} 
void MixPulseAudioProcessorEditor::exportScreenshot(){ if(!visualizer) return; auto* c=visualizer->getContentComponent(); if(!c) return; juce::Image img(juce::Image::ARGB,c->getWidth(),c->getHeight(),true); juce::Graphics gg(img); c->paintEntireComponent(gg,false); auto dir=juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("MixPulse"); dir.createDirectory(); auto n="MixPulse_Visualizer_"+juce::Time::getCurrentTime().formatted("%Y-%m-%d_%H-%M-%S")+".png"; juce::FileOutputStream os(dir.getChildFile(n)); if(os.openedOk()){ juce::PNGImageFormat png; png.writeImageToStream(img,os);} }
