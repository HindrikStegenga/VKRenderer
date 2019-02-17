//
// Created by hindrik on 10-2-19.
//

#ifndef VKRENDERER_SCENE_H
#define VKRENDERER_SCENE_H

#include <vector>
#include <string>
#include "ECS/Entity.h"
#include "ECS/EntityManager.h"

class Scene {
private:
    EntityManager entityManager;
public:
    Scene();
};


#endif //VKRENDERER_SCENE_H
