//
// Created by Hindrik  Stegenga on 04/04/2018.
//

#include "VertexBinding.h"

VertexBinding::VertexBinding(json object) {

    vlName = object["name"];
    binding.binding = object["binding"];

    string pInput = object["inputRate"];
    if(!parseInputRate(pInput, binding.inputRate)){
        Logger::failure("Could not parse vertex layout inputrate!");
    }

    auto attribs = object["attributes"];
    for(auto& attrib : attribs)
    {
        VertexAttribute a(attrib);
        attributes.emplace_back(a);
    }

    std::sort(std::begin(attributes), std::end(attributes), [](VertexAttribute& a, VertexAttribute& b) -> bool {
        return a.attributeDescription().location < b.attributeDescription().location;
    });

    uint32_t offset = 0;
    for (auto &attribute : attributes) {
        attribute.setOffset(offset);
        offset += attribute.size();
    }
    binding.stride = offset;
}

bool VertexBinding::parseInputRate(string &value, VkVertexInputRate &inputRate) {

    if(value == "perVertex") {
        inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return true;
    }
    if(value == "perInstance") {
        inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
        return true;
    }
    return false;
}

string& VertexBinding::name() {
    return vlName;
}

vector<VkVertexInputAttributeDescription> VertexBinding::attributeDescriptions() {

    vector<VkVertexInputAttributeDescription> values;

    for(auto& item : attributes)
    {
        values.emplace_back(item.attributeDescription());
    }
    return values;
}

VkVertexInputBindingDescription VertexBinding::bindingDescription() {
    return binding;
}