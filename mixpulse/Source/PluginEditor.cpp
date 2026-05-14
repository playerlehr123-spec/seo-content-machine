#include <atomic>
#include "PluginEditor.h"
#include "VisualizerRenderer.h"
#include "Branding.h"
#include "ExportPreset.h"
#include "CreatorTemplate.h"

namespace {
float gainToDb(float g) { return juce::jlimit(-60.0f, 0.0f, juce::Decibels::gainToDecibels(std::max(1.0e-6f, g))); }
float dbToY(float db, const juce::Rectangle<float>& r) { return juce::jmap(db, -60.0f, 0.0f, r.getBottom(), r.getY()); }
}

MixPulseAudioProcessorEditor::MixPulseAudioProcessorEditor(MixPulseAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p), theme(ThemeManager::darkNeon())
{
    setWantsKeyboardFocus(true); setSize(1200, 700); setResizeLimits(480, 300, 2000, 1400);
    addAndMakeVisible(tapButton); addAndMakeVisible(visualizerButton); addAndMakeVisible(beatSyncButton); addAndMakeVisible(screenshotButton); addAndMakeVisible(hudButton); addAndMakeVisible(fullscreenButton); addAndMakeVisible(infoButton); addAndMakeVisible(copyInfoButton); addAndMakeVisible(savePresetButton); addAndMakeVisible(loadPresetButton); addAndMakeVisible(resetDefaultButton); addAndMakeVisible(themeBox); addAndMakeVisible(exportPresetBox); addAndMakeVisible(templateBox);
    tapButton.onClick = [this]{ processor.tapTempo.tap(juce::Time::getMillisecondCounterHiRes()/1000.0); processor.beatPulse.trigger(processor.tapTempo.getBpm().value_or(0.0)); };
    beatSyncButton.onClick = [this]{ processor.visualizerState.beatSync.store(beatSyncButton.getToggleState()); };
    visualizerButton.onClick = [this]{ openVisualizer(); };
    screenshotButton.onClick = [this]{ exportScreenshot(); };
    fullscreenButton.onClick = [this]{ if(visualizer) visualizer->toggleFullscreen(); };
    hudButton.onClick = [this]{ hudMode = !hudMode; processor.hudEnabled = hudMode; setStatusMessage(hudMode ? "HUD mode ON" : "HUD mode OFF"); repaint(); };
    infoButton.onClick = [this]{ setStatusMessage("Info: " + juce::String(Branding::ProductDisplayName) + " " + Branding::ProductVersion + " (" + Branding::ProductCodename + ")"); };
    copyInfoButton.onClick = [this]{
        juce::String buildMode = juce::JUCEApplicationBase::isStandaloneApp() ? "Standalone" : "VST3 / Host";
        juce::String info = juce::String(Branding::ProductDisplayName) + " " + Branding::ProductVersion + "\n"
            + "Internal codename: " + Branding::ProductCodename + "\n"
            + "Build: " + buildMode + "\n"
            + "HUD: " + juce::String(hudMode ? "on" : "off") + "\n"
            + "Output window: " + juce::String((visualizer && visualizer->isVisible()) ? "open" : "closed") + "\n"
            + "Last frame status: " + (statusMessage.isNotEmpty() ? statusMessage : "--") + "\n"
            + "Notes: LUFS/True Peak placeholders in beta";
        juce::SystemClipboard::copyTextToClipboard(info);
        setStatusMessage("Info copied");
    };
        themeBox.addItem("Dark Neon", 1); themeBox.addItem("Lo-Fi Warm (TODO)", 2); themeBox.setSelectedId(1);

    for (int i = 0; i < (int)getBuiltInExportPresets().size(); ++i)
        exportPresetBox.addItem(exportPresetShortLabel(i), i + 1);
    exportPresetBox.setSelectedId(1);
    exportPresetBox.onChange = [this] { applySelectedExportPresetToOutputGuide(); };

    savePresetButton.onClick = [this]{ saveUserPreset(); };
    loadPresetButton.onClick = [this]{ loadUserPreset(); };
    resetDefaultButton.onClick = [this]{ resetDefaults(); };

    for (int i = 0; i < (int)getBuiltInCreatorTemplates().size(); ++i)
        templateBox.addItem(getBuiltInCreatorTemplates()[(size_t)i].name, i + 1);
    templateBox.setSelectedId(1);
    templateBox.onChange = [this]
    {
        const int idx = templateBox.getSelectedId() - 1;
        if (idx >= 0 && idx < (int)getBuiltInCreatorTemplates().size())
        {
            const auto& tp = getBuiltInCreatorTemplates()[(size_t)idx];
            exportPresetBox.setSelectedId(tp.preferredExportPresetIndex + 1, juce::sendNotificationSync);
            setStatusMessage("Template: " + tp.name + " • " + tp.moduleName);
        }
    };
    syncUiToProcessorState();
    startTimerHz(30);
}
MixPulseAudioProcessorEditor::~MixPulseAudioProcessorEditor()
{
    if (visualizer) {
        visualizer->setVisible(false);
        visualizer.reset();
    }
}

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


