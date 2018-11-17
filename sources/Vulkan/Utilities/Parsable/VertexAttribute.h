//
// Created by Hindrik  Stegenga on 31/03/2018.
//

#ifndef VKRENDERER_VERTEXATTRIBUTE_H
#define VKRENDERER_VERTEXATTRIBUTE_H

#include "../../../CommonInclude.h"
#include "../../Platform/VulkanPlatform.h"
#include <nlohmannJSON/json.hpp>

using json = nlohmann::json;

struct VertexAttribute {
private:
    constexpr static uint32_t attribNameMaxSize = 16;

    std::array<char, attribNameMaxSize>  attribName     = {};
    VkVertexInputAttributeDescription attribute         = {};

public:
    explicit VertexAttribute(json object);
    ~VertexAttribute() = default;

    VertexAttribute(const VertexAttribute&) = default;
    VertexAttribute(VertexAttribute&&)      = default;

    VertexAttribute& operator=(const VertexAttribute&)  = default;
    VertexAttribute& operator=(VertexAttribute&&)       = default;

public:
    string name();
    uint32_t size();
    void setOffset(uint32_t offset);
    VkVertexInputAttributeDescription attributeDescription();
public:
    static bool parseFormat(string value, VkFormat& format);
};


#endif //VKRENDERER_VERTEXATTRIBUTE_H
