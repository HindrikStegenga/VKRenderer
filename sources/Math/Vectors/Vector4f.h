//
// Created by Hindrik Stegenga on 2019-01-25.
//

#ifndef VKRENDERER_VECTOR4F_H
#define VKRENDERER_VECTOR4F_H

#include "../MathSerialization.h"

namespace Math {

    struct Vector4f {
    public:
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;
    public:
        Vector4f() = default;
        ~Vector4f() = default;

        Vector4f(float x, float y, float z, float w);

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

using Math::Vector4f;

SERIALIZE_START(Vector4f)
    SERIALIZE_MEMBER("x", Vector4f::x),
    SERIALIZE_MEMBER("y", Vector4f::y),
    SERIALIZE_MEMBER("z", Vector4f::z),
    SERIALIZE_MEMBER("w", Vector4f::w)
SERIALIZE_END

#endif //VKRENDERER_VECTOR4F_H
