//
// Created by hindrik on 9-2-19.
//

#include <cmath>
#include "Matrix2x2f.h"
#include "../../Utilities/Logger.h"

using namespace std;

namespace Math {

    Matrix2x2f::Matrix2x2f(float a0, float a1, float b0, float b1) : data { a0,a1,b0,b1 } {}

    Matrix2x2f::Matrix2x2f(Vector2f a, Vector2f b) : data { a.x, a.y, b.x, b.y } {}

    Matrix2x2f::Matrix2x2f(array<float, 4> array) : data { array[0], array[1], array[2], array[3] } {}

    float& Matrix2x2f::operator[](const size_t index) {
        return data[index];
    }

    const float &Matrix2x2f::operator[](size_t index) const {
        return data[index];
    }

    Vector2f Matrix2x2f::getFirstRow() const {
        return Vector2f(data[0], data[1]);
    }

    Vector2f Matrix2x2f::getSecondRow() const {
        return Vector2f(data[2], data[3]);
    }

    void Matrix2x2f::setFirstRow(Vector2f row) {
        data[0] = row.x;
        data[1] = row.y;
    }

    void Matrix2x2f::setSecondRow(Vector2f row) {
        data[2] = row.x;
        data[3] = row.y;
    }

    Vector2f Matrix2x2f::getFirstColumn() const {
        return Vector2f(data[0], data[2]);
    }

    Vector2f Matrix2x2f::getSecondColumn() const {
        return Vector2f(data[1], data[3]);
    }

    void Matrix2x2f::setFirstColumn(Vector2f column) {
        data[0] = column.x;
        data[2] = column.y;
    }

    void Matrix2x2f::setSecondColumn(Vector2f column) {
        data[1] = column.x;
        data[3] = column.y;
    }

    array<float, 4> Matrix2x2f::getData() const {
        return { data[0], data[1], data[2], data[3] };
    }

    void Matrix2x2f::setData(array<float, 4> dataSet) {
        std::copy(std::begin(dataSet), std::end(dataSet), std::begin(data));
    }

    float Matrix2x2f::element(size_t row, size_t column) {
        return data[row * 2 + column];
    }

    Matrix2x2f Matrix2x2f::identity() {
        return Matrix2x2f();
    }

    Matrix2x2f Matrix2x2f::transpose() const {
        return Matrix2x2f(data[0], data[2], data[1], data[3]);
    }

    Matrix2x2f add(const Matrix2x2f& lhs, float rhs) {
        return Matrix2x2f(lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs, lhs[3] + rhs);
    }

    Matrix2x2f subtract(const Matrix2x2f &lhs, float rhs) {
        return Matrix2x2f(lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs, lhs[3] - rhs);
    }

    Matrix2x2f multiply(const Matrix2x2f &lhs, float rhs) {
        return Matrix2x2f(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs);
    }

    Matrix2x2f multiply(const Matrix2x2f& lhs, const Matrix2x2f& rhs) {
        return Matrix2x2f(
                lhs[0] * rhs[0] + lhs[1] * rhs[2], //a0 * c0 + a1 * d0
                lhs[0] * rhs[1] + lhs[1] * rhs[3], //a0 * c1 + a1 * d1
                lhs[2] * rhs[0] + lhs[3] * rhs[2], //b0 * c0 + b1 * d0
                lhs[2] * rhs[1] + lhs[3] * rhs[3]  //b0 * c1 + b1 * d1
                );
    }

    Vector2f multiply(const Vector2f &lhs, const Matrix2x2f &rhs) {
        return Vector2f(
                lhs.x * rhs[0] + lhs.y * rhs[2],
                lhs.x * rhs[1] + lhs.y * rhs[3]
                );
    }
}
