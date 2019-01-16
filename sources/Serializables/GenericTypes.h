//
// Created by Hindrik Stegenga on 2018-12-14.
//

#ifndef VKRENDERER_GENERICTYPES_H
#define VKRENDERER_GENERICTYPES_H

#include <MetaStuff/JsonCast.h>
#include <MetaStuff/Meta.h>
#include "SerializeMacro.h"

#include <string>
#include <cstdint>
#include "Vectors.h"

struct Transform {
    Vector3f position;
    Vector3f rotation;
    Vector3f scale;
};

struct GameObject {
    string name;
    bool isStatic;
    Transform transform;
};

struct Scene {
    string name;
    vector<GameObject> gameObjects;
};

SERIALIZE_START(Transform)
    SERIALIZE_MEMBER("position", Transform::position),
    SERIALIZE_MEMBER("rotation", Transform::rotation),
    SERIALIZE_MEMBER("scale", Transform::scale)
SERIALIZE_END

SERIALIZE_START(GameObject)
    SERIALIZE_MEMBER("name", GameObject::name),
    SERIALIZE_MEMBER("isStatic", GameObject::isStatic),
    SERIALIZE_MEMBER("transform", GameObject::transform)
SERIALIZE_END

SERIALIZE_START(Scene)
    SERIALIZE_MEMBER("name", Scene::name),
    SERIALIZE_MEMBER("gameObjects", Scene::gameObjects)
SERIALIZE_END


#endif //VKRENDERER_GENERICTYPES_H
