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

struct GraphicsSettings {
    uint32_t resolutionX;
    uint32_t resolutionY;
    bool preferIGPU;
    bool verticalSync;
    bool lowPower;
};

SERIALIZE_START(GraphicsSettings)
    SERIALIZE_MEMBER("resolutionX", GraphicsSettings::resolutionX),
    SERIALIZE_MEMBER("resolutionY", GraphicsSettings::resolutionY),
    SERIALIZE_MEMBER("preferIGPU", GraphicsSettings::preferIGPU),
    SERIALIZE_MEMBER("verticalSync", GraphicsSettings::verticalSync),
    SERIALIZE_MEMBER("lowPower", GraphicsSettings::lowPower)
SERIALIZE_END



#endif //VKRENDERER_CONFIGTYPES_H
