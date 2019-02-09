//
// Created by Hindrik Stegenga on 2019-01-25.
//

#include <cmath>
#include "Vector2f.h"

using namespace std;

namespace Math {

    Vector2f::Vector2f(float x, float y) : x(x), y(y) {}

    float Vector2f::magnitude() const {
        return sqrt(x * x + y * y);
    }

    Vector2f Vector2f::negate() const {
        return Vector2f(x * -1.0f, y * -1.0f);
    }

    Vector2f Vector2f::unit() const {
        float mag = magnitude();
        return Vector2f(x / mag, y / mag);
    }

    Vector2f add(const Vector2f &lhs, float rhs) {
        return Vector2f(lhs.x + rhs, lhs.y + rhs);
    }

    Vector2f add(const Vector2f &lhs, const Vector2f &rhs) {
        return Vector2f(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    Vector2f subtract(const Vector2f &lhs, float rhs) {
        return add(lhs, rhs * -1.0f);
    }

    Vector2f subtract(const Vector2f &lhs, const Vector2f &rhs) {
        return add(lhs, rhs.negate());
    }

    Vector2f multiply(const Vector2f &lhs, float rhs) {
        return Vector2f(lhs.x * rhs, lhs.y * rhs);
    }

    float dot(const Vector2f &lhs, const Vector2f &rhs) {
        Vector2f lhsU = lhs.unit();
        Vector2f rhsU = rhs.unit();

        return (lhsU.x * rhsU.x) + (lhsU.y * rhsU.y);
    }
}




