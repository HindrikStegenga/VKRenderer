//
// Created by hindrik on 9-2-19.
//

#ifndef VKRENDERER_MATRIX4X4F_H
#define VKRENDERER_MATRIX4X4F_H

#include <array>
#include "../MathSerialization.h"
#include "../Vectors/Vector4f.h"
#include "Matrix3x3f.h"

using std::array;

namespace Math {

    class Matrix4x4f final {
    private:
        float data[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                           0.0f, 1.0f, 0.0f, 0.0f,
                           0.0f, 0.0f, 1.0f, 0.0f,
                           0.0f, 0.0f, 0.0f, 1.0f };
        // row major
        // a0 a1 a2 a3 -> | 1 0 0 0 |
        // -----------    -----------
        // b0 b1 b2 b3 -> | 0 1 0 0 |
        // -----------    -----------
        // c0 c1 c2 c3 -> | 0 0 1 0 |
        // -----------    -----------
        // d0 d1 d2 d3 -> | 0 0 0 1 |
    public:
        Matrix4x4f() = default;
        ~Matrix4x4f() = default;

        Matrix4x4f(const Matrix4x4f&) = default;
        Matrix4x4f& operator=(const Matrix4x4f&) = default;

        explicit Matrix4x4f(const Matrix3x3f& mat);

        Matrix4x4f(float a0, float a1, float a2, float a3,
                   float b0, float b1, float b2, float b3,
                   float c0, float c1, float c2, float c3,
                   float d0, float d1, float d2, float d3);

        explicit Matrix4x4f(const array<float, 16>& array);
        Matrix4x4f(const Vector4f& a, const Vector4f& b, const Vector4f& c, Vector4f d);
    public:
        float& operator[](size_t index);
        const float& operator[](size_t index) const;

        Vector4f getFirstRow() const;
        Vector4f getSecondRow() const;
        Vector4f getThirdRow() const;
        Vector4f getFourthRow() const;
        void setFirstRow(const Vector4f& row);
        void setSecondRow(const Vector4f& row);
        void setThirdRow(const Vector4f& row);
        void setFourthRow(const Vector4f& row);

        Vector4f getFirstColumn() const;
        Vector4f getSecondColumn() const;
        Vector4f getThirdColumn() const;
        Vector4f getFourthColumn() const;
        void setFirstColumn(const Vector4f& column);
        void setSecondColumn(const Vector4f& column);
        void setThirdColumn(const Vector4f& column);
        void setFourthColumn(const Vector4f& column);

        array<float, 16> getData() const;
        void setData(array<float, 16> data);

        float element(size_t row, size_t column);
    public:
        static Matrix4x4f identity();
    public:
        Matrix4x4f transpose() const;
    };

    Matrix4x4f add(const Matrix4x4f& lhs, float rhs);
    Matrix4x4f subtract(const Matrix4x4f& lhs, float rhs);
    Matrix4x4f multiply(const Matrix4x4f& lhs, float rhs);
    Matrix4x4f multiply(const Matrix4x4f& lhs, const Matrix4x4f& rhs);
    Vector4f   multiply(const Vector4f& lhs, const Matrix4x4f& rhs);
    
}

SERIALIZE_START(Math::Matrix4x4f)
    SERIALIZE_GETSET("data", Math::Matrix4x4f::getData, Math::Matrix4x4f::setData)
SERIALIZE_END

#endif //VKRENDERER_MATRIX4X4F_H
