//
// Created by hindrik on 9-2-19.
//

#ifndef VKRENDERER_MATRIX3X3F_H
#define VKRENDERER_MATRIX3X3F_H

#include <array>
#include "../MathSerialization.h"
#include "../Vectors/Vector3f.h"

using std::array;

namespace Math {

    class Matrix3x3f final {
    private:
        float data[9] = { 1.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f,
                          0.0f, 0.0f, 1.0f };
        // row major
        // a0 a1 a2 -> | 1 0 0 |
        // --------    ---------
        // b0 b1 b2 -> | 0 1 0 |
        // --------    ---------
        // c0 c1 c2 -> | 0 0 1 |
    public:
        Matrix3x3f() = default;
        ~Matrix3x3f() = default;

        Matrix3x3f(const Matrix3x3f&) = default;
        Matrix3x3f& operator=(const Matrix3x3f&) = default;

        Matrix3x3f(float a0, float a1, float a2,
                   float b0, float b1, float b2,
                   float c0, float c1, float c2);

        explicit Matrix3x3f(array<float, 9> array);
        Matrix3x3f(Vector3f a, Vector3f b, Vector3f c);
    public:
        float& operator[](size_t index);
        const float& operator[](size_t index) const;

        Vector3f getFirstRow() const;
        Vector3f getSecondRow() const;
        Vector3f getThirdRow() const;
        void setFirstRow(const Vector3f& row);
        void setSecondRow(const Vector3f& row);
        void setThirdRow(const Vector3f& row);

        Vector3f getFirstColumn() const;
        Vector3f getSecondColumn() const;
        Vector3f getThirdColumn() const;
        void setFirstColumn(const Vector3f& column);
        void setSecondColumn(const Vector3f& column);
        void setThirdColumn(const Vector3f& column);

        array<float, 9> getData() const;
        void setData(array<float, 9> data);

        float element(size_t row, size_t column);
    public:
        static Matrix3x3f identity();
    public:
        Matrix3x3f transpose() const;
    };

    Matrix3x3f add(const Matrix3x3f& lhs, float rhs);
    Matrix3x3f subtract(const Matrix3x3f& lhs, float rhs);
    Matrix3x3f multiply(const Matrix3x3f& lhs, float rhs);
    Matrix3x3f multiply(const Matrix3x3f& lhs, const Matrix3x3f& rhs);
    Vector3f   multiply(const Vector3f& lhs, const Matrix3x3f& rhs);
}

SERIALIZE_START(Math::Matrix3x3f)
    SERIALIZE_GETSET("data", Math::Matrix3x3f::getData, Math::Matrix3x3f::setData)
SERIALIZE_END

#endif //VKRENDERER_MATRIX3X3F_H
