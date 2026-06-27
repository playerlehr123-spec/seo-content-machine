#include <atomic>
#include "PluginEditor.h"
#include "VisualizerRenderer.h"
#include "Branding.h"
#include "ExportPreset.h"
#include "CreatorTemplate.h"

namespace {
float gainToDb(float g) { return juce::jlimit(-60.0f, 0.0f, juce::Decibels::gainToDecibels(std::max(1.0e-6f, g))); }
float dbToY(float db, const juce::Rectangle<float>& r) { return juce::jmap(db, -60.0f, 0.0f, r.getBottom(), r.getY()); }

bool comboHasItemId(const juce::ComboBox& box, int id)
{
    for (int i = 0; i < box.getNumItems(); ++i)
        if (box.getItemId(i) == id)
            return true;

    return false;
}

int safeExportPresetIndex(int selectedId, int fallbackIndex)
{
    const auto& presets = getBuiltInExportPresets();
    if (presets.empty())
        return 0;

    const int requested = selectedId > 0 ? selectedId - 1 : fallbackIndex;
    return juce::jlimit(0, (int)presets.size() - 1, requested);
}

const CreatorTemplatePreset* getTemplateForSelectedId(int selectedId)
{
    const auto& templates = getBuiltInCreatorTemplates();
    if (templates.empty())
        return nullptr;

    return &templates[(size_t)sanitizeCreatorTemplateIndex(selectedId - 1)];
}

juce::String templateBrandFieldHint(const CreatorTemplatePreset* preset)
{
    if (preset == nullptr)
        return "artist/title/CTA";

    if (preset->name == "Release Announcement")
        return "artist/title/label/CTA";
    if (preset->name == "Label Drop")
        return "label/title/CTA";
    if (preset->name == "Logo Reactor")
        return "artist/title/logo";
    if (preset->name == "Type Pulse")
        return "title/CTA";
    if (preset->name == "Minimal Meter")
        return "brand optional";
    if (preset->name == "Stream Overlay")
        return "artist/title optional";
    if (preset->name == "Particle Card")
        return "title/CTA optional";
    if (preset->name == "Spectrum Promo")
        return "title/label/CTA";

    return "artist/title/CTA";
}

juce::String fallbackText(const juce::String& value, const juce::String& fallback)
{
    return value.trim().isNotEmpty() ? value : fallback;
}

const ExportPreset* getExportPresetForSelection(int selectedId, int fallbackIndex, int& safeIndex)
{
    const auto& presets = getBuiltInExportPresets();
    if (presets.empty())
    {
        safeIndex = 0;
        return nullptr;
    }

    safeIndex = safeExportPresetIndex(selectedId, fallbackIndex);
    return &presets[(size_t)safeIndex];
}

juce::String exportPresetStatusText(int selectedId, int fallbackIndex)
{
    int safeIndex = 0;
    if (const auto* preset = getExportPresetForSelection(selectedId, fallbackIndex, safeIndex))
        return preset->aspectLabel + " / " + exportPresetDimensionLabel(*preset) + " / " + exportPresetWorkflowLabel(*preset);

    return "Export preset unavailable";
}

juce::String sanitizeBrandTextInput(const juce::String& value, const juce::String& fallback, int maxChars = 64)
{
    auto trimmed = value.trim();
    if (trimmed.isEmpty())
        return fallback;

    return trimmed.substring(0, maxChars);
}

void configureBrandTextEditor(juce::TextEditor& editor, const juce::String& placeholder)
{
    editor.setMultiLine(false);
    editor.setReturnKeyStartsNewLine(false);
    editor.setSelectAllWhenFocused(true);
    editor.setInputRestrictions(64);
    editor.setTextToShowWhenEmpty(placeholder, juce::Colours::white.withAlpha(0.35f));
    editor.setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromRGB(8, 13, 24));
    editor.setColour(juce::TextEditor::outlineColourId, juce::Colour::fromRGB(32, 218, 255).withAlpha(0.30f));
    editor.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colour::fromRGB(80, 255, 160).withAlpha(0.70f));
    editor.setColour(juce::TextEditor::textColourId, juce::Colours::white.withAlpha(0.90f));
    editor.setColour(juce::TextEditor::highlightColourId, juce::Colour::fromRGB(32, 218, 255).withAlpha(0.40f));
}

struct BuiltInSessionPreset
{
    const char* name;
    int templateIndex;
    const char* artist;
    const char* title;
    const char* label;
    const char* cta;
    float visualIntensity;
    float motionAmount;
    float bloomAmount;
    juce::Colour primary;
    juce::Colour secondary;
    juce::Colour accent;
    const char* status;
};

