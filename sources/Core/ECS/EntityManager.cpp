//
// Created by hindrik on 16-2-19.
//

#include "EntityManager.h"

EntityManager::EntityManager() {

    auto handle1 = entities.getItem(1);
    auto handle2 = entities.getItem(2);
    auto handle3 = entities.getItem(3);

    entities.returnItem(handle2);

    Entity& entity1 = entities[handle1];
    Entity& entity2 = entities[handle3];

}
