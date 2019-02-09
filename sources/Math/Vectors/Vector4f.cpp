//
// Created by Hindrik Stegenga on 2019-01-25.
//

#include <cmath>
#include "Vector4f.h"

using namespace std;

namespace Math {

    Vector4f::Vector4f(float x, float y, float z, float w) : x(x),y(y),z(z),w(w) {}

    float Vector4f::magnitude() const {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    Vector4f Vector4f::negate() const {
        return Vector4f(
                x * -1.0f,
                y * -1.0f,
                z * -1.0f,
                w * -1.0f
        );
    }

    Vector4f Vector4f::unit() const {
        float mag = magnitude();
        return Vector4f(x / mag, y / mag, z / mag, w / mag);
    }

    Vector4f add(const Vector4f &lhs, float rhs) {
        return Vector4f(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs, lhs.w + rhs);
    }

    Vector4f add(const Vector4f &lhs, const Vector4f &rhs) {
        return Vector4f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
    }

    Vector4f subtract(const Vector4f &lhs, float rhs) {
        return add(lhs, rhs * -1.0f);
    }

    Vector4f subtract(const Vector4f &lhs, const Vector4f &rhs) {
        return add(lhs, rhs.negate());
    }

    Vector4f multiply(const Vector4f &lhs, float rhs) {
        return Vector4f(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
    }

    float dot(const Vector4f &lhs, const Vector4f &rhs) {
        Vector4f lhsU = lhs.unit();
        Vector4f rhsU = rhs.unit();

        return (lhsU.x * rhsU.x) + (lhsU.y * rhsU.y) + (lhsU.z * rhsU.z) + (lhsU.w * rhsU.w);
    }
}