const std::vector<BuiltInSessionPreset>& getBuiltInSessionPresets()
{
    static const std::vector<BuiltInSessionPreset> presets {
        { "Minimal Meter - Dark Cyan", 0, "Artist Name", "Track Title", "WaveFrame", "Meter", 0.75f, 0.65f, 0.45f, juce::Colour::fromRGB(32, 218, 255), juce::Colour::fromRGB(20, 30, 50), juce::Colour::fromRGB(255, 220, 120), "implemented" },
        { "Logo Reactor - Neon Green", 1, "Artist Name", "Track Title", "Label Name", "Listen", 0.78f, 0.58f, 0.52f, juce::Colour::fromRGB(80, 255, 160), juce::Colour::fromRGB(8, 18, 16), juce::Colour::fromRGB(32, 218, 255), "implemented" },
        { "Release Announcement - Vertical", 2, "Artist Name", "Track Title", "Label Name", "Out Now", 0.72f, 0.42f, 0.30f, juce::Colour::fromRGB(32, 218, 255), juce::Colour::fromRGB(14, 14, 24), juce::Colour::fromRGB(255, 220, 120), "implemented" },
        { "Label Drop - Square", 3, "Artist Name", "Track Title", "Label Name", "Out Now", 0.68f, 0.38f, 0.28f, juce::Colour::fromRGB(255, 220, 120), juce::Colour::fromRGB(18, 16, 24), juce::Colour::fromRGB(32, 218, 255), "implemented" },
        { "Stream Overlay - Wide", 4, "Artist Name", "Live Set", "Label Name", "Live", 0.70f, 0.70f, 0.35f, juce::Colour::fromRGB(32, 218, 255), juce::Colour::fromRGB(8, 13, 24), juce::Colour::fromRGB(80, 255, 160), "placeholder" },
        { "Type Pulse - Dark Glow", 7, "Artist Name", "Track Title", "Label Name", "Listen / Watch", 0.82f, 0.66f, 0.42f, juce::Colour::fromRGB(190, 255, 245), juce::Colour::fromRGB(7, 10, 18), juce::Colour::fromRGB(32, 218, 255), "implemented" },
        { "Particle Card - Accent Motion", 8, "Artist Name", "Track Title", "Label Name", "Watch", 0.76f, 0.82f, 0.48f, juce::Colour::fromRGB(160, 255, 120), juce::Colour::fromRGB(8, 12, 20), juce::Colour::fromRGB(32, 218, 255), "placeholder" },
        { "Spectrum Promo - Clean Grid", 9, "Artist Name", "Track Title", "Label Name", "Listen", 0.70f, 0.48f, 0.25f, juce::Colour::fromRGB(32, 218, 255), juce::Colour::fromRGB(10, 14, 22), juce::Colour::fromRGB(255, 220, 120), "implemented" }
    };
    return presets;
}
}

