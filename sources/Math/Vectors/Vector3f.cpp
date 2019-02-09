//
// Created by Hindrik Stegenga on 2019-01-25.
//

#include <cmath>
#include "Vector3f.h"

using namespace std;

namespace Math {

    Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z){}

    float Vector3f::magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vector3f Vector3f::negate() const {
        return Vector3f(
                x * -1.0f,
                y * -1.0f,
                z * -1.0f
                );
    }

    Vector3f Vector3f::unit() const {
        float mag = magnitude();
        return Vector3f(x / mag, y / mag, z / mag);
    }

    Vector3f add(const Vector3f &lhs, float rhs) {
        return Vector3f(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
    }

    Vector3f add(const Vector3f &lhs, const Vector3f &rhs) {
        return Vector3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    Vector3f subtract(const Vector3f &lhs, float rhs) {
        return add(lhs, rhs * -1.0f);
    }

    Vector3f subtract(const Vector3f &lhs, const Vector3f &rhs) {
        return add(lhs, rhs.negate());
    }

    Vector3f multiply(const Vector3f &lhs, float rhs) {
        return Vector3f(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }

    float dot(const Vector3f &lhs, const Vector3f &rhs) {
        Vector3f lhsU = lhs.unit();
        Vector3f rhsU = rhs.unit();

        return (lhsU.x * rhsU.x) + (lhsU.y * rhsU.y) + (lhsU.z * rhsU.z);
    }

    Vector3f cross(const Vector3f &lhs, const Vector3f &rhs) {
        return Vector3f(
                lhs.y*rhs.z - lhs.z*rhs.y,
                lhs.z*rhs.x - lhs.x*rhs.z,
                lhs.x*rhs.y - lhs.y*rhs.x
        );
    }

}
