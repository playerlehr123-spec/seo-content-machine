#pragma once
#include <atomic>
#include <array>
#include <JuceHeader.h>

enum class VisualModuleType { SpectrumBars, Waveform, Vectorscope, LogoPulse, TextCard, GradientField, ParticleBurstPlaceholder, TunnelPlaceholder, PlasmaPlaceholder };
enum class VisualFxType { Bloom, Mirror, Colorize, Scanlines, ChromaticSplit, FeedbackPlaceholder, PixelatePlaceholder, DisplacementPlaceholder };
enum class ModSource { None, FullAmplitude, BassEnergy, LowMidEnergy, MidEnergy, HighEnergy, BeatPulse, TapTempoBpm, LufsMPlaceholder };
enum class OutputPreset { Free, Landscape16x9, Square1x1, Portrait9x16, Portrait4x5, Thumbnail16x9 };

struct VisualRackState
{
    std::atomic<int> selectedModule {(int)VisualModuleType::SpectrumBars};
    std::atomic<bool> fxBloom { true }, fxMirror { true }, fxColorize { true }, fxScanlines { false }, fxChromaticSplit { false };
    std::atomic<int> primaryModSource {(int)ModSource::FullAmplitude};
    std::atomic<int> outputPreset {(int)OutputPreset::Landscape16x9};
    std::atomic<float> bloomAmount { 0.5f }, colorizeAmount { 0.5f }, scanlineAmount { 0.2f }, chromaticAmount { 0.15f }, visualIntensity { 1.0f }, motionAmount { 0.8f };
};

struct VisualRackPreset { const char* name; VisualModuleType module; ModSource mod; OutputPreset output; bool bloom, mirror, colorize, scanlines, chroma; };
std::array<VisualRackPreset, 5> getBuiltInVisualRackPresets();