void MixPulseAudioProcessorEditor::setStatusMessage(const juce::String& msg)
{
    statusMessage = msg;
    statusUntilSeconds = juce::Time::getMillisecondCounterHiRes() / 1000.0 + 3.0;
}

void MixPulseAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(theme.background); auto b=getLocalBounds().reduced(10);
    auto header=b.removeFromTop(76); g.setColour(theme.panel); g.fillRoundedRectangle(header.toFloat(),8.0f); g.setColour(theme.panelBorder); g.drawRoundedRectangle(header.toFloat(),8.0f,1.0f);
    g.setColour(theme.accent); g.setFont(24.0f); g.drawText(Branding::ProductDisplayName, header.removeFromLeft(190), juce::Justification::centredLeft);
    g.setColour(theme.mutedText); g.setFont(12.0f); g.drawText(Branding::ProductVersion, header.removeFromLeft(80), juce::Justification::centredLeft);
    auto bpm=processor.tapTempo.getBpm(); g.setColour(theme.text); g.setFont(18.0f); g.drawText("BPM " + (bpm?juce::String(*bpm,1):"--.-"), header.removeFromLeft(120), juce::Justification::centredLeft);
    g.setColour(theme.mutedText); g.drawText("SR/Buffer host", header.removeFromLeft(150), juce::Justification::centredLeft);

    if (hudMode)
    {
        auto hud=b.reduced(6);
        drawMeterColumn(g, hud.removeFromLeft(300));
        auto& m=processor.analyzer.getMeterData();
        g.setColour(theme.text); g.setFont(18.0f);
        g.drawText("HUD  BPM " + (processor.tapTempo.getBpm()?juce::String(*processor.tapTempo.getBpm(),1):"--.-"), hud.removeFromTop(28), juce::Justification::left);
        g.drawText("LUFS M " + juce::String(m.lufsM.load(),1) + "  TP " + juce::String(gainToDb(m.truePeak.load()),1), hud.removeFromTop(24), juce::Justification::left);
    }
    else
    {
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

    auto preview=right.removeFromTop(124).reduced(12); g.setColour(theme.grid); g.drawRoundedRectangle(preview.toFloat(),6,1); g.drawText("Creator Output Window Preview", preview.removeFromTop(22), juce::Justification::left); g.drawText("Spectrum Preview", preview.removeFromTop(18), juce::Justification::left); g.drawText("Other modules are placeholders", preview.removeFromTop(18), juce::Justification::left);
    auto visCtl=right.reduced(12); g.setColour(theme.grid); g.drawRoundedRectangle(visCtl.toFloat(),6,1); g.drawText("Visual Rack", visCtl.removeFromTop(22), juce::Justification::left); g.drawText("Preset: Dark Neon Meter (placeholder)", visCtl.removeFromTop(18), juce::Justification::left); g.drawText("Module: " + visualModuleName((VisualModuleType) processor.visualRackState.selectedModule.load()), visCtl.removeFromTop(18), juce::Justification::left); g.drawText("FX: Bloom " + juce::String(processor.visualRackState.fxBloom.load()?"ON":"OFF") + " / Mirror " + juce::String(processor.visualRackState.fxMirror.load()?"ON":"OFF") + " / Colorize " + juce::String(processor.visualRackState.fxColorize.load()?"ON":"OFF"), visCtl.removeFromTop(18), juce::Justification::left); g.drawText("FX: Scanlines " + juce::String(processor.visualRackState.fxScanlines.load()?"ON":"OFF") + " / Chromatic " + juce::String(processor.visualRackState.fxChromaticSplit.load()?"ON":"OFF"), visCtl.removeFromTop(18), juce::Justification::left); g.drawText("Aspect: " + juce::String(processor.visualRackState.outputPreset.load()) + " / Export: " + exportPresetShortLabel(exportPresetBox.getSelectedId()-1), visCtl.removeFromTop(18), juce::Justification::left); g.drawText("Template: " + templateBox.getText() + " • PNG only beta", visCtl.removeFromTop(18), juce::Justification::left);
    g.drawText("QA: " + juce::String(Branding::BetaStatus) + " / " + (juce::JUCEApplicationBase::isStandaloneApp() ? "Standalone" : "VST3 / Host"), visCtl.removeFromTop(18), juce::Justification::left);
    }

    if ((juce::Time::getMillisecondCounterHiRes() / 1000.0) < statusUntilSeconds) {
        g.setColour(theme.accent); g.setFont(13.0f);
        g.drawText(statusMessage, getLocalBounds().removeFromBottom(22).reduced(10,0), juce::Justification::centredLeft);
    }
}

