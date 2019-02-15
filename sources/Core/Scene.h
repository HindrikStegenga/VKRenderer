//
// Created by hindrik on 10-2-19.
//

#ifndef VKRENDERER_SCENE_H
#define VKRENDERER_SCENE_H

#include <vector>
#include <string>
#include "ECS/Entity.h"
#include "../DataStorage/StaticReusablePool.h"
#include "../DataStorage/LinearStaticReusablePool.h"

class Scene {
private:
    //For some reason not compiling in release mode?

    //StaticReusablePool<Entity> staticEntities;

    //LinearStaticReusablePool<Entity> staticEntities;
    //LinearStaticReusablePool<Entity> dynamicEntities;

public:
    Scene();
};


#endif //VKRENDERER_SCENE_H
