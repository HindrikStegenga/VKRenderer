//
// Created by Hindrik  Stegenga on 16/03/2018.
//

#ifndef VKRENDERER_VERTEXLAYOUT_H
#define VKRENDERER_VERTEXLAYOUT_H

#include "../../../CommonInclude.h"
#include "../../Platform/VulkanPlatform.h"
#include "../../../../libraries/nlohmannJSON/json.hpp"
#include "VertexAttribute.h"

using json = nlohmann::json;

class VertexLayout final {
private:
    string                  name            = "";
    VkVertexInputRate       inputRate       = VK_VERTEX_INPUT_RATE_MAX_ENUM;
    uint32_t                stride          = 0;
    uint32_t                binding         = 0;
    vector<VertexAttribute> attributes      = {};

public:
    explicit VertexLayout(const string& name);
    ~VertexLayout() = default;

    VertexLayout(const VertexLayout&) = default;
    VertexLayout(VertexLayout&&) = delete;

    VertexLayout& operator=(const VertexLayout&) = default;
    VertexLayout& operator=(VertexLayout&) = delete;




private:
    static bool parseInputRate(string& value, VkVertexInputRate& inputRate);
    void parseLayout(json& object);
};


#endif //VKRENDERER_VERTEXLAYOUT_H
