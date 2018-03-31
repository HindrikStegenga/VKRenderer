//
// Created by Hindrik  Stegenga on 31/03/2018.
//

#ifndef VKRENDERER_VERTEXATTRIBUTE_H
#define VKRENDERER_VERTEXATTRIBUTE_H

#include "../../../CommonInclude.h"
#include "../../Platform/VulkanPlatform.h"
#include "../../../../libraries/nlohmannJSON/json.hpp"

using json = nlohmann::json;

struct VertexAttribute {
private:

    constexpr static uint32_t attribNameMaxSize = 16;

    std::array<char, attribNameMaxSize>  attribName      = {};
public:
    VkVertexInputAttributeDescription attribute = {};
public:
    string name();
    uint32_t size();
public:
    static VertexAttribute parseFromJSON(json object);
    static bool parseFormat(string value, VkFormat& format);
};


#endif //VKRENDERER_VERTEXATTRIBUTE_H
