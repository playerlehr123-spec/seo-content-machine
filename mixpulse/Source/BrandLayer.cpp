#include "BrandLayer.h"

namespace BrandLayer
{
namespace
{
juce::var getPropertyOrDefault(const juce::DynamicObject* obj, const juce::Identifier& key, juce::var fallback)
{
    if (obj == nullptr)
        return fallback;

    if (obj->hasProperty(key))
        return obj->getProperty(key);

    return fallback;
}

int sanitizeLogoPositionMode(int value)
{
    switch ((LogoPositionMode)value)
    {
        case LogoPositionMode::Center:
        case LogoPositionMode::CornerTopLeft:
        case LogoPositionMode::CornerTopRight:
        case LogoPositionMode::CornerBottomLeft:
        case LogoPositionMode::CornerBottomRight:
        case LogoPositionMode::Watermark:
            return value;
    }
    return (int)LogoPositionMode::Center;
}

juce::String defaultIfEmpty(const juce::String& value, const juce::String& fallback)
{
    return value.trim().isNotEmpty() ? value : fallback;
}
}

static juce::var toVar(const CreatorBrandState& s)
{
    CreatorBrandState normalized = s;
    normalizeBrandState(normalized);

    auto* o = new juce::DynamicObject();
    o->setProperty("schemaVersion", 1);
    o->setProperty("product", "WaveFrame");
    o->setProperty("artistName", normalized.artistName);
    o->setProperty("trackTitle", normalized.trackTitle);
    o->setProperty("labelName", normalized.labelName);
    o->setProperty("callToAction", normalized.callToAction);
    o->setProperty("releaseStatusText", normalized.releaseStatusText);
    o->setProperty("logoPath", normalized.logoPath);
    o->setProperty("hasLogo", normalized.hasLogo);
    o->setProperty("logoOpacity", normalized.logoOpacity);
    o->setProperty("logoScale", normalized.logoScale);
    o->setProperty("logoPositionMode", normalized.logoPositionMode);
    o->setProperty("brandPrimaryColor", normalized.brandPrimaryColor.toString());
    o->setProperty("brandSecondaryColor", normalized.brandSecondaryColor.toString());
    o->setProperty("brandAccentColor", normalized.brandAccentColor.toString());
    return o;
}

void normalizeBrandState(CreatorBrandState& s)
{
    s.artistName = defaultIfEmpty(s.artistName, "Artist Name");
    s.trackTitle = defaultIfEmpty(s.trackTitle, "Track Title");
    s.labelName = defaultIfEmpty(s.labelName, "Label Name");
    s.callToAction = defaultIfEmpty(s.callToAction, "Out Now");
    s.releaseStatusText = defaultIfEmpty(s.releaseStatusText, "Out Now");
    s.logoOpacity = juce::jlimit(0.0f, 1.0f, s.logoOpacity);
    s.logoScale = juce::jlimit(0.1f, 3.0f, s.logoScale);
    s.logoPositionMode = sanitizeLogoPositionMode(s.logoPositionMode);
    s.hasLogo = s.logoPath.isNotEmpty() && juce::File(s.logoPath).existsAsFile();
}

bool savePreset(const CreatorBrandState& s, const juce::File& path)
{
    auto dir = path.getParentDirectory();
    dir.createDirectory();
    if (!dir.isDirectory())
        return false;

    return path.replaceWithText(juce::JSON::toString(toVar(s), true));
}

bool loadPreset(CreatorBrandState& s, const juce::File& path)
{
    if (!path.existsAsFile()) return false;
    auto v = juce::JSON::parse(path);
    auto* o = v.getDynamicObject();
    if (!o) return false;

    CreatorBrandState loaded = s;
    loaded.artistName = getPropertyOrDefault(o, "artistName", loaded.artistName).toString();
    loaded.trackTitle = getPropertyOrDefault(o, "trackTitle", loaded.trackTitle).toString();
    loaded.labelName = getPropertyOrDefault(o, "labelName", loaded.labelName).toString();
    loaded.callToAction = getPropertyOrDefault(o, "callToAction", loaded.callToAction).toString();
    loaded.releaseStatusText = getPropertyOrDefault(o, "releaseStatusText", loaded.releaseStatusText).toString();
    loaded.logoPath = getPropertyOrDefault(o, "logoPath", loaded.logoPath).toString();
    loaded.hasLogo = (bool) getPropertyOrDefault(o, "hasLogo", loaded.hasLogo);
    loaded.logoOpacity = (float) (double) getPropertyOrDefault(o, "logoOpacity", loaded.logoOpacity);
    loaded.logoScale = (float) (double) getPropertyOrDefault(o, "logoScale", loaded.logoScale);
    loaded.logoPositionMode = (int) getPropertyOrDefault(o, "logoPositionMode", loaded.logoPositionMode);
    loaded.brandPrimaryColor = juce::Colour::fromString(getPropertyOrDefault(o, "brandPrimaryColor", loaded.brandPrimaryColor.toString()).toString());
    loaded.brandSecondaryColor = juce::Colour::fromString(getPropertyOrDefault(o, "brandSecondaryColor", loaded.brandSecondaryColor.toString()).toString());
    loaded.brandAccentColor = juce::Colour::fromString(getPropertyOrDefault(o, "brandAccentColor", loaded.brandAccentColor.toString()).toString());
    normalizeBrandState(loaded);
    s = loaded;
    return true;
}

juce::File defaultPresetFile()
{
    return juce::File::getSpecialLocation(juce::File::userDocumentsDirectory)
        .getChildFile("WaveFrame").getChildFile("Presets").getChildFile("WaveFrame_UserPreset.json");
}
}
