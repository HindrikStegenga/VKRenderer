//
// Created by hindrik on 7-2-19.
//

#include "Entity.h"

Entity::Entity(uint32_t id, Transform transform) : entityID(id), transform(transform) {

}

uint32_t Entity::getID() const {
    return entityID;
}

void Entity::setID(uint32_t id) {
    entityID = id;
}
