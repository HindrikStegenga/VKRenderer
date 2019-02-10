//
// Created by hindrik on 9-2-19.
//

#include "Matrix3x3f.h"

namespace Math {

    Matrix3x3f::Matrix3x3f(
            float a0, float a1, float a2,
            float b0, float b1, float b2,
            float c0, float c1, float c2
    ) : data{
        a0, a1, a2,
        b0, b1, b2,
        c0, c1, c2
    } {}

    Matrix3x3f::Matrix3x3f(const array<float, 9>& array)
        : data { array[0], array[1], array[2],
                 array[3], array[4], array[5],
                 array[6], array[7], array[8]} {
    }

    Matrix3x3f::Matrix3x3f(const Matrix2x2f &mat) : data { mat[0], mat[1], 0.0f,
                                                           mat[2], mat[3], 0.0f,
                                                           0.0f,     0.0f, 1.0f } {
    }

    Matrix3x3f::Matrix3x3f(const Vector3f& a, const Vector3f& b, const Vector3f& c)
        : data { a.x, a.y, a.z,
                 b.x, b.y, b.z,
                 c.x, c.y, c.z } {
    }

    float &Matrix3x3f::operator[](size_t index) {
        return data[index];
    }

    const float &Matrix3x3f::operator[](size_t index) const {
        return data[index];
    }

    Vector3f Matrix3x3f::getFirstRow() const {
        return Vector3f(data[0], data[1], data[2]);
    }

    Vector3f Matrix3x3f::getSecondRow() const {
        return Vector3f(data[3], data[4], data[5]);
    }

    Vector3f Matrix3x3f::getThirdRow() const {
        return Vector3f(data[6], data[7], data[8]);
    }

    void Matrix3x3f::setFirstRow(const Vector3f& row) {
        data[0] = row.x;
        data[1] = row.y;
        data[2] = row.z;
    }

    void Matrix3x3f::setSecondRow(const Vector3f& row) {
        data[3] = row.x;
        data[4] = row.y;
        data[5] = row.z;
    }

    void Matrix3x3f::setThirdRow(const Vector3f& row) {
        data[6] = row.x;
        data[7] = row.y;
        data[8] = row.z;
    }

    Vector3f Matrix3x3f::getFirstColumn() const {
        return Vector3f(data[0], data[3], data[6]);
    }

    Vector3f Matrix3x3f::getSecondColumn() const {
        return Vector3f(data[1], data[4], data[7]);
    }

    Vector3f Matrix3x3f::getThirdColumn() const {
        return Vector3f(data[2], data[5], data[8]);
    }

    void Matrix3x3f::setFirstColumn(const Vector3f &column) {
        data[0] = column.x;
        data[3] = column.y;
        data[6] = column.z;
    }

    void Matrix3x3f::setSecondColumn(const Vector3f &column) {
        data[1] = column.x;
        data[4] = column.y;
        data[7] = column.z;
    }

    void Matrix3x3f::setThirdColumn(const Vector3f &column) {
        data[2] = column.x;
        data[5] = column.y;
        data[8] = column.z;
    }

    array<float, 9> Matrix3x3f::getData() const {
        return { data[0], data[1], data[2],
                 data[3], data[4], data[5],
                 data[6], data[7], data[8]
        };
    }

    void Matrix3x3f::setData(array<float, 9> dataSet) {
        std::copy(std::begin(dataSet), std::end(dataSet), std::begin(data));
    }

    float Matrix3x3f::element(size_t row, size_t column) {
        return data[row * 3 + column];
    }

    Matrix3x3f Matrix3x3f::identity() {
        return Matrix3x3f();
    }

    Matrix3x3f Matrix3x3f::transpose() const {
        return Matrix3x3f(
                data[0], data[3], data[6],
                data[1], data[4], data[7],
                data[2], data[5], data[8]
                );
    }

    Matrix3x3f add(const Matrix3x3f &lhs, float rhs) {
        return Matrix3x3f(
                lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs,
                lhs[3] + rhs, lhs[4] + rhs, lhs[5] + rhs,
                lhs[6] + rhs, lhs[7] + rhs, lhs[8] + rhs
                );
    }

    Matrix3x3f subtract(const Matrix3x3f &lhs, float rhs) {
        return Matrix3x3f(
                lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs,
                lhs[3] - rhs, lhs[4] - rhs, lhs[5] - rhs,
                lhs[6] - rhs, lhs[7] - rhs, lhs[8] - rhs
        );
    }

    Matrix3x3f multiply(const Matrix3x3f &lhs, float rhs) {
        return Matrix3x3f(
                lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs,
                lhs[3] * rhs, lhs[4] * rhs, lhs[5] * rhs,
                lhs[6] * rhs, lhs[7] * rhs, lhs[8] * rhs
        );
    }

    Matrix3x3f multiply(const Matrix3x3f &lhs, const Matrix3x3f &rhs) {
        return Matrix3x3f(
                lhs[0] * rhs[0] + lhs[1] * rhs[3] + lhs[2] * rhs[6],
                lhs[0] * rhs[1] + lhs[1] * rhs[4] + lhs[2] * rhs[7],
                lhs[0] * rhs[2] + lhs[1] * rhs[5] + lhs[2] * rhs[8],

                lhs[3] * rhs[0] + lhs[4] * rhs[3] + lhs[5] * rhs[6],
                lhs[3] * rhs[1] + lhs[4] * rhs[4] + lhs[5] * rhs[7],
                lhs[3] * rhs[2] + lhs[4] * rhs[5] + lhs[5] * rhs[8],

                lhs[6] * rhs[0] + lhs[7] * rhs[3] + lhs[8] * rhs[6],
                lhs[6] * rhs[1] + lhs[7] * rhs[4] + lhs[8] * rhs[7],
                lhs[6] * rhs[2] + lhs[7] * rhs[5] + lhs[8] * rhs[8]
                );
    }

    Vector3f multiply(const Vector3f &lhs,const Matrix3x3f &rhs) {
        return Vector3f(
                lhs.x * rhs[0] + lhs.y * rhs[3] + lhs.z * rhs[6],
                lhs.x * rhs[1] + lhs.y * rhs[4] + lhs.z * rhs[7],
                lhs.x * rhs[2] + lhs.y * rhs[5] + lhs.z * rhs[8]

        );
    }
}
