//
// Created by Hindrik Stegenga on 2019-01-25.
//

#include "Vector4f.h"

Math::Vector4f::Vector4f(float x, float y, float z, float w) : x(x),y(y),z(z),w(w) {}

float Math::Vector4f::magnitude() const {
    return 0;
}

Math::Vector4f Math::Vector4f::negate() const {
    return Math::Vector4f();
}

Math::Vector4f Math::Vector4f::unit() const {
    return Math::Vector4f();
}

