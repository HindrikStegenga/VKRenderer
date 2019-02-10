//
// Created by hindrik on 9-2-19.
//

#include "Matrix4x4f.h"

namespace Math {

    Matrix4x4f::Matrix4x4f(
            float a0, float a1, float a2, float a3,
            float b0, float b1, float b2, float b3,
            float c0, float c1, float c2, float c3,
            float d0, float d1, float d2, float d3)
            : data {
            a0, a1, a2, a3,
            b0, b1, b2, b3,
            c0, c1, c2, c3,
            d0, d1, d2, d3
    } {}

    Matrix4x4f::Matrix4x4f(const array<float, 16>& array)
    : data { array[0], array[1], array[2], array[3],
             array[4], array[5], array[6], array[7],
             array[8], array[9], array[10], array[11],
             array[12], array[13], array[14], array[15]
    } {
    }

    Matrix4x4f::Matrix4x4f(const Matrix3x3f &mat) 
    : data { mat[0], mat[1], mat[2],  0.0f,
             mat[3], mat[4], mat[5],  0.0f,
             mat[6], mat[7], mat[8],  0.0f,
               0.0f,   0.0f,    0.0f, 1.0f } {
    }
    
    Matrix4x4f::Matrix4x4f(const Vector4f& a, const Vector4f& b, const Vector4f& c, Vector4f d)
    : data{ a.x, a.y, a.z, a.w,
            b.x, b.y, b.z, b.w,
            c.x, c.y, c.z, c.w,
            d.x, d.y, d.z, d.w } {
    }

    float &Matrix4x4f::operator[](size_t index) {
        return data[index];
    }

    const float &Matrix4x4f::operator[](size_t index) const {
        return data[index];
    }

    Vector4f Matrix4x4f::getFirstRow() const {
        return Vector4f(data[0], data[1], data[2], data[3]);
    }

    Vector4f Matrix4x4f::getSecondRow() const {
        return Vector4f(data[4], data[5], data[6], data[7]);
    }

    Vector4f Matrix4x4f::getThirdRow() const {
        return Vector4f(data[8], data[9], data[10], data[11]);
    }

    Vector4f Matrix4x4f::getFourthRow() const {
        return Vector4f(data[12], data[13], data[14], data[15]);
    }

    void Matrix4x4f::setFirstRow(const Vector4f &row) {
        data[0] = row.x;
        data[1] = row.y;
        data[2] = row.z;
        data[3] = row.w;
    }

    void Matrix4x4f::setSecondRow(const Vector4f &row) {
        data[4] = row.x;
        data[5] = row.y;
        data[6] = row.z;
        data[7] = row.w;
    }

    void Matrix4x4f::setThirdRow(const Vector4f &row) {
        data[8] = row.x;
        data[9] = row.y;
        data[10] = row.z;
        data[11] = row.w;
    }

    void Matrix4x4f::setFourthRow(const Vector4f &row) {
        data[12] = row.x;
        data[13] = row.y;
        data[14] = row.z;
        data[15] = row.w;
    }

    Vector4f Matrix4x4f::getFirstColumn() const {
        return Vector4f(data[0], data[4], data[8], data[12]);
    }

    Vector4f Matrix4x4f::getSecondColumn() const {
        return Vector4f(data[1], data[5], data[9], data[13]);
    }

    Vector4f Matrix4x4f::getThirdColumn() const {
        return Vector4f(data[2], data[6], data[10], data[14]);
    }

    Vector4f Matrix4x4f::getFourthColumn() const {
        return Vector4f(data[3], data[7], data[11], data[15]);
    }

    void Matrix4x4f::setFirstColumn(const Vector4f &column) {
        data[0] = column.x;
        data[4] = column.y;
        data[8] = column.z;
        data[12] = column.w;
    }

    void Matrix4x4f::setSecondColumn(const Vector4f &column) {
        data[1] = column.x;
        data[5] = column.y;
        data[9] = column.z;
        data[13] = column.w;
    }

    void Matrix4x4f::setThirdColumn(const Vector4f &column) {
        data[2] = column.x;
        data[6] = column.y;
        data[10] = column.z;
        data[14] = column.w;
    }

    void Matrix4x4f::setFourthColumn(const Vector4f &column) {
        data[3] = column.x;
        data[7] = column.y;
        data[11] = column.z;
        data[15] = column.w;
    }

    array<float, 16> Matrix4x4f::getData() const {
        return { data[0], data[1], data[2], data[3],
                 data[4], data[5], data[6], data[7],
                 data[8], data[9], data[10], data[11],
                 data[12], data[13], data[14], data[15]
        };
    }

    void Matrix4x4f::setData(array<float, 16> dataSet) {
        std::copy(std::begin(dataSet), std::end(dataSet), std::begin(data));
    }

    float Matrix4x4f::element(size_t row, size_t column) {
        return data[row * 4 + column];
    }

    Matrix4x4f Matrix4x4f::identity() {
        return Matrix4x4f();
    }

