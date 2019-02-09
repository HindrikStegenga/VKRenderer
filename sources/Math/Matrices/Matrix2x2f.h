//
// Created by hindrik on 9-2-19.
//

#ifndef VKRENDERER_MATRIX2X2F_H
#define VKRENDERER_MATRIX2X2F_H

#include <array>
#include "../MathSerialization.h"
#include "../Vectors/Vector2f.h"

using std::array;

namespace Math {

    class Matrix2x2f final {
    private:
        float data[4] = { 1.0f, 0.0f,
                          0.0f, 1.0f };
        // row major
        // a0 a1 -> | 1 0 |
        // -----    -------
        // b0 b1 -> | 0 1 |

    public:
        Matrix2x2f() = default;
        ~Matrix2x2f() = default;

        Matrix2x2f(const Matrix2x2f&) = default;
        Matrix2x2f& operator=(const Matrix2x2f&) = default;

        Matrix2x2f(float a0, float a1, float b0, float b1);

        explicit Matrix2x2f(array<float, 4> array);
        Matrix2x2f(Vector2f a, Vector2f b);
    public:
        float& operator[](size_t index);
        const float& operator[](size_t index) const;

        Vector2f getFirstRow() const;
        Vector2f getSecondRow() const;
        void setFirstRow(Vector2f row);
        void setSecondRow(Vector2f row);

        array<float, 4> getData() const;
        void setData(array<float, 4> data);

        float element(size_t row, size_t column);
    public:
        static Matrix2x2f identity();
    public:
        Matrix2x2f transpose() const;
    };

    Matrix2x2f add(const Matrix2x2f& lhs, float rhs);
    Matrix2x2f subtract(const Matrix2x2f& lhs, float rhs);
    Matrix2x2f multiply(const Matrix2x2f& lhs, float rhs);
    Matrix2x2f multiply(const Matrix2x2f& lhs, const Matrix2x2f& rhs);
    Vector2f   multiply(const Vector2f& lhs, const Matrix2x2f& rhs);
}

SERIALIZE_START(Math::Matrix2x2f)
    SERIALIZE_GETSET("data", Math::Matrix2x2f::getData, Math::Matrix2x2f::setData)
SERIALIZE_END


#endif //VKRENDERER_MATRIX2X2F_H
