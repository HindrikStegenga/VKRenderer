//
// Created by Hindrik Stegenga on 2019-01-25.
//

#ifndef VKRENDERER_VECTOR4F_H
#define VKRENDERER_VECTOR4F_H

#include "../MathSerialization.h"
#include "Vector2f.h"
#include "Vector3f.h"

namespace Math {

    struct Vector4f final {
    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;
    public:
        Vector4f() = default;
        ~Vector4f() = default;

        Vector4f(float x, float y, float z, float w);

        Vector4f(const Vector3f& vec, float c);
        Vector4f(const Vector2f& vec1, const Vector2f& vec2);

        Vector4f(const Vector4f&) = default;
        Vector4f& operator=(const Vector4f&) = default;
    public:
        float magnitude() const;
        Vector4f negate() const;
        Vector4f unit() const;
    };

    Vector4f add(const Vector4f& lhs, float rhs);
    Vector4f subtract(const Vector4f& lhs, float rhs);
    Vector4f multiply(const Vector4f& lhs, float rhs);

    Vector4f add(const Vector4f& lhs, const Vector4f& rhs);
    Vector4f subtract(const Vector4f& lhs, const Vector4f& rhs);
    float    dot(const Vector4f& lhs, const Vector4f& rhs);
}

SERIALIZE_START(Math::Vector4f)
    SERIALIZE_MEMBER("x", Math::Vector4f::x),
    SERIALIZE_MEMBER("y", Math::Vector4f::y),
    SERIALIZE_MEMBER("z", Math::Vector4f::z),
    SERIALIZE_MEMBER("w", Math::Vector4f::w)
SERIALIZE_END

#endif //VKRENDERER_VECTOR4F_H
