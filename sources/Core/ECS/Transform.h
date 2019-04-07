//
// Created by Hindrik Stegenga on 2018-12-14.
//

#ifndef VKRENDERER_TRANSFORM_H
#define VKRENDERER_TRANSFORM_H


#include "../../Math/Vectors/Vector3f.h"

using namespace Math;

class Transform final {
public:
    Vector3f position;
    Vector3f rotation;
    Vector3f scale;
public:
    Transform() = default;
    ~Transform() = default;

    Transform(const Transform&) = default;
    Transform& operator=(const Transform&) = default;
public:



};

SERIALIZE_START(Transform)
    SERIALIZE_MEMBER("position", Transform::position),
    SERIALIZE_MEMBER("rotation", Transform::rotation),
    SERIALIZE_MEMBER("scale", Transform::scale)
SERIALIZE_END


#endif //VKRENDERER_TRANSFORM_H
