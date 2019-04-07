//
// Created by hindrik on 7-2-19.
//

#ifndef VKRENDERER_ENTITY_H
#define VKRENDERER_ENTITY_H

#include <cstdint>
#include <vector>
#include "Transform.h"

class Entity final {
private:
    uint32_t  entityID  = 0;
public:
    Transform transform = {};
public:
    Entity() = default;
    ~Entity() = default;

    //TODO: Fix copy constructor mess.

    Entity(const Entity&) = default;
    //Entity(Entity&&) noexcept = default;

    Entity& operator=(const Entity&) = default;
    //Entity& operator=(Entity&&) noexcept = default;

    Entity(uint32_t id, Transform transform);
public:
    uint32_t getID() const;
    void setID(uint32_t id);
};

SERIALIZE_START(Entity)
    SERIALIZE_GETSET("id", Entity::getID, Entity::setID),
    SERIALIZE_MEMBER("transform", Entity::transform)
SERIALIZE_END



#endif //VKRENDERER_ENTITY_H
