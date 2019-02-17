//
// Created by hindrik on 7-2-19.
//

#ifndef VKRENDERER_ENTITY_H
#define VKRENDERER_ENTITY_H

#include <cstdint>
#include "../Transform.h"
#include "../../Data Structures/Handle.h"


class Entity {
private:
    int id;
    Transform transform;
    bool isStatic = false;
public:
    Entity(int id) : id(id) {}

    template<typename ComponentType, typename ...Args>
    Handle<ComponentType, uint16_t> addComponent(Args... args);

    template<typename ComponentType>
    void removeComponent(Handle<ComponentType, uint16_t> handle);
};

template<typename ComponentType, typename... Args>
Handle<ComponentType, uint16_t> Entity::addComponent(Args... args) {
    return Handle<ComponentType, uint16_t>();
}

template<typename ComponentType>
void Entity::removeComponent(Handle<ComponentType, uint16_t> handle) {

}


#endif //VKRENDERER_ENTITY_H
