//
// Created by Hindrik Stegenga on 2019-01-25.
//

#ifndef VKRENDERER_VECTOR3F_H
#define VKRENDERER_VECTOR3F_H

#include "../MathSerialization.h"

namespace Math {

    struct Vector3f final {
    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    public:
        Vector3f() = default;
        ~Vector3f() = default;

        Vector3f(float x, float y, float z);

        Vector3f(const Vector3f&) = default;

        Vector3f& operator=(const Vector3f&) = default;
    public:
        float magnitude() const;
        Vector3f negate() const;
        Vector3f unit() const;
    };

    Vector3f add(const Vector3f& lhs, float rhs);
    Vector3f subtract(const Vector3f& lhs, float rhs);
    Vector3f multiply(const Vector3f& lhs, float rhs);

    Vector3f add(const Vector3f& lhs, const Vector3f& rhs);
    Vector3f subtract(const Vector3f& lhs, const Vector3f& rhs);
    float    dot(const Vector3f& lhs, const Vector3f& rhs);
    Vector3f cross(const Vector3f& lhs, const Vector3f& rhs);
}

SERIALIZE_START(Math::Vector3f)
    SERIALIZE_MEMBER("x", Math::Vector3f::x),
    SERIALIZE_MEMBER("y", Math::Vector3f::y),
    SERIALIZE_MEMBER("z", Math::Vector3f::z)
SERIALIZE_END

#endif //VKRENDERER_VECTOR3F_H
