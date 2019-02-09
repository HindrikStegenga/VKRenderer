//
// Created by Hindrik Stegenga on 2019-01-25.
//

#ifndef VKRENDERER_VECTOR2F_H
#define VKRENDERER_VECTOR2F_H

#include "../MathSerialization.h"

namespace Math {

    struct Vector2f {
    public:
        float x = 0.0f;
        float y = 0.0f;
    public:
        Vector2f() = default;
        ~Vector2f() = default;

        Vector2f(float x, float y);

        Vector2f(const Vector2f&) = default;

        Vector2f& operator=(const Vector2f&) = default;
    public:
        float magnitude() const;
        Vector2f negate() const;
        Vector2f unit() const;
    };

    Vector2f add(const Vector2f& lhs, float rhs);
    Vector2f subtract(const Vector2f& lhs, float rhs);
    Vector2f multiply(const Vector2f& lhs, float rhs);

    Vector2f add(const Vector2f& lhs, const Vector2f& rhs);
    Vector2f subtract(const Vector2f& lhs, const Vector2f& rhs);
    float    dot(const Vector2f& lhs, const Vector2f& rhs);

}

using Math::Vector2f;

SERIALIZE_START(Vector2f)
    SERIALIZE_MEMBER("x", Vector2f::x),
    SERIALIZE_MEMBER("y", Vector2f::y)
SERIALIZE_END

#endif //VKRENDERER_VECTOR2F_H