MixPulseAudioProcessorEditor::MixPulseAudioProcessorEditor(MixPulseAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p), theme(ThemeManager::darkNeon())
{
    setWantsKeyboardFocus(true); setSize(1240, 760); setResizeLimits(760, 520, 2000, 1400);
    addAndMakeVisible(tapButton); addAndMakeVisible(visualizerButton); addAndMakeVisible(beatSyncButton); addAndMakeVisible(screenshotButton); addAndMakeVisible(hudButton); addAndMakeVisible(fullscreenButton); addAndMakeVisible(infoButton); addAndMakeVisible(copyInfoButton); addAndMakeVisible(savePresetButton); addAndMakeVisible(loadPresetButton); addAndMakeVisible(resetDefaultButton); addAndMakeVisible(themeBox); addAndMakeVisible(exportPresetBox); addAndMakeVisible(templateBox); addAndMakeVisible(moduleBox); addAndMakeVisible(sessionPresetBox);
    addAndMakeVisible(artistNameEditor); addAndMakeVisible(trackTitleEditor); addAndMakeVisible(labelNameEditor); addAndMakeVisible(ctaTextEditor);
    configureBrandTextEditor(artistNameEditor, "Artist Name");
    configureBrandTextEditor(trackTitleEditor, "Track Title");
    configureBrandTextEditor(labelNameEditor, "Label Name");
    configureBrandTextEditor(ctaTextEditor, "Out Now");
    artistNameEditor.setTooltip("Shown in templates that use artist branding.");
    trackTitleEditor.setTooltip("Used by title, promo, and type modules.");
    labelNameEditor.setTooltip("Optional label/brand line.");
    ctaTextEditor.setTooltip("Short callout like Out Now or Presave.");
    artistNameEditor.onTextChange = [this] { applyBrandEditorsToState(); };
    trackTitleEditor.onTextChange = [this] { applyBrandEditorsToState(); };
    labelNameEditor.onTextChange = [this] { applyBrandEditorsToState(); };
    ctaTextEditor.onTextChange = [this] { applyBrandEditorsToState(); };
    tapButton.onClick = [this]{ processor.tapTempo.tap(juce::Time::getMillisecondCounterHiRes()/1000.0); processor.beatPulse.trigger(processor.tapTempo.getBpm().value_or(0.0)); };
    beatSyncButton.onClick = [this]{ processor.visualizerState.beatSync.store(beatSyncButton.getToggleState()); };
    visualizerButton.onClick = [this]{ openVisualizer(); };
    screenshotButton.onClick = [this]{ exportScreenshot(); };
    fullscreenButton.onClick = [this]{ if (!visualizer) openVisualizer(); if(visualizer) { visualizer->toggleFullscreen(); setStatusMessage("Output fullscreen toggled safely"); } };
    hudButton.onClick = [this]{ hudMode = !hudMode; processor.hudEnabled = hudMode; setStatusMessage(hudMode ? "HUD mode ON" : "HUD mode OFF"); resized(); repaint(); };
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

    const auto& sessionPresets = getBuiltInSessionPresets();
    for (int i = 0; i < (int)sessionPresets.size(); ++i)
        sessionPresetBox.addItem(sessionPresets[(size_t)i].name, i + 1);
    sessionPresetBox.setSelectedId(1);
    sessionPresetBox.onChange = [this] { applyBuiltInSessionPreset(sessionPresetBox.getSelectedId() - 1); };

    moduleBox.addItem("Spectrum Bars", (int)VisualModuleType::SpectrumBars + 1);
    moduleBox.addItem("Logo Reactor", (int)VisualModuleType::LogoPulse + 1);
    moduleBox.addItem("Type Pulse", (int)VisualModuleType::TypePulse + 1);
    moduleBox.addItem("Promo Card", (int)VisualModuleType::PromoCard + 1);
    moduleBox.addItem("Particles", (int)VisualModuleType::Particles + 1);
    moduleBox.addItem("Text Card", (int)VisualModuleType::TextCard + 1);
    moduleBox.setSelectedId((int)processor.visualRackState.selectedModule.load() + 1);
    moduleBox.onChange = [this]
    {
        const int selectedId = moduleBox.getSelectedId();
        auto module = sanitizeVisualModuleIndex(selectedId > 0 ? selectedId - 1 : (int)VisualModuleType::SpectrumBars);
        if (!comboHasItemId(moduleBox, module + 1))
        {
            module = (int)VisualModuleType::SpectrumBars;
            moduleBox.setSelectedId((int)VisualModuleType::SpectrumBars + 1, juce::dontSendNotification);
        }
        processor.visualRackState.selectedModule.store(module);
        setStatusMessage("Module: " + visualModuleName((VisualModuleType)module));
    };

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
        const auto& templates = getBuiltInCreatorTemplates();
        if (templates.empty())
        {
            setStatusMessage("Template unavailable - using defaults");
            return;
        }

        int idx = templateBox.getSelectedId() - 1;
        if (idx < 0 || idx >= (int)templates.size())
        {
            idx = 0;
            templateBox.setSelectedId(1, juce::dontSendNotification);
            setStatusMessage("Template fallback: " + templates.front().name);
        }
        idx = sanitizeCreatorTemplateIndex(idx);

        const auto& tp = templates[(size_t)idx];
        processor.visualRackState.selectedModule.store(sanitizeVisualModuleIndex((int)tp.module));
        processor.brandState.callToAction = tp.ctaText.isNotEmpty() ? tp.ctaText : juce::String("Out Now");
        processor.brandState.releaseStatusText = tp.releaseStatusText.isNotEmpty() ? tp.releaseStatusText : juce::String("Out Now");
        syncModuleBoxToProcessor();
        const int presetIndex = safeExportPresetIndex(tp.preferredExportPresetIndex + 1, 0);
        exportPresetBox.setSelectedId(presetIndex + 1, juce::sendNotificationSync);
        syncBrandEditorsToState();
        setStatusMessage("Template: " + tp.name + " -> " + tp.moduleName + " / " + creatorTemplateStatusLabel(tp));
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

void MixPulseAudioProcessorEditor::drawPanel(juce::Graphics& g, juce::Rectangle<int> area, const juce::String& title)
{
    auto panel = area.toFloat();
    g.setColour(theme.panel);
    g.fillRoundedRectangle(panel, 8.0f);
    g.setColour(theme.panelBorder);
    g.drawRoundedRectangle(panel, 8.0f, 1.0f);
    if (title.isNotEmpty())
        drawSectionTitle(g, area.reduced(14, 10).removeFromTop(22), title);
}

void MixPulseAudioProcessorEditor::drawSectionTitle(juce::Graphics& g, juce::Rectangle<int> area, const juce::String& text)
{
    g.setColour(theme.text);
    g.setFont(juce::Font(14.0f, juce::Font::bold));
    g.drawText(text, area, juce::Justification::centredLeft);
}

void MixPulseAudioProcessorEditor::drawLabelValue(juce::Graphics& g, juce::Rectangle<int> area, const juce::String& label, const juce::String& value)
{
    auto left = area.removeFromLeft(92);
    g.setColour(theme.mutedText);
    g.setFont(11.0f);
    g.drawText(label, left, juce::Justification::centredLeft);
    g.setColour(theme.text);
    g.setFont(12.0f);
    g.drawText(value, area, juce::Justification::centredLeft);
}

void MixPulseAudioProcessorEditor::drawPill(juce::Graphics& g, juce::Rectangle<int> area, const juce::String& text, juce::Colour colour)
{
    auto pill = area.toFloat();
    g.setColour(colour.withAlpha(0.13f));
    g.fillRoundedRectangle(pill, 12.0f);
    g.setColour(colour.withAlpha(0.55f));
    g.drawRoundedRectangle(pill, 12.0f, 1.0f);
    g.setColour(theme.text);
    g.setFont(11.0f);
    g.drawText(text, area.reduced(8, 0), juce::Justification::centred);
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
    drawPanel(g, area, "Meter Rail");
    auto panel = area.toFloat().reduced(12.0f, 42.0f);
    auto ticks = panel.withTrimmedBottom(78.0f);
    for (auto db : {0,-3,-6,-9,-12,-24}) { auto y=dbToY((float)db,ticks); g.setColour(theme.grid); g.drawHorizontalLine((int)y,ticks.getX(),ticks.getRight()); g.setColour(theme.mutedText); g.drawText(juce::String(db),(int)ticks.getRight()-30,(int)y-8,28,14,juce::Justification::right); }

    const auto& m = processor.analyzer.getMeterData(); auto bw=ticks.getWidth()/5.2f;
    drawVerticalBar(g,{ticks.getX()+bw*0.2f,ticks.getY(),bw,ticks.getHeight()},m.peakL.load(),theme.left,"Peak L",peakHoldL);
    drawVerticalBar(g,{ticks.getX()+bw*1.3f,ticks.getY(),bw,ticks.getHeight()},m.peakR.load(),theme.right,"Peak R",peakHoldR);
    drawVerticalBar(g,{ticks.getX()+bw*2.7f,ticks.getY(),bw,ticks.getHeight()},m.rmsL.load(),theme.left.withAlpha(0.7f),"RMS L",rmsHoldL);
    drawVerticalBar(g,{ticks.getX()+bw*3.8f,ticks.getY(),bw,ticks.getHeight()},m.rmsR.load(),theme.right.withAlpha(0.7f),"RMS R",rmsHoldR);
    auto stats = area.reduced(14).removeFromBottom(70);
    g.setColour(m.clipLatched.load()?theme.warningDot:juce::Colours::darkgrey); g.fillEllipse((float)stats.getX(), (float)stats.getY()+4.0f, 8.0f, 8.0f);
    g.setColour(theme.mutedText); g.setFont(11.0f); g.drawText("CLIP", stats.withTrimmedLeft(14).removeFromTop(18), juce::Justification::left);
    drawLabelValue(g, stats.removeFromTop(20), "LUFS M", juce::String(m.lufsM.load(), 1));
    drawLabelValue(g, stats.removeFromTop(20), "True Peak", juce::String(gainToDb(m.truePeak.load()), 1) + " dB");
    g.setColour(theme.mutedText); g.setFont(10.0f);
    g.drawText("Refs -6  -12  -14  -23", stats, juce::Justification::left);
}


void MixPulseAudioProcessorEditor::setStatusMessage(const juce::String& msg)
{
    statusMessage = msg;
    statusUntilSeconds = juce::Time::getMillisecondCounterHiRes() / 1000.0 + 3.0;
}

void MixPulseAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(theme.background);
    auto b = getLocalBounds().reduced(14);
    drawHeader(g, b.removeFromTop(74));
    b.removeFromTop(12);

    if (hudMode)
    {
        drawHudPanel(g, b);
    }
    else
    {
        auto meter = b.removeFromLeft(218);
        b.removeFromLeft(12);
        auto controls = b.removeFromRight(326);
        b.removeFromRight(12);
        drawMeterColumn(g, meter);
        drawPreviewCanvas(g, b);
        drawRightControlPanel(g, controls);
    }

    if ((juce::Time::getMillisecondCounterHiRes() / 1000.0) < statusUntilSeconds) {
        g.setColour(theme.accent); g.setFont(13.0f);
        g.drawText(statusMessage, getLocalBounds().removeFromBottom(22).reduced(10,0), juce::Justification::centredLeft);
    }
}

