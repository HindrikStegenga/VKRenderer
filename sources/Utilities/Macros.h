//
// Created by Hindrik Stegenga on 31-10-17.
//

#ifndef VKRENDERER_MACROS_H
#define VKRENDERER_MACROS_H

#include "TypeTraits.h"

#define SAFE_POINTER_RELEASE(x) if((x) != nullptr) { delete (x); }

#define REGISTER_PARSE_TYPE(X) template <> struct TypeTraits<X> \
    { inline static const char* name() { return #X; } };

#define PATH_RENDERMODE_JSON "config/rendermodes/"
#define PATH_GRAPHICS_PIPELINE_LAYOUT_JSON "config/graphics_pipeline_layouts/"
#define PATH_VERTEX_LAYOUT_JSON "config/vertex_layouts/"


#endif //VKRENDERER_MACROS_H
