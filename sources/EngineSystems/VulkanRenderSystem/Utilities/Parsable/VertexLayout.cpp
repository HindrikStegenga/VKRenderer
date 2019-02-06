//
// Created by Hindrik  Stegenga on 16/03/2018.
//

#include "VertexLayout.h"



VertexLayout::VertexLayout(const string &name)
{

    std::ifstream file(PATH_VERTEX_LAYOUT_JSON + name + ".json");

    if(!file.is_open())
        Logger::failure("File could not be opened: " + name);

    std::stringstream buffer;
    buffer << file.rdbuf();

    auto json_rep = json::parse(buffer.str());

    vlName = json_rep["name"];

    auto bindingSet = json_rep["bindings"];
    for(const auto& binding : bindingSet)
    {
        VertexBinding b(binding);
        bindings.emplace_back(b);
    }

    file.close();

}

const string& VertexLayout::name() {
    return vlName;
}

const vector<VkVertexInputAttributeDescription> VertexLayout::attributeDescriptions() {

    vector<VkVertexInputAttributeDescription> values;

    for(auto& binding : bindings)
    {
        for(auto& attribute : binding.attributeDescriptions())
        {
            values.push_back(attribute);
        }
    }
    return values;
}

const vector<VkVertexInputBindingDescription> VertexLayout::bindingDescriptions() {

    vector<VkVertexInputBindingDescription> descriptions = {};

    for(auto& item : bindings)
    {
        descriptions.emplace_back(item.bindingDescription());
    }

    return descriptions;
}