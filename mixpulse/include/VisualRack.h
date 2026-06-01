#pragma once

#include <atomic>
#include <vector>
#include <JuceHeader.h>

#include "MeterData.h"
#include "BeatPulseEngine.h"
#include "TapTempoEngine.h"

enum class VisualModuleType { SpectrumBars, Waveform, Vectorscope, LogoPulse, TextCard, GradientField, ParticleBurstPlaceholder, TunnelPlaceholder, PlasmaPlaceholder, TypePulse, PromoCard, Particles };
enum class VisualFxType { Bloom, Mirror, Colorize, Scanlines, ChromaticSplit, FeedbackPlaceholder, PixelatePlaceholder, DisplacementPlaceholder };
enum class ModSource { None, FullAmplitude, BassEnergy, LowMidEnergy, MidEnergy, HighEnergy, BeatPulse, TapTempoBpm, LufsMPlaceholder };
enum class OutputPreset { Free, Landscape16x9, Square1x1, Portrait9x16, Portrait4x5, Thumbnail16x9 };

struct VisualRackState
{
    std::atomic<int> selectedModule { (int) VisualModuleType::SpectrumBars };
    std::atomic<bool> fxBloom { true }, fxMirror { true }, fxColorize { true }, fxScanlines { false }, fxChromaticSplit { false };
    std::atomic<int> primaryModSource { (int) ModSource::FullAmplitude };
    std::atomic<int> outputPreset { (int) OutputPreset::Landscape16x9 };
    std::atomic<float> bloomAmount { 0.45f }, colorizeAmount { 0.5f }, scanlineAmount { 0.15f }, chromaticAmount { 0.12f }, visualIntensity { 0.75f }, motionAmount { 0.65f };
};

struct VisualRackPreset
{
    const char* name;
    VisualModuleType module;
    OutputPreset outputPreset;
    ModSource primaryModSource;
    bool bloom, mirror, colorize, scanlines, chromaticSplit;
    float bloomAmount, colorizeAmount, scanlineAmount, chromaticAmount, visualIntensity, motionAmount;
};

const std::vector<VisualRackPreset>& getBuiltInVisualRackPresets();
void applyPresetToRack(const VisualRackPreset& preset, VisualRackState& rack);
float getModulationValue(ModSource source, const MeterData& meter, const BeatPulseEngine& beatPulse, const TapTempoEngine& tapTempo);

bool isValidVisualModuleIndex(int value);
int sanitizeVisualModuleIndex(int value);
bool isValidOutputPresetIndex(int value);
int sanitizeOutputPresetIndex(int value);
juce::String visualModuleName(VisualModuleType module);
