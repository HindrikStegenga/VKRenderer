//
// Created by hindrik on 7-2-19.
//

#ifndef VKRENDERER_COMPONENT_H
#define VKRENDERER_COMPONENT_H

#include "TypeID.h"

template<typename T>
class Component {
public:
    Component() = default;
    virtual ~Component() = 0;

    Component(const Component&) = default;
    Component(Component&&) noexcept = default;

    Component& operator=(const Component&) = default;
    Component& operator=(Component&&) noexcept = default;
public:
    static const uint64_t getTypeID() {
        return TypeID::get<T>();
    }
};

#endif //VKRENDERER_COMPONENT_H
