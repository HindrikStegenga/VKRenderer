//
// Created by hindrik on 17-11-18.
//

#ifndef VKRENDERER_CONFIGTYPES_H
#define VKRENDERER_CONFIGTYPES_H

#include <MetaStuff/JsonCast.h>
#include <MetaStuff/Meta.h>
#include "SerializeMacro.h"

#include <string>
#include <cstdint>

using std::string;
using std::vector;

struct ApplicationSettings {
    string applicationName;
    string engineName;
    uint32_t applicationVersionMajor;
    uint32_t applicationVersionMinor;
    uint32_t applicationVersionPatch;
    uint32_t engineVersionMajor;
    uint32_t engineVersionMinor;
    uint32_t engineVersionPatch;
    bool debugMode;
};

SERIALIZE_START(ApplicationSettings)
    SERIALIZE_MEMBER("applicationName", ApplicationSettings::applicationName),
    SERIALIZE_MEMBER("engineName", ApplicationSettings::engineName),
    SERIALIZE_MEMBER("applicationVersionMajor", ApplicationSettings::applicationVersionMajor),
    SERIALIZE_MEMBER("applicationVersionMinor", ApplicationSettings::applicationVersionMinor),
    SERIALIZE_MEMBER("applicationVersionPatch", ApplicationSettings::applicationVersionPatch),
    SERIALIZE_MEMBER("engineVersionMajor", ApplicationSettings::engineVersionMajor),
    SERIALIZE_MEMBER("engineVersionMinor", ApplicationSettings::engineVersionMinor),
    SERIALIZE_MEMBER("engineVersionPatch", ApplicationSettings::engineVersionPatch),
    SERIALIZE_MEMBER("debugMode", ApplicationSettings::debugMode)
SERIALIZE_END

struct GraphicsSettings {
    uint32_t resolutionX;
    uint32_t resolutionY;
    bool preferIGPU;
    bool preventTearing;
    bool limitFrameRate;
};

SERIALIZE_START(GraphicsSettings)
    SERIALIZE_MEMBER("resolutionX", GraphicsSettings::resolutionX),
    SERIALIZE_MEMBER("resolutionY", GraphicsSettings::resolutionY),
    SERIALIZE_MEMBER("preferIGPU", GraphicsSettings::preferIGPU),
    SERIALIZE_MEMBER("preventTearing", GraphicsSettings::preventTearing),
    SERIALIZE_MEMBER("limitFrameRate", GraphicsSettings::limitFrameRate)
SERIALIZE_END

struct VulkanSettings {
    string renderMode;
    uint32_t preferredFramesInFlight;
};

SERIALIZE_START(VulkanSettings)
    SERIALIZE_MEMBER("renderMode", VulkanSettings::renderMode),
    SERIALIZE_MEMBER("preferredFramesInFlight", VulkanSettings::preferredFramesInFlight)
SERIALIZE_END





#endif //VKRENDERER_CONFIGTYPES_H
