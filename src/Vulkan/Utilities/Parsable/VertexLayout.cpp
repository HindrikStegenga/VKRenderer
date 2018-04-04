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

    parseLayout(json_rep);
    file.close();

}

bool VertexLayout::parseInputRate(string &value, VkVertexInputRate &inputRate) {

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

void VertexLayout::parseLayout(json& object) {

    vlName = object["name"];
    binding = object["binding"];

    string pInput = object["inputRate"];
    if(!parseInputRate(pInput, inputRate)){
        Logger::failure("Could not parse vertex layout inputrate!");
    }

    auto attribs = object["attributes"];
    for(auto& attrib : attribs)
    {
        VertexAttribute a = VertexAttribute::parseFromJSON(attrib);
        attributes.emplace_back(a);
    }

    std::sort(std::begin(attributes), std::end(attributes), [](const VertexAttribute& a, const VertexAttribute& b) -> bool {
         return a.attribute.location < b.attribute.location;
    });

    uint32_t offset = 0;
    for (auto &attribute : attributes) {
        attribute.attribute.offset = offset;
        offset += attribute.size();
    }
    stride = offset;
}

const string &VertexLayout::name() {
    return vlName;
}

