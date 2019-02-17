//
// Created by hindrik on 16-2-19.
//

#ifndef VKRENDERER_ENTITYMANAGER_H
#define VKRENDERER_ENTITYMANAGER_H

#include <vector>
#include <array>

#include "../../Data Structures/Handle.h"
#include "Entity.h"
#include "../../Data Structures/HandleVector/HandleVector.h"

DECLARE_HANDLE_16(Entity)

using std::vector;

class EntityManager final {
private:
    HandleVector<Entity> entities;
public:
    EntityManager();






};


#endif //VKRENDERER_ENTITYMANAGER_H
