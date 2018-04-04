//
// Created by Hindrik  Stegenga on 04/04/2018.
//

#ifndef VKRENDERER_VERTEXBINDING_H
#define VKRENDERER_VERTEXBINDING_H

#include "../../../CommonInclude.h"
#include "../../Platform/VulkanPlatform.h"
#include "../../../../libraries/nlohmannJSON/json.hpp"
#include "VertexAttribute.h"

using json = nlohmann::json;

class VertexBinding final {
private:
    string                  vlName              = "";
    VkVertexInputBindingDescription binding     = {};
    vector<VertexAttribute> attributes          = {};

public:
    explicit VertexBinding(json object);
    ~VertexBinding() = default;

    VertexBinding(const VertexBinding&) = default;
    VertexBinding(VertexBinding&&)      = default;

    VertexBinding& operator=(const VertexBinding&)  = default;
    VertexBinding& operator=(VertexBinding&&)       = default;

    string& name();
    vector<VkVertexInputAttributeDescription> attributeDescriptions();
    VkVertexInputBindingDescription bindingDescription();

private:
    static bool parseInputRate(string& value, VkVertexInputRate& inputRate);
};


#endif //VKRENDERER_VERTEXBINDING_H