void MixPulseAudioProcessorEditor::resized()
{
    auto b = getLocalBounds().reduced(14);
    auto header = b.removeFromTop(74).reduced(18, 18);
    auto actions = header.removeFromRight(356);
    visualizerButton.setBounds(actions.removeFromLeft(76)); actions.removeFromLeft(8);
    screenshotButton.setBounds(actions.removeFromLeft(70)); actions.removeFromLeft(8);
    hudButton.setBounds(actions.removeFromLeft(56)); actions.removeFromLeft(8);
    infoButton.setBounds(actions.removeFromLeft(54)); actions.removeFromLeft(8);
    copyInfoButton.setBounds(actions.removeFromLeft(76));

    b.removeFromTop(12);
    if (hudMode)
    {
        moduleBox.setBounds(0, 0, 0, 0);
        templateBox.setBounds(0, 0, 0, 0);
        exportPresetBox.setBounds(0, 0, 0, 0);
        themeBox.setBounds(0, 0, 0, 0);
        sessionPresetBox.setBounds(0, 0, 0, 0);
        tapButton.setBounds(0, 0, 0, 0);
        beatSyncButton.setBounds(0, 0, 0, 0);
        fullscreenButton.setBounds(0, 0, 0, 0);
        savePresetButton.setBounds(0, 0, 0, 0);
        loadPresetButton.setBounds(0, 0, 0, 0);
        resetDefaultButton.setBounds(0, 0, 0, 0);
        artistNameEditor.setBounds(0, 0, 0, 0);
        trackTitleEditor.setBounds(0, 0, 0, 0);
        labelNameEditor.setBounds(0, 0, 0, 0);
        ctaTextEditor.setBounds(0, 0, 0, 0);
        return;
    }

    b.removeFromLeft(218);
    b.removeFromLeft(12);
    auto right = b.removeFromRight(326).reduced(14, 42);
    auto controls = right.removeFromTop(126);
    controls.removeFromTop(22);
    sessionPresetBox.setBounds(controls.removeFromTop(26));
    controls.removeFromTop(4);
    moduleBox.setBounds(controls.removeFromTop(26));
    auto beatRow = controls.removeFromTop(28);
    beatSyncButton.setBounds(beatRow.removeFromLeft(118));
    beatRow.removeFromLeft(8);
    tapButton.setBounds(beatRow.removeFromLeft(54));
    beatRow.removeFromLeft(8);
    fullscreenButton.setBounds(beatRow.removeFromLeft(56));

    right.removeFromTop(10);
    right.removeFromTop(74);
    right.removeFromTop(10);
    auto brand = right.removeFromTop(204);
    brand.removeFromTop(22);
    auto brandFields = brand.removeFromTop(116);
    auto row = brandFields.removeFromTop(24);
    artistNameEditor.setBounds(row.removeFromRight(204));
    brandFields.removeFromTop(5);
    row = brandFields.removeFromTop(24);
    trackTitleEditor.setBounds(row.removeFromRight(204));
    brandFields.removeFromTop(5);
    row = brandFields.removeFromTop(24);
    labelNameEditor.setBounds(row.removeFromRight(204));
    brandFields.removeFromTop(5);
    row = brandFields.removeFromTop(24);
    ctaTextEditor.setBounds(row.removeFromRight(204));
    auto brandButtons = brand.removeFromBottom(26);
    savePresetButton.setBounds(brandButtons.removeFromLeft(84));
    brandButtons.removeFromLeft(8);
    loadPresetButton.setBounds(brandButtons.removeFromLeft(84));
    brandButtons.removeFromLeft(8);
    resetDefaultButton.setBounds(brandButtons.removeFromLeft(88));

    right.removeFromTop(10);
    auto templates = right.removeFromTop(104);
    templates.removeFromTop(22);
    templateBox.setBounds(templates.removeFromTop(26));

    right.removeFromTop(10);
    auto exportCard = right;
    exportCard.removeFromTop(22);
    exportPresetBox.setBounds(exportCard.removeFromTop(26));
    exportCard.removeFromTop(8);
    themeBox.setBounds(exportCard.removeFromTop(26).removeFromLeft(134));
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

void MixPulseAudioProcessorEditor::drawHeader(juce::Graphics& g, juce::Rectangle<int> area)
{
    drawPanel(g, area, juce::String());
    auto header = area.reduced(18, 12);
    auto title = header.removeFromLeft(250);
    g.setColour(theme.accent);
    g.setFont(juce::Font(27.0f, juce::Font::bold));
    g.drawText(Branding::ProductDisplayName, title.removeFromTop(34), juce::Justification::centredLeft);
    g.setColour(theme.mutedText);
    g.setFont(12.0f);
    g.drawText(juce::String(Branding::ProductVersion) + " / " + Branding::BetaStatus + " / MixPulse internal", title, juce::Justification::centredLeft);

    auto status = header.removeFromLeft(390);
    auto bpm = processor.tapTempo.getBpm();
    drawPill(g, status.removeFromLeft(118).reduced(0, 8), "BPM " + (bpm ? juce::String(*bpm, 1) : "--.-"), theme.accent);
    status.removeFromLeft(8);
    drawPill(g, status.removeFromLeft(128).reduced(0, 8), "Input: host", theme.secondary);
    status.removeFromLeft(8);
    drawPill(g, status.removeFromLeft(132).reduced(0, 8), visualizer && visualizer->isVisible() ? "Output open" : "Output closed", theme.mutedText);
}

void MixPulseAudioProcessorEditor::drawPreviewCanvas(juce::Graphics& g, juce::Rectangle<int> area)
{
    drawPanel(g, area, "Preview Canvas");
    auto inner = area.reduced(18, 42);
    auto meta = inner.removeFromTop(76);
    const auto moduleName = visualModuleName((VisualModuleType)sanitizeVisualModuleIndex(processor.visualRackState.selectedModule.load()));
    const auto* selectedTemplate = getTemplateForSelectedId(templateBox.getSelectedId());
    const juce::String templateName = selectedTemplate != nullptr ? selectedTemplate->name : juce::String("Minimal Meter");
    drawLabelValue(g, meta.removeFromTop(22), "Module", moduleName);
    drawLabelValue(g, meta.removeFromTop(22), "Template", templateName);
    drawLabelValue(g, meta.removeFromTop(22), "Use", selectedTemplate != nullptr ? selectedTemplate->bestFor : "Producer utility");

    inner.removeFromTop(8);
    auto canvas = inner.toFloat().reduced(2.0f);
    g.setColour(juce::Colour::fromRGB(8, 13, 24));
    g.fillRoundedRectangle(canvas, 10.0f);
    g.setColour(theme.grid.withAlpha(0.45f));
    for (int x = (int)canvas.getX(); x < (int)canvas.getRight(); x += 28)
        g.drawVerticalLine(x, canvas.getY(), canvas.getBottom());
    for (int y = (int)canvas.getY(); y < (int)canvas.getBottom(); y += 28)
        g.drawHorizontalLine(y, canvas.getX(), canvas.getRight());

    auto guide = canvas.reduced(34.0f);
    float ratio = 16.0f / 9.0f;
    const auto preset = (OutputPreset)processor.visualRackState.outputPreset.load();
    if (preset == OutputPreset::Square1x1) ratio = 1.0f;
    else if (preset == OutputPreset::Portrait9x16) ratio = 9.0f / 16.0f;
    else if (preset == OutputPreset::Portrait4x5) ratio = 4.0f / 5.0f;

    auto frame = guide;
    if (frame.getWidth() / frame.getHeight() > ratio)
        frame = frame.withWidth(frame.getHeight() * ratio).withCentre(guide.getCentre());
    else
        frame = frame.withHeight(frame.getWidth() / ratio).withCentre(guide.getCentre());

    g.setColour(theme.accent.withAlpha(0.14f));
    g.fillRoundedRectangle(frame, 8.0f);
    g.setColour(theme.accent.withAlpha(0.72f));
    g.drawRoundedRectangle(frame, 8.0f, 1.6f);
    g.setColour(theme.secondary.withAlpha(0.58f));
    g.drawRoundedRectangle(frame.reduced(frame.getWidth() * 0.08f, frame.getHeight() * 0.08f), 6.0f, 1.0f);

    g.setColour(theme.text);
    g.setFont(juce::Font(26.0f, juce::Font::bold));
    auto overlay = frame.toNearestInt().reduced(18);
    g.drawFittedText(fallbackText(processor.brandState.trackTitle, "Track Title"), overlay.removeFromTop(58), juce::Justification::centred, 2);
    g.setFont(15.0f);
    g.drawText(fallbackText(processor.brandState.artistName, "Artist Name"), overlay.removeFromTop(28), juce::Justification::centred);
    g.setColour(theme.mutedText);
    g.setFont(13.0f);
    g.drawText(templateName + " / " + moduleName, overlay.removeFromTop(24), juce::Justification::centred);
    g.drawText(fallbackText(processor.brandState.callToAction, "Out Now") + " / still-frame preview", frame.toNearestInt().reduced(18), juce::Justification::centredBottom);

    auto footer = inner.removeFromBottom(42);
    drawPill(g, footer.removeFromLeft(176).reduced(0, 8), exportPresetStatusText(exportPresetBox.getSelectedId(), processor.selectedExportPreset), theme.accent);
    footer.removeFromLeft(8);
    drawPill(g, footer.removeFromLeft(150).reduced(0, 8), "PNG frame only", theme.secondary);
    footer.removeFromLeft(8);
    drawPill(g, footer.removeFromLeft(162).reduced(0, 8), "Video export: future", theme.mutedText);
}

void MixPulseAudioProcessorEditor::drawRightControlPanel(juce::Graphics& g, juce::Rectangle<int> area)
{
    drawPanel(g, area, "Creator Controls");
    auto r = area.reduced(14, 42);

    auto controls = r.removeFromTop(126);
    drawSectionTitle(g, controls.removeFromTop(20), "Session / Controls");
    drawLabelValue(g, controls.removeFromTop(28), "Session", "");
    drawLabelValue(g, controls.removeFromTop(28), "Visual", "");
    drawLabelValue(g, controls.removeFromTop(22), "Beat sync", processor.visualizerState.beatSync.load() ? "On" : "Off");

    r.removeFromTop(10);
    auto motion = r.removeFromTop(74);
    drawSectionTitle(g, motion.removeFromTop(20), "Visual Controls");
    drawLabelValue(g, motion.removeFromTop(20), "Intensity", juce::String(processor.visualRackState.visualIntensity.load(), 2));
    drawLabelValue(g, motion.removeFromTop(20), "Motion", juce::String(processor.visualRackState.motionAmount.load(), 2));

    r.removeFromTop(10);
    auto brand = r.removeFromTop(204);
    drawSectionTitle(g, brand.removeFromTop(20), "Brand Text");
    drawLabelValue(g, brand.removeFromTop(29), "Artist", "");
    drawLabelValue(g, brand.removeFromTop(29), "Track", "");
    drawLabelValue(g, brand.removeFromTop(29), "Label", "");
    drawLabelValue(g, brand.removeFromTop(29), "CTA", "");
    drawLabelValue(g, brand.removeFromTop(20), "Colors", "primary/accent/background TODO");
    drawLabelValue(g, brand.removeFromTop(20), "Logo", processor.brandState.logoPath.isNotEmpty() ? "preset path" : "placeholder layer");

    r.removeFromTop(10);
    auto templates = r.removeFromTop(120);
    drawSectionTitle(g, templates.removeFromTop(20), "Templates");
    templates.removeFromTop(30);
    if (const auto* tp = getTemplateForSelectedId(templateBox.getSelectedId()))
    {
        drawLabelValue(g, templates.removeFromTop(18), "Purpose", tp->bestFor);
        drawLabelValue(g, templates.removeFromTop(18), "Module", tp->moduleName);
        drawLabelValue(g, templates.removeFromTop(18), "Status", creatorTemplateStatusLabel(*tp));
        drawLabelValue(g, templates.removeFromTop(18), "Fields", templateBrandFieldHint(tp));
        drawLabelValue(g, templates.removeFromTop(18), "Export", exportPresetStatusText(tp->preferredExportPresetIndex + 1, 0));
    }
    else
    {
        drawLabelValue(g, templates.removeFromTop(18), "Status", "Template defaults unavailable");
    }

    r.removeFromTop(10);
    auto exportCard = r;
    drawSectionTitle(g, exportCard.removeFromTop(20), "Export");
    exportCard.removeFromTop(30);
    int exportIndex = 0;
    const auto* preset = getExportPresetForSelection(exportPresetBox.getSelectedId(), processor.selectedExportPreset, exportIndex);
    drawLabelValue(g, exportCard.removeFromTop(20), "Preset", preset != nullptr ? preset->name : "Default unavailable");
    drawLabelValue(g, exportCard.removeFromTop(20), "Size", preset != nullptr ? preset->aspectLabel + " / " + exportPresetDimensionLabel(*preset) : "Current window");
    drawLabelValue(g, exportCard.removeFromTop(20), "Use", preset != nullptr ? preset->useCase : "manual still capture");
    drawLabelValue(g, exportCard.removeFromTop(20), "Workflow", preset != nullptr ? exportPresetWorkflowLabel(*preset) + " / OBS capture" : "Still PNG / OBS capture");
}

void MixPulseAudioProcessorEditor::drawHudPanel(juce::Graphics& g, juce::Rectangle<int> area)
{
    auto meter = area.removeFromLeft(260);
    area.removeFromLeft(14);
    drawMeterColumn(g, meter);
    drawPanel(g, area, "HUD Meter View");
    auto r = area.reduced(18, 44);
    auto& m = processor.analyzer.getMeterData();
    drawLabelValue(g, r.removeFromTop(28), "BPM", processor.tapTempo.getBpm() ? juce::String(*processor.tapTempo.getBpm(), 1) : "--.-");
    drawLabelValue(g, r.removeFromTop(28), "LUFS M", juce::String(m.lufsM.load(), 1));
    drawLabelValue(g, r.removeFromTop(28), "True Peak", juce::String(gainToDb(m.truePeak.load()), 1) + " dB");
    drawLabelValue(g, r.removeFromTop(28), "Output", visualizer && visualizer->isVisible() ? "open" : "closed");
    drawLabelValue(g, r.removeFromTop(28), "Export", "PNG still only");
}

void MixPulseAudioProcessorEditor::timerCallback(){ repaint(); }
void MixPulseAudioProcessorEditor::openVisualizer()
{
    if(!visualizer)
        visualizer=std::make_unique<VisualizerWindow>(processor.analyzer,processor.beatPulse,processor.visualizerState,processor.visualRackState,processor.brandState);

    if (visualizer)
    {
        visualizer->prepareToShow();
        setStatusMessage("Output window ready for OBS Window Capture");
    }
}

void MixPulseAudioProcessorEditor::syncBrandEditorsToState()
{
    BrandLayer::normalizeBrandState(processor.brandState);
    artistNameEditor.setText(processor.brandState.artistName, juce::dontSendNotification);
    trackTitleEditor.setText(processor.brandState.trackTitle, juce::dontSendNotification);
    labelNameEditor.setText(processor.brandState.labelName, juce::dontSendNotification);
    ctaTextEditor.setText(processor.brandState.callToAction, juce::dontSendNotification);
}

void MixPulseAudioProcessorEditor::applyBrandEditorsToState()
{
    processor.brandState.artistName = sanitizeBrandTextInput(artistNameEditor.getText(), "Artist Name");
    processor.brandState.trackTitle = sanitizeBrandTextInput(trackTitleEditor.getText(), "Track Title");
    processor.brandState.labelName = sanitizeBrandTextInput(labelNameEditor.getText(), "Label Name");
    processor.brandState.callToAction = sanitizeBrandTextInput(ctaTextEditor.getText(), "Out Now");
    BrandLayer::normalizeBrandState(processor.brandState);
    setStatusMessage("Brand updated");
    repaint();
}

void MixPulseAudioProcessorEditor::applySelectedExportPresetToOutputGuide()
{
    const int idx = safeExportPresetIndex(exportPresetBox.getSelectedId(), processor.selectedExportPreset);
    processor.selectedExportPreset = idx;
    switch (idx)
    {
        case 1: processor.visualRackState.outputPreset.store((int) OutputPreset::Portrait9x16); break;
        case 2: processor.visualRackState.outputPreset.store((int) OutputPreset::Square1x1); break;
        case 3: processor.visualRackState.outputPreset.store((int) OutputPreset::Portrait4x5); break;
        case 4: case 5: processor.visualRackState.outputPreset.store((int) OutputPreset::Landscape16x9); break;
        default: processor.visualRackState.outputPreset.store((int) OutputPreset::Free); break;
    }
    if (exportPresetBox.getSelectedId() <= 0)
        exportPresetBox.setSelectedId(idx + 1, juce::dontSendNotification);

    setStatusMessage("Export preset: " + exportPresetStatusText(idx + 1, idx));
}

void MixPulseAudioProcessorEditor::applyBuiltInSessionPreset(int presetIndex)
{
    const auto& presets = getBuiltInSessionPresets();
    if (presets.empty())
    {
        setStatusMessage("Built-in presets unavailable");
        return;
    }

    const int safePresetIndex = juce::jlimit(0, (int)presets.size() - 1, presetIndex);
    const auto& preset = presets[(size_t)safePresetIndex];
    const int templateIndex = sanitizeCreatorTemplateIndex(preset.templateIndex);
    const auto& templates = getBuiltInCreatorTemplates();

    if (!templates.empty())
    {
        templateBox.setSelectedId(templateIndex + 1, juce::sendNotificationSync);
        const auto& selectedTemplate = templates[(size_t)templateIndex];
        processor.visualRackState.selectedModule.store(sanitizeVisualModuleIndex((int)selectedTemplate.module));
        const int exportIndex = safeExportPresetIndex(selectedTemplate.preferredExportPresetIndex + 1, 0);
        exportPresetBox.setSelectedId(exportIndex + 1, juce::sendNotificationSync);
    }

    processor.visualRackState.visualIntensity.store(juce::jlimit(0.0f, 2.0f, preset.visualIntensity));
    processor.visualRackState.motionAmount.store(juce::jlimit(0.0f, 1.0f, preset.motionAmount));
    processor.visualRackState.bloomAmount.store(juce::jlimit(0.0f, 1.0f, preset.bloomAmount));
    processor.brandState.artistName = preset.artist;
    processor.brandState.trackTitle = preset.title;
    processor.brandState.labelName = preset.label;
    processor.brandState.callToAction = preset.cta;
    processor.brandState.releaseStatusText = preset.cta;
    processor.brandState.brandPrimaryColor = preset.primary;
    processor.brandState.brandSecondaryColor = preset.secondary;
    processor.brandState.brandAccentColor = preset.accent;
    BrandLayer::normalizeBrandState(processor.brandState);
    syncBrandEditorsToState();
    syncModuleBoxToProcessor();
    setStatusMessage("Built-in preset: " + juce::String(preset.name) + " / " + juce::String(preset.status));
}

void MixPulseAudioProcessorEditor::exportScreenshot()
{
    if (!visualizer) openVisualizer();

    const auto& presets = getBuiltInExportPresets();
    if (presets.empty())
    {
        setStatusMessage("Frame capture failed: no export presets available");
        return;
    }

    const int presetIndex = juce::jlimit(0, (int)presets.size() - 1, exportPresetBox.getSelectedId() - 1);
    const auto& preset = presets[(size_t)presetIndex];
    if (!preset.enabled)
    {
        setStatusMessage("Frame capture TODO: " + preset.name + " is not available in v0.2");
        return;
    }

    auto exportDir = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile(Branding::ProductDisplayName).getChildFile("Exports");
    if (!exportDir.createDirectory())
    {
        setStatusMessage("Frame capture failed: cannot create Documents/WaveFrame/Exports");
        return;
    }

    auto* sourceComponent = visualizer ? visualizer->getContentComponent() : nullptr;
    if (!sourceComponent || sourceComponent->getWidth() <= 0 || sourceComponent->getHeight() <= 0)
        sourceComponent = this;

    int w = sourceComponent->getWidth(), h = sourceComponent->getHeight();
    if (preset.width > 0 && preset.height > 0) { w = preset.width; h = preset.height; }
    if (w <= 0 || h <= 0) { setStatusMessage("Frame capture failed: invalid render size"); return; }

    juce::Image img(juce::Image::ARGB, w, h, true);
    juce::Graphics gg(img);
    if (preset.width > 0 && preset.height > 0)
    {
        VisualizerRenderer renderer;
        renderer.render(gg, { 0, 0, w, h }, processor.analyzer.getSpectrumSnapshot(), processor.visualizerState.mode.load(), processor.beatPulse.getPulse(), processor.visualRackState, &processor.brandState);
    }
    else
    {
        sourceComponent->paintEntireComponent(gg, false);
    }

    auto stamp = juce::Time::getCurrentTime().formatted("%Y-%m-%d_%H-%M-%S");
    auto safeName = exportPresetShortLabel(presetIndex).removeCharacters(" /:");
    auto file = exportDir.getChildFile("WaveFrame_" + safeName + "_" + stamp + ".png");
    juce::FileOutputStream os(file);
    juce::PNGImageFormat png;
    if (!os.openedOk()) { setStatusMessage("Frame capture failed: cannot create output file"); return; }
    if (!png.writeImageToStream(img, os)) { setStatusMessage("Frame capture failed: PNG encoder error"); return; }

    setStatusMessage("Captured still PNG: " + exportPresetShortLabel(presetIndex) + " " + juce::String(w) + "x" + juce::String(h));
}


void MixPulseAudioProcessorEditor::syncUiToProcessorState()
{
    beatSyncButton.setToggleState(processor.visualizerState.beatSync.load(), juce::dontSendNotification);
    hudMode = processor.hudEnabled;
    processor.selectedExportPreset = safeExportPresetIndex(processor.selectedExportPreset + 1, 0);
    exportPresetBox.setSelectedId(processor.selectedExportPreset + 1, juce::dontSendNotification);
    const int themeId = processor.selectedTheme > 0 ? processor.selectedTheme : 1;
    themeBox.setSelectedId(themeId, juce::dontSendNotification);
    syncModuleBoxToProcessor();
    BrandLayer::normalizeBrandState(processor.brandState);
    syncBrandEditorsToState();
    applySelectedExportPresetToOutputGuide();
}

void MixPulseAudioProcessorEditor::syncModuleBoxToProcessor()
{
    int module = sanitizeVisualModuleIndex(processor.visualRackState.selectedModule.load());
    if (!comboHasItemId(moduleBox, module + 1))
        module = (int)VisualModuleType::SpectrumBars;

    processor.visualRackState.selectedModule.store(module);
    moduleBox.setSelectedId(module + 1, juce::dontSendNotification);
}

void MixPulseAudioProcessorEditor::saveUserPreset()
{
    applyBrandEditorsToState();
    processor.selectedExportPreset = safeExportPresetIndex(exportPresetBox.getSelectedId(), processor.selectedExportPreset);
    processor.selectedTheme = themeBox.getSelectedId() > 0 ? themeBox.getSelectedId() : 1;
    processor.hudEnabled = hudMode;
    BrandLayer::normalizeBrandState(processor.brandState);
    if (BrandLayer::savePreset(processor.brandState, BrandLayer::defaultPresetFile()))
        setStatusMessage("Brand preset saved locally: Documents/WaveFrame/Presets");
    else
        setStatusMessage("Brand preset save failed safely");
}

void MixPulseAudioProcessorEditor::loadUserPreset()
{
    if (!BrandLayer::loadPreset(processor.brandState, BrandLayer::defaultPresetFile()))
    {
        setStatusMessage("Brand preset load failed safely - current session kept");
        return;
    }
    BrandLayer::normalizeBrandState(processor.brandState);
    syncBrandEditorsToState();
    if (processor.brandState.logoPath.isNotEmpty())
    {
        auto logo = juce::File(processor.brandState.logoPath);
        if (logo.existsAsFile()) setStatusMessage("Brand preset loaded - Logo path valid");
        else setStatusMessage("Brand preset loaded - Logo placeholder used");
    }
    else setStatusMessage("Brand preset loaded");
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
    if (templateBox.getNumItems() > 0)
        templateBox.setSelectedId(1, juce::dontSendNotification);
    if (sessionPresetBox.getNumItems() > 0)
        sessionPresetBox.setSelectedId(1, juce::dontSendNotification);
    syncUiToProcessorState();
    syncBrandEditorsToState();
    setStatusMessage("Brand fields reset to default session");
}



