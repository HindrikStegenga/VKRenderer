//
// Created by Hindrik Stegenga on 2019-01-25.
//

#include <cmath>
#include "Vector3f.h"

using namespace std;
using Math::Vector3f;

Math::Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z){}

float Math::Vector3f::magnitude() const {
    return sqrt(x * x + y * y + z * z);
}

Math::Vector3f Math::Vector3f::negate() const {
    return Math::Vector3f(x * -1.0f, y * -1.0f, z * -1.0f);
}

Math::Vector3f Math::Vector3f::unit() const {
    float mag = magnitude();
    return Vector3f(x / mag, y / mag, z / mag);
}

Math::Vector3f Math::add(const Math::Vector3f &lhs, float rhs) {
    return Vector3f(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
}

Math::Vector3f Math::add(const Math::Vector3f &lhs, const Math::Vector3f &rhs) {
    return Math::Vector3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Math::Vector3f Math::subtract(const Math::Vector3f &lhs, float rhs) {
    return add(lhs, rhs * -1.0f);
}

Math::Vector3f Math::subtract(const Math::Vector3f &lhs, const Math::Vector3f &rhs) {
    return add(lhs, rhs.negate());
}

Math::Vector3f Math::multiply(const Math::Vector3f &lhs, float rhs) {
    return Vector3f(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

float Math::dot(const Math::Vector3f &lhs, const Math::Vector3f &rhs) {
    Vector3f lhsU = lhs.unit();
    Vector3f rhsU = rhs.unit();

    return (lhsU.x * rhsU.x) + (lhsU.y * rhsU.y) + (lhsU.z * rhsU.z);
}

Math::Vector3f Math::cross(const Math::Vector3f &lhs, const Math::Vector3f &rhs) {
    return Vector3f(
            lhs.y*rhs.z - lhs.z*rhs.y,
            lhs.z*rhs.x - lhs.x*rhs.z,
            lhs.x*rhs.y - lhs.y*rhs.x
            );
}
