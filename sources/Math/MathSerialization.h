//
// Created by hindrik on 9-2-19.
//

#ifndef VKRENDERER_MATHSERIALIZATION_H
#define VKRENDERER_MATHSERIALIZATION_H

#include "../Serializables/SerializeMacro.h"

namespace Math {

    template <typename T>
    void from_json(const json& j, T& obj) {
        meta::deserialize(obj, j);
    }

    template <typename T>
    void to_json(json & j, const T& obj) {
        j = meta::serialize(obj);
    }

}

#endif //VKRENDERER_MATHSERIALIZATION_H
