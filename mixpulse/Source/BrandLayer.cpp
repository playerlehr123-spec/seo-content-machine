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
}

static juce::var toVar(const CreatorBrandState& s)
{
    auto* o = new juce::DynamicObject();
    o->setProperty("artistName", s.artistName);
    o->setProperty("trackTitle", s.trackTitle);
    o->setProperty("labelName", s.labelName);
    o->setProperty("callToAction", s.callToAction);
    o->setProperty("releaseStatusText", s.releaseStatusText);
    o->setProperty("logoPath", s.logoPath);
    o->setProperty("hasLogo", s.hasLogo);
    o->setProperty("showLogoPlaceholder", s.showLogoPlaceholder);
    o->setProperty("showTextOverlay", s.showTextOverlay);
    o->setProperty("logoOpacity", s.logoOpacity);
    o->setProperty("logoScale", s.logoScale);
    o->setProperty("logoPositionMode", s.logoPositionMode);
    o->setProperty("brandPrimaryColor", s.brandPrimaryColor.toString());
    o->setProperty("brandSecondaryColor", s.brandSecondaryColor.toString());
    o->setProperty("brandAccentColor", s.brandAccentColor.toString());
    o->setProperty("brandBackgroundColor", s.brandBackgroundColor.toString());
    o->setProperty("brandTextColor", s.brandTextColor.toString());
    return o;
}

bool savePreset(const CreatorBrandState& s, const juce::File& path)
{
    path.getParentDirectory().createDirectory();
    return path.replaceWithText(juce::JSON::toString(toVar(s), true));
}

bool loadPreset(CreatorBrandState& s, const juce::File& path)
{
    if (!path.existsAsFile()) return false;
    auto v = juce::JSON::parse(path);
    auto* o = v.getDynamicObject();
    if (!o) return false;
    s.artistName = getPropertyOrDefault(o, "artistName", s.artistName).toString();
    s.trackTitle = getPropertyOrDefault(o, "trackTitle", s.trackTitle).toString();
    s.labelName = getPropertyOrDefault(o, "labelName", s.labelName).toString();
    s.callToAction = getPropertyOrDefault(o, "callToAction", s.callToAction).toString();
    s.releaseStatusText = getPropertyOrDefault(o, "releaseStatusText", s.releaseStatusText).toString();
    s.logoPath = getPropertyOrDefault(o, "logoPath", s.logoPath).toString();
    s.hasLogo = (bool) getPropertyOrDefault(o, "hasLogo", s.hasLogo);
    s.showLogoPlaceholder = (bool) getPropertyOrDefault(o, "showLogoPlaceholder", s.showLogoPlaceholder);
    s.showTextOverlay = (bool) getPropertyOrDefault(o, "showTextOverlay", s.showTextOverlay);
    s.logoOpacity = (float) (double) getPropertyOrDefault(o, "logoOpacity", s.logoOpacity);
    s.logoScale = (float) (double) getPropertyOrDefault(o, "logoScale", s.logoScale);
    s.logoPositionMode = (int) getPropertyOrDefault(o, "logoPositionMode", s.logoPositionMode);
    s.brandPrimaryColor = juce::Colour::fromString(getPropertyOrDefault(o, "brandPrimaryColor", s.brandPrimaryColor.toString()).toString());
    s.brandSecondaryColor = juce::Colour::fromString(getPropertyOrDefault(o, "brandSecondaryColor", s.brandSecondaryColor.toString()).toString());
    s.brandAccentColor = juce::Colour::fromString(getPropertyOrDefault(o, "brandAccentColor", s.brandAccentColor.toString()).toString());
    s.brandBackgroundColor = juce::Colour::fromString(getPropertyOrDefault(o, "brandBackgroundColor", s.brandBackgroundColor.toString()).toString());
    s.brandTextColor = juce::Colour::fromString(getPropertyOrDefault(o, "brandTextColor", s.brandTextColor.toString()).toString());
    return true;
}

juce::File defaultPresetFile()
{
    return juce::File::getSpecialLocation(juce::File::userDocumentsDirectory)
        .getChildFile("WaveFrame").getChildFile("Presets").getChildFile("WaveFrame_UserPreset.json");
}
}