void MixPulseAudioProcessorEditor::resized()
{
    auto r=getLocalBounds().reduced(16).removeFromTop(34);
    tapButton.setBounds(r.removeFromLeft(58)); r.removeFromLeft(6); beatSyncButton.setBounds(r.removeFromLeft(96)); r.removeFromLeft(6);
    visualizerButton.setBounds(r.removeFromLeft(84)); r.removeFromLeft(6); fullscreenButton.setBounds(r.removeFromLeft(56)); r.removeFromLeft(6);
    screenshotButton.setBounds(r.removeFromLeft(84)); r.removeFromLeft(6); exportPresetBox.setBounds(r.removeFromLeft(96)); r.removeFromLeft(6); templateBox.setBounds(r.removeFromLeft(176)); r.removeFromLeft(6); savePresetButton.setBounds(r.removeFromLeft(94)); r.removeFromLeft(6); loadPresetButton.setBounds(r.removeFromLeft(94)); r.removeFromLeft(6); resetDefaultButton.setBounds(r.removeFromLeft(104)); r.removeFromLeft(6); hudButton.setBounds(r.removeFromLeft(52)); r.removeFromLeft(6); infoButton.setBounds(r.removeFromLeft(54)); r.removeFromLeft(6); copyInfoButton.setBounds(r.removeFromLeft(88)); r.removeFromLeft(6); themeBox.setBounds(r.removeFromLeft(120));
}

bool MixPulseAudioProcessorEditor::keyPressed(const juce::KeyPress& k)
{
    if(k.getTextCharacter()=='t'||k.getTextCharacter()=='T'){tapButton.triggerClick();return true;}
    if(k.getTextCharacter()=='b'||k.getTextCharacter()=='B'){beatSyncButton.setToggleState(!beatSyncButton.getToggleState(),juce::sendNotification);return true;}
    if(k.getTextCharacter()=='v'||k.getTextCharacter()=='V'){ auto m=(int)processor.visualizerState.mode.load(); processor.visualizerState.mode.store((VisualizerMode)((m+1)%10)); return true;}
    if(k.getTextCharacter()=='r'||k.getTextCharacter()=='R'){processor.analyzer.getMeterData().clipLatched.store(false,std::memory_order_relaxed); return true;}
    if(k.getTextCharacter()=='s'||k.getTextCharacter()=='S'){exportScreenshot();return true;}
    if(k.getTextCharacter()=='f'||k.getTextCharacter()=='F'){ if(!visualizer) openVisualizer(); if(visualizer) visualizer->toggleFullscreen(); return true;}
    if(k.getTextCharacter()=='h'||k.getTextCharacter()=='H'){ hudButton.triggerClick(); return true;}
    if(k==juce::KeyPress::escapeKey){ if(visualizer) visualizer->setFullScreen(false); return true;}
    return false;
}
void MixPulseAudioProcessorEditor::timerCallback(){ repaint(); }
void MixPulseAudioProcessorEditor::openVisualizer(){ if(!visualizer) visualizer=std::make_unique<VisualizerWindow>(processor.analyzer,processor.beatPulse,processor.visualizerState,processor.visualRackState); visualizer->setVisible(true); visualizer->toFront(true);} 
void MixPulseAudioProcessorEditor::applySelectedExportPresetToOutputGuide()
{
    const int idx = juce::jmax(0, exportPresetBox.getSelectedId() - 1);
    processor.selectedExportPreset = idx;
    switch (idx)
    {
        case 1: processor.visualRackState.outputPreset.store((int) OutputPreset::Portrait9x16); break;
        case 2: processor.visualRackState.outputPreset.store((int) OutputPreset::Square1x1); break;
        case 3: processor.visualRackState.outputPreset.store((int) OutputPreset::Portrait4x5); break;
        case 4: case 5: processor.visualRackState.outputPreset.store((int) OutputPreset::Landscape16x9); break;
        default: processor.visualRackState.outputPreset.store((int) OutputPreset::Free); break;
    }
}