    Matrix4x4f Matrix4x4f::transpose() const {
        return Matrix4x4f(
                data[0], data[4], data[8], data[12],
                data[1], data[5], data[9], data[13],
                data[2], data[6], data[10], data[14],
                data[3], data[7], data[11], data[15]
                );
    }
    
    Matrix4x4f add(const Matrix4x4f &lhs, float rhs) {
        return Matrix4x4f(
                lhs[0] + rhs, lhs[4] + rhs, lhs[8] + rhs, lhs[12] + rhs,
                lhs[1] + rhs, lhs[5] + rhs, lhs[9] + rhs, lhs[13] + rhs,
                lhs[2] + rhs, lhs[6] + rhs, lhs[10] + rhs, lhs[14] + rhs,
                lhs[3] + rhs, lhs[7] + rhs, lhs[11] + rhs, lhs[15] + rhs
                );
    }

    Matrix4x4f subtract(const Matrix4x4f &lhs, float rhs) {
        return Matrix4x4f(
                lhs[0] - rhs, lhs[4] - rhs, lhs[8] - rhs, lhs[12] - rhs,
                lhs[1] - rhs, lhs[5] - rhs, lhs[9] - rhs, lhs[13] - rhs,
                lhs[2] - rhs, lhs[6] - rhs, lhs[10] - rhs, lhs[14] - rhs,
                lhs[3] - rhs, lhs[7] - rhs, lhs[11] - rhs, lhs[15] - rhs
        );
    }

    Matrix4x4f multiply(const Matrix4x4f &lhs, float rhs) {
        return Matrix4x4f(
                lhs[0] * rhs, lhs[4] * rhs, lhs[8] * rhs, lhs[12] * rhs,
                lhs[1] * rhs, lhs[5] * rhs, lhs[9] * rhs, lhs[13] * rhs,
                lhs[2] * rhs, lhs[6] * rhs, lhs[10] * rhs, lhs[14] * rhs,
                lhs[3] * rhs, lhs[7] * rhs, lhs[11] * rhs, lhs[15] * rhs
        );
    }

    Matrix4x4f multiply(const Matrix4x4f &lhs, const Matrix4x4f &rhs) {
        return Matrix4x4f(
                lhs[0] * rhs[0] + lhs[1] * rhs[4] + lhs[2] * rhs[8] + lhs[3] * rhs[12],
                lhs[0] * rhs[1] + lhs[1] * rhs[5] + lhs[2] * rhs[9] + lhs[3] * rhs[13],
                lhs[0] * rhs[2] + lhs[1] * rhs[6] + lhs[2] * rhs[10] + lhs[3] * rhs[14],
                lhs[0] * rhs[3] + lhs[1] * rhs[7] + lhs[2] * rhs[11] + lhs[3] * rhs[15],

                lhs[4] * rhs[0] + lhs[5] * rhs[4] + lhs[6] * rhs[8] + lhs[7] * rhs[12],
                lhs[4] * rhs[1] + lhs[5] * rhs[5] + lhs[6] * rhs[9] + lhs[7] * rhs[13],
                lhs[4] * rhs[2] + lhs[5] * rhs[6] + lhs[6] * rhs[10] + lhs[7] * rhs[14],
                lhs[4] * rhs[3] + lhs[5] * rhs[7] + lhs[6] * rhs[11] + lhs[7] * rhs[15],

                lhs[8] * rhs[0] + lhs[9] * rhs[4] + lhs[10] * rhs[8] + lhs[11] * rhs[12],
                lhs[8] * rhs[1] + lhs[9] * rhs[5] + lhs[10] * rhs[9] + lhs[11] * rhs[13],
                lhs[8] * rhs[2] + lhs[9] * rhs[6] + lhs[10] * rhs[10] + lhs[11] * rhs[14],
                lhs[8] * rhs[3] + lhs[9] * rhs[7] + lhs[10] * rhs[11] + lhs[11] * rhs[15],

                lhs[12] * rhs[0] + lhs[13] * rhs[4] + lhs[14] * rhs[8] + lhs[15] * rhs[12],
                lhs[12] * rhs[1] + lhs[13] * rhs[5] + lhs[14] * rhs[9] + lhs[15] * rhs[13],
                lhs[12] * rhs[2] + lhs[13] * rhs[6] + lhs[14] * rhs[10] + lhs[15] * rhs[14],
                lhs[12] * rhs[3] + lhs[13] * rhs[7] + lhs[14] * rhs[11] + lhs[15] * rhs[15]
                );
    }

    Vector4f multiply(const Vector4f &lhs, const Matrix4x4f &rhs) {
        return Vector4f(
                lhs.x * rhs[0] + lhs.y * rhs[4] + lhs.z * rhs[8] + lhs.w * rhs[12],
                lhs.x * rhs[1] + lhs.y * rhs[5] + lhs.z * rhs[9] + lhs.w * rhs[13],
                lhs.x * rhs[2] + lhs.y * rhs[6] + lhs.z * rhs[10] + lhs.w * rhs[14],
                lhs.x * rhs[3] + lhs.y * rhs[7] + lhs.z * rhs[11] + lhs.w * rhs[15]
        );
    }
}

