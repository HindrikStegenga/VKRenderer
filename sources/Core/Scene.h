//
// Created by hindriks on 7-4-19.
//

#ifndef VKRENDERER_SCENE_H
#define VKRENDERER_SCENE_H

#include <string>
#include <vector>
#include "ECS/Entity.h"

using std::string;
using std::vector;

class Scene final {
public:
    string name;
    vector<Entity> staticEntities;
    vector<Entity> dynamicEntities;
public:
    Scene() = default;
    ~Scene() = default;

    Scene(const Scene&) = delete;
    Scene(Scene&&) = default;

    Scene& operator=(const Scene&) = delete;
    Scene& operator=(Scene&&) = default;
public:
    explicit Scene(const string& fileName);

};

SERIALIZE_START(Scene)
    SERIALIZE_MEMBER("name", Scene::name),
    SERIALIZE_MEMBER("staticEntities", Scene::staticEntities),
    SERIALIZE_MEMBER("dynamicEntities", Scene::dynamicEntities)
SERIALIZE_END


#endif //VKRENDERER_SCENE_H