void MixPulseAudioProcessorEditor::exportScreenshot()
{
    if (!visualizer) openVisualizer();

    const auto& presets = getBuiltInExportPresets();
    const int presetIndex = juce::jlimit(0, (int)presets.size() - 1, exportPresetBox.getSelectedId() - 1);
    const auto& preset = presets[(size_t)presetIndex];
    if (!preset.enabled)
    {
        setStatusMessage("Fixed-size export coming soon: " + preset.name);
        return;
    }

    auto exportDir = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile(Branding::ProductDisplayName).getChildFile("Exports");
    exportDir.createDirectory();

    auto* sourceComponent = visualizer ? visualizer->getContentComponent() : nullptr;
    if (!sourceComponent || sourceComponent->getWidth() <= 0 || sourceComponent->getHeight() <= 0)
        sourceComponent = this;

    int w = sourceComponent->getWidth(), h = sourceComponent->getHeight();
    if (preset.width > 0 && preset.height > 0) { w = preset.width; h = preset.height; }
    if (w <= 0 || h <= 0) { setStatusMessage("Export failed: invalid render size"); return; }

    juce::Image img(juce::Image::ARGB, w, h, true);
    juce::Graphics gg(img);
    if (preset.width > 0 && preset.height > 0 && sourceComponent != this)
    {
        float sx = (float)w / (float)sourceComponent->getWidth();
        float sy = (float)h / (float)sourceComponent->getHeight();
        gg.addTransform(juce::AffineTransform::scale(sx, sy));
    }
    sourceComponent->paintEntireComponent(gg, false);

    auto stamp = juce::Time::getCurrentTime().formatted("%Y-%m-%d_%H-%M-%S");
    auto safeName = exportPresetShortLabel(presetIndex).removeCharacters(" /:");
    auto file = exportDir.getChildFile("WaveFrame_" + safeName + "_" + stamp + ".png");
    juce::FileOutputStream os(file);
    juce::PNGImageFormat png;
    if (!os.openedOk()) { setStatusMessage("Export failed: cannot create output file"); return; }
    if (!png.writeImageToStream(img, os)) { setStatusMessage("Export failed: PNG encoder error"); return; }

    setStatusMessage("Saved " + exportPresetShortLabel(presetIndex) + " PNG to Documents/WaveFrame/Exports");
}


void MixPulseAudioProcessorEditor::syncUiToProcessorState()
{
    beatSyncButton.setToggleState(processor.visualizerState.beatSync.load(), juce::dontSendNotification);
    hudMode = processor.hudEnabled;
    exportPresetBox.setSelectedId(processor.selectedExportPreset + 1, juce::dontSendNotification);
    themeBox.setSelectedId(processor.selectedTheme, juce::dontSendNotification);
    applySelectedExportPresetToOutputGuide();
}

void MixPulseAudioProcessorEditor::saveUserPreset()
{
    processor.selectedExportPreset = juce::jmax(0, exportPresetBox.getSelectedId() - 1);
    processor.selectedTheme = themeBox.getSelectedId();
    processor.hudEnabled = hudMode;
    if (BrandLayer::savePreset(processor.brandState, BrandLayer::defaultPresetFile()))
        setStatusMessage("Preset saved: Documents/WaveFrame/Presets");
    else
        setStatusMessage("Preset save failed");
}

void MixPulseAudioProcessorEditor::loadUserPreset()
{
    if (!BrandLayer::loadPreset(processor.brandState, BrandLayer::defaultPresetFile()))
    {
        setStatusMessage("Preset load failed");
        return;
    }
    if (processor.brandState.logoPath.isNotEmpty())
    {
        auto logo = juce::File(processor.brandState.logoPath);
        if (logo.existsAsFile()) setStatusMessage("Preset loaded • Logo reloaded");
        else setStatusMessage("Preset loaded • Logo file missing");
    }
    else setStatusMessage("Preset loaded");
}

void MixPulseAudioProcessorEditor::resetDefaults()
{
    processor.visualizerState.mode.store(VisualizerMode::SpectrumBars);
    processor.visualRackState.selectedModule.store((int)VisualModuleType::SpectrumBars);
    processor.visualRackState.outputPreset.store((int)OutputPreset::Landscape16x9);
    processor.visualRackState.fxBloom.store(true);
    processor.visualRackState.fxMirror.store(true);
    processor.visualRackState.fxColorize.store(true);
    processor.visualRackState.fxScanlines.store(false);
    processor.visualRackState.fxChromaticSplit.store(false);
    processor.visualRackState.visualIntensity.store(0.75f);
    processor.visualRackState.motionAmount.store(0.65f);
    processor.visualRackState.primaryModSource.store((int)ModSource::FullAmplitude);
    processor.visualizerState.beatSync.store(true);
    processor.brandState = BrandLayer::CreatorBrandState{};
    processor.selectedExportPreset = 0;
    processor.selectedTheme = 1;
    processor.hudEnabled = false;
    syncUiToProcessorState();
    setStatusMessage("Defaults restored");
}
