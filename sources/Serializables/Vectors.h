//
// Created by Hindrik Stegenga on 2018-12-14.
//

#ifndef VKRENDERER_VECTORS_H
#define VKRENDERER_VECTORS_H

#include <MetaStuff/JsonCast.h>
#include <MetaStuff/Meta.h>
#include "SerializeMacro.h"

#include <string>
#include <cstdint>

using std::string;
using std::vector;

namespace Serializable {

    struct Vector2f {
        float x;
        float y;
    };

    struct Vector3f {
        float x;
        float y;
        float z;
    };

    struct Vector4f {
        float x;
        float y;
        float z;
        float w;
    };
}

SERIALIZE_START(Serializable::Vector2f)
    SERIALIZE_MEMBER("x", Serializable::Vector2f::x),
    SERIALIZE_MEMBER("y", Serializable::Vector2f::y)
SERIALIZE_END

SERIALIZE_START(Serializable::Vector3f)
    SERIALIZE_MEMBER("x", Serializable::Vector3f::x),
    SERIALIZE_MEMBER("y", Serializable::Vector3f::y),
    SERIALIZE_MEMBER("z", Serializable::Vector3f::z)
SERIALIZE_END

SERIALIZE_START(Serializable::Vector4f)
    SERIALIZE_MEMBER("x", Serializable::Vector4f::x),
    SERIALIZE_MEMBER("y", Serializable::Vector4f::y),
    SERIALIZE_MEMBER("z", Serializable::Vector4f::z),
    SERIALIZE_MEMBER("w", Serializable::Vector4f::w)
SERIALIZE_END

#endif //VKRENDERER_GENERICTYPES_H
