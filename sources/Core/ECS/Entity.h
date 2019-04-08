//
// Created by hindrik on 7-2-19.
//

#ifndef VKRENDERER_ENTITY_H
#define VKRENDERER_ENTITY_H

#include <cstdint>
#include <vector>
#include <string>
#include "Transform.h"

using std::string;

class Entity final {
private:
    string name = "";
public:
    Transform transform = {};
private:
    Entity() = default;
public:
    ~Entity() = default;
    Entity(const string& name, Transform transform);

    Entity(const Entity&) = delete;
    Entity(Entity&&) noexcept = default;

    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) noexcept = default;


    SERIALIZE_FRIEND(meta, Entity)
};

SERIALIZE_START(Entity)
    SERIALIZE_MEMBER("name", Entity::name),
    SERIALIZE_MEMBER("transform", Entity::transform)
SERIALIZE_END



#endif //VKRENDERER_ENTITY_H
