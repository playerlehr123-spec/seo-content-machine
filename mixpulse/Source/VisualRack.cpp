#include "VisualRack.h"

namespace
{
const std::vector<VisualRackPreset> kBuiltInVisualRackPresets {
    {"Dark Neon Meter", VisualModuleType::SpectrumBars, OutputPreset::Landscape16x9, ModSource::FullAmplitude, true, true, true, false, false, 0.45f, 0.5f, 0.15f, 0.12f, 0.75f, 0.65f},
    {"Stream Overlay", VisualModuleType::SpectrumBars, OutputPreset::Landscape16x9, ModSource::BeatPulse, true, true, true, true, false, 0.35f, 0.45f, 0.2f, 0.1f, 0.7f, 0.7f},
    {"Reel Visualizer", VisualModuleType::SpectrumBars, OutputPreset::Portrait9x16, ModSource::BeatPulse, true, true, true, false, true, 0.45f, 0.55f, 0.1f, 0.2f, 0.8f, 0.75f},
    {"Logo Reactor", VisualModuleType::LogoPulse, OutputPreset::Square1x1, ModSource::BeatPulse, true, false, true, false, false, 0.5f, 0.55f, 0.0f, 0.0f, 0.75f, 0.6f},
    {"Type Pulse", VisualModuleType::TypePulse, OutputPreset::Portrait9x16, ModSource::BeatPulse, true, false, true, false, false, 0.35f, 0.6f, 0.0f, 0.0f, 0.8f, 0.7f},
    {"Promo Card", VisualModuleType::PromoCard, OutputPreset::Portrait4x5, ModSource::FullAmplitude, true, false, true, false, false, 0.25f, 0.45f, 0.0f, 0.0f, 0.65f, 0.35f},
    {"Particles v1", VisualModuleType::Particles, OutputPreset::Landscape16x9, ModSource::BeatPulse, true, false, true, false, true, 0.45f, 0.55f, 0.0f, 0.16f, 0.75f, 0.8f},
    {"Album Art Background", VisualModuleType::GradientField, OutputPreset::Square1x1, ModSource::FullAmplitude, true, false, true, false, false, 0.2f, 0.5f, 0.0f, 0.0f, 0.5f, 0.45f},
    {"Minimal Meter", VisualModuleType::SpectrumBars, OutputPreset::Free, ModSource::FullAmplitude, false, false, false, false, false, 0.0f, 0.0f, 0.0f, 0.0f, 0.6f, 0.4f},
};
}

const std::vector<VisualRackPreset>& getBuiltInVisualRackPresets() { return kBuiltInVisualRackPresets; }

void applyPresetToRack(const VisualRackPreset& preset, VisualRackState& rack)
{
    rack.selectedModule.store((int) preset.module);
    rack.outputPreset.store((int) preset.outputPreset);
    rack.primaryModSource.store((int) preset.primaryModSource);
    rack.fxBloom.store(preset.bloom);
    rack.fxMirror.store(preset.mirror);
    rack.fxColorize.store(preset.colorize);
    rack.fxScanlines.store(preset.scanlines);
    rack.fxChromaticSplit.store(preset.chromaticSplit);
    rack.bloomAmount.store(preset.bloomAmount);
    rack.colorizeAmount.store(preset.colorizeAmount);
    rack.scanlineAmount.store(preset.scanlineAmount);
    rack.chromaticAmount.store(preset.chromaticAmount);
    rack.visualIntensity.store(preset.visualIntensity);
    rack.motionAmount.store(preset.motionAmount);
}

float getModulationValue(ModSource source, const MeterData& meter, const BeatPulseEngine& beatPulse, const TapTempoEngine& tapTempo)
{
    switch (source)
    {
        case ModSource::None: return 0.0f;
        case ModSource::FullAmplitude: return juce::jlimit(0.0f, 1.0f, 0.5f * (meter.rmsL.load() + meter.rmsR.load()));
        case ModSource::BassEnergy: return juce::jlimit(0.0f, 1.0f, meter.bassEnergy.load());
        case ModSource::LowMidEnergy: return juce::jlimit(0.0f, 1.0f, meter.lowMidEnergy.load());
        case ModSource::MidEnergy: return juce::jlimit(0.0f, 1.0f, meter.midEnergy.load());
        case ModSource::HighEnergy: return juce::jlimit(0.0f, 1.0f, meter.highEnergy.load());
        case ModSource::BeatPulse: return juce::jlimit(0.0f, 1.0f, beatPulse.getPulse());
        case ModSource::TapTempoBpm:
            if (auto bpm = tapTempo.getBpm())
                return juce::jlimit(0.0f, 1.0f, (float) ((*bpm - 60.0) / 140.0));
            return 0.0f;
        case ModSource::LufsMPlaceholder:
            return juce::jlimit(0.0f, 1.0f, (meter.lufsM.load() + 60.0f) / 60.0f);
    }
    return 0.0f;
}

bool isValidVisualModuleIndex(int value)
{
    switch ((VisualModuleType)value)
    {
        case VisualModuleType::SpectrumBars:
        case VisualModuleType::Waveform:
        case VisualModuleType::Vectorscope:
        case VisualModuleType::LogoPulse:
        case VisualModuleType::TextCard:
        case VisualModuleType::GradientField:
        case VisualModuleType::ParticleBurstPlaceholder:
        case VisualModuleType::TunnelPlaceholder:
        case VisualModuleType::PlasmaPlaceholder:
        case VisualModuleType::TypePulse:
        case VisualModuleType::PromoCard:
        case VisualModuleType::Particles:
            return true;
    }
    return false;
}

int sanitizeVisualModuleIndex(int value)
{
    return isValidVisualModuleIndex(value) ? value : (int)VisualModuleType::SpectrumBars;
}

bool isValidOutputPresetIndex(int value)
{
    switch ((OutputPreset)value)
    {
        case OutputPreset::Free:
        case OutputPreset::Landscape16x9:
        case OutputPreset::Square1x1:
        case OutputPreset::Portrait9x16:
        case OutputPreset::Portrait4x5:
        case OutputPreset::Thumbnail16x9:
            return true;
    }
    return false;
}

int sanitizeOutputPresetIndex(int value)
{
    return isValidOutputPresetIndex(value) ? value : (int)OutputPreset::Landscape16x9;
}

juce::String visualModuleName(VisualModuleType module)
{
    if (!isValidVisualModuleIndex((int)module))
        module = VisualModuleType::SpectrumBars;

    switch (module)
    {
        case VisualModuleType::SpectrumBars: return "Spectrum Bars";
        case VisualModuleType::Waveform: return "Waveform";
        case VisualModuleType::Vectorscope: return "Vectorscope";
        case VisualModuleType::LogoPulse: return "Logo Reactor";
        case VisualModuleType::TextCard: return "Text Card";
        case VisualModuleType::GradientField: return "Gradient Field";
        case VisualModuleType::ParticleBurstPlaceholder: return "Particle Burst";
        case VisualModuleType::TunnelPlaceholder: return "Tunnel";
        case VisualModuleType::PlasmaPlaceholder: return "Plasma";
        case VisualModuleType::TypePulse: return "Type Pulse";
        case VisualModuleType::PromoCard: return "Promo Card";
        case VisualModuleType::Particles: return "Particles";
    }
    return "Unknown";
}
