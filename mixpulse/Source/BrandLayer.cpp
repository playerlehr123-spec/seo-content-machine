#include "BrandLayer.h"

namespace BrandLayer
{
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
    o->setProperty("logoOpacity", s.logoOpacity);
    o->setProperty("logoScale", s.logoScale);
    o->setProperty("logoPositionMode", s.logoPositionMode);
    o->setProperty("brandPrimaryColor", s.brandPrimaryColor.toString());
    o->setProperty("brandSecondaryColor", s.brandSecondaryColor.toString());
    o->setProperty("brandAccentColor", s.brandAccentColor.toString());
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
    s.artistName = o->getProperty("artistName", s.artistName).toString();
    s.trackTitle = o->getProperty("trackTitle", s.trackTitle).toString();
    s.labelName = o->getProperty("labelName", s.labelName).toString();
    s.callToAction = o->getProperty("callToAction", s.callToAction).toString();
    s.releaseStatusText = o->getProperty("releaseStatusText", s.releaseStatusText).toString();
    s.logoPath = o->getProperty("logoPath", s.logoPath).toString();
    s.hasLogo = (bool) o->getProperty("hasLogo", s.hasLogo);
    s.logoOpacity = (float) o->getProperty("logoOpacity", s.logoOpacity);
    s.logoScale = (float) o->getProperty("logoScale", s.logoScale);
    s.logoPositionMode = (int) o->getProperty("logoPositionMode", s.logoPositionMode);
    s.brandPrimaryColor = juce::Colour::fromString(o->getProperty("brandPrimaryColor", s.brandPrimaryColor.toString()).toString());
    s.brandSecondaryColor = juce::Colour::fromString(o->getProperty("brandSecondaryColor", s.brandSecondaryColor.toString()).toString());
    s.brandAccentColor = juce::Colour::fromString(o->getProperty("brandAccentColor", s.brandAccentColor.toString()).toString());
    return true;
}

juce::File defaultPresetFile()
{
    return juce::File::getSpecialLocation(juce::File::userDocumentsDirectory)
        .getChildFile("WaveFrame").getChildFile("Presets").getChildFile("WaveFrame_UserPreset.json");
}
}
