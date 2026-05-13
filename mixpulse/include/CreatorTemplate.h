#pragma once
#include <string>
#include <vector>

namespace mixpulse {
struct CreatorTemplate {
    std::string name;
    std::string description;
    std::string recommendedScene;
    std::string recommendedOutputPreset;
    std::string recommendedModule;
    std::string defaultBrandText;
};

std::vector<CreatorTemplate> builtInCreatorTemplates();
}
