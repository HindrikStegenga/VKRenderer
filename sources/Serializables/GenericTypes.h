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

namespace Serializable {

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
}

SERIALIZE_START(Serializable::Transform)
    SERIALIZE_MEMBER("position", Serializable::Transform::position),
    SERIALIZE_MEMBER("rotation", Serializable::Transform::rotation),
    SERIALIZE_MEMBER("scale", Serializable::Transform::scale)
SERIALIZE_END

SERIALIZE_START(Serializable::GameObject)
    SERIALIZE_MEMBER("name", Serializable::GameObject::name),
    SERIALIZE_MEMBER("isStatic", Serializable::GameObject::isStatic),
    SERIALIZE_MEMBER("transform", Serializable::GameObject::transform)
SERIALIZE_END

SERIALIZE_START(Serializable::Scene)
    SERIALIZE_MEMBER("name", Serializable::Scene::name),
    SERIALIZE_MEMBER("gameObjects", Serializable::Scene::gameObjects)
SERIALIZE_END


#endif //VKRENDERER_GENERICTYPES_H
