//
// Created by Hindrik  Stegenga on 16/03/2018.
//

#ifndef VKRENDERER_VERTEXLAYOUT_H
#define VKRENDERER_VERTEXLAYOUT_H

#include "../../../CommonInclude.h"
#include "../../Platform/VulkanPlatform.h"
#include <nlohmannJSON/json.hpp>
#include "VertexAttribute.h"
#include "VertexBinding.h"

using json = nlohmann::json;

class VertexLayout final {
private:
    string                  vlName          = "";
    vector<VertexBinding>   bindings        = {};
public:
    explicit VertexLayout(const string& name);
    ~VertexLayout() = default;

    VertexLayout(const VertexLayout&)   = default;
    VertexLayout(VertexLayout&&)        = default;

    VertexLayout& operator=(const VertexLayout&)    = default;
    VertexLayout& operator=(VertexLayout&&)         = default;

    const string& name();
    const vector<VkVertexInputAttributeDescription> attributeDescriptions();
    const vector<VkVertexInputBindingDescription>   bindingDescriptions();
};


#endif //VKRENDERER_VERTEXLAYOUT_H
