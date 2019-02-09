//
// Created by Hindrik Stegenga on 2019-01-25.
//

#ifndef VKRENDERER_VECTOR4F_H
#define VKRENDERER_VECTOR4F_H

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


#endif //VKRENDERER_VECTOR4F_H
