//
// Created by Hindrik Stegenga on 11/11/2018.
//

#ifndef VKRENDERER_VULKANTYPES_H
#define VKRENDERER_VULKANTYPES_H

#include "SerializeMacro.h"
#include <MetaStuff/Meta.h>
#include <MetaStuff/JsonCast.h>

#include <string>

struct Test {

    int age;
    std::string name;

};


SERIALIZE_START(Test)
    SERIALIZE_MEMBER("age",  Test::age),
    SERIALIZE_MEMBER("name", Test::name)
SERIALIZE_END




#endif //VKRENDERER_VULKANTYPES_H
