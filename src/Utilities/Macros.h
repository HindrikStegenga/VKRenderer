//
// Created by Hindrik Stegenga on 31-10-17.
//

#ifndef VKRENDERER_MACROS_H
#define VKRENDERER_MACROS_H

#include "TypeTraits.h"

#define SAFE_POINTER_RELEASE(x) if((x) != nullptr) { delete (x); }

#define REGISTER_PARSE_TYPE(X) template <> struct TypeTraits<X> \
    { inline static const char* name() { return #X; } };

#endif //VKRENDERER_MACROS_H
