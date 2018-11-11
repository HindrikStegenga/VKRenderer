//
// Created by Hindrik Stegenga on 11/11/2018.
//

#ifndef VKRENDERER_VULKANTYPES_H
#define VKRENDERER_VULKANTYPES_H

#include <MetaStuff/JsonCast.h>
#include <MetaStuff/Meta.h>
#include "SerializeMacro.h"

#include <string>
#include <vector>

using std::string;
using std::vector;


struct VertexAttribute {
    string name;
    string type;
    int location;
};

struct VertexBinding {
    string inputRate;
    int binding;
    vector<VertexAttribute> attributes;
};

struct VertexLayout {
    string name;
    vector<VertexBinding> bindings;
};


SERIALIZE_START(VertexAttribute)
    SERIALIZE_MEMBER("name", VertexAttribute::name),
    SERIALIZE_MEMBER("type", VertexAttribute::type),
    SERIALIZE_MEMBER("location", VertexAttribute::location)
SERIALIZE_END

SERIALIZE_START(VertexBinding)
    SERIALIZE_MEMBER("inputRate", VertexBinding::inputRate),
    SERIALIZE_MEMBER("binding", VertexBinding::binding),
    SERIALIZE_MEMBER("attributes", VertexBinding::attributes)
SERIALIZE_END

SERIALIZE_START(VertexLayout)
    SERIALIZE_MEMBER("name", VertexLayout::name),
    SERIALIZE_MEMBER("bindings", VertexLayout::bindings)
SERIALIZE_END

#endif //VKRENDERER_VULKANTYPES_H
