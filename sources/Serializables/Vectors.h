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

SERIALIZE_START(Vector2f)
    SERIALIZE_MEMBER("x", Vector2f::x),
    SERIALIZE_MEMBER("y", Vector2f::y)
SERIALIZE_END

SERIALIZE_START(Vector3f)
    SERIALIZE_MEMBER("x", Vector3f::x),
    SERIALIZE_MEMBER("y", Vector3f::y),
    SERIALIZE_MEMBER("z", Vector3f::z)
SERIALIZE_END

SERIALIZE_START(Vector4f)
    SERIALIZE_MEMBER("x", Vector4f::x),
    SERIALIZE_MEMBER("y", Vector4f::y),
    SERIALIZE_MEMBER("z", Vector4f::z),
    SERIALIZE_MEMBER("w", Vector4f::w)
SERIALIZE_END

#endif //VKRENDERER_GENERICTYPES_H
