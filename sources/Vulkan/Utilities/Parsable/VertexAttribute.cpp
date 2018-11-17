//
// Created by Hindrik  Stegenga on 31/03/2018.
//

#include "VertexAttribute.h"

string VertexAttribute::name() {
    return std::string(attribName.data());
}

bool VertexAttribute::parseFormat(string value, VkFormat &format) {

    //doubles

    if(value == "dvec4")
    {
        format = VK_FORMAT_R64G64B64A64_SFLOAT;
        return true;
    }
    if(value == "dvec3")
    {
        format = VK_FORMAT_R64G64B64_SFLOAT;
        return true;
    }
    if(value == "dvec2")
    {
        format = VK_FORMAT_R64G64_SFLOAT;
        return true;
    }
    if(value == "double")
    {
        format = VK_FORMAT_R64_SFLOAT;
        return true;
    }
    
    //floats
    if(value == "vec4")
    {
        format = VK_FORMAT_R32G32B32A32_SFLOAT;
        return true;
    }
    if(value == "vec3")
    {
        format = VK_FORMAT_R32G32B32_SFLOAT;
        return true;
    }
    if(value == "vec2")
    {
        format = VK_FORMAT_R32G32_SFLOAT;
        return true;
    }
    if(value == "float")
    {
        format = VK_FORMAT_R32_SFLOAT;
        return true;
    }


    //Signed ints
    if(value == "ivec4")
    {
        format = VK_FORMAT_R32G32B32A32_SINT;
        return true;
    }
    if(value == "ivec3")
    {
        format = VK_FORMAT_R32G32B32_SINT;
        return true;
    }
    if(value == "ivec2")
    {
        format = VK_FORMAT_R32G32_SINT;
        return true;
    }
    if(value == "int")
    {
        format = VK_FORMAT_R32_SINT;
        return true;
    }

    //Unsigned ints
    if(value == "uvec4")
    {
        format = VK_FORMAT_R32G32B32A32_UINT;
        return true;
    }
    if(value == "uvec3")
    {
        format = VK_FORMAT_R32G32B32_UINT;
        return true;
    }
    if(value == "uvec2")
    {
        format = VK_FORMAT_R32G32_UINT;
        return true;
    }
    if(value == "uint")
    {
        format = VK_FORMAT_R32_UINT;
        return true;
    }


    return false;
}

uint32_t VertexAttribute::size() {

    switch(attribute.format)
    {
        case VK_FORMAT_R32_SFLOAT:
        case VK_FORMAT_R32_UINT:
        case VK_FORMAT_R32_SINT:
            return 4;

        case VK_FORMAT_R32G32_SFLOAT:
        case VK_FORMAT_R32G32_SINT:
        case VK_FORMAT_R32G32_UINT:
            return 8;

        case VK_FORMAT_R32G32B32_SFLOAT:
        case VK_FORMAT_R32G32B32_SINT:
        case VK_FORMAT_R32G32B32_UINT:
            return 12;

        case VK_FORMAT_R32G32B32A32_SFLOAT:
        case VK_FORMAT_R32G32B32A32_SINT:
        case VK_FORMAT_R32G32B32A32_UINT:
            return 16;


        case VK_FORMAT_R64G64B64A64_SFLOAT:
            return 32;
        case VK_FORMAT_R64G64B64_SFLOAT:
            return 24;
        case VK_FORMAT_R64G64_SFLOAT:
            return 16;
        case VK_FORMAT_R64_SFLOAT:
            return 8;

        default:
            return 0;
    }
}

VertexAttribute::VertexAttribute(json object) {

    string parsedName = object["name"];

    if(parsedName.size() >= attribNameMaxSize) {
        Logger::failure("Too large name size!");
    }

    uint32_t idx = 0;
    for(char& a : parsedName) {
        attribName[idx] = a;
        idx++;
    }

    attribute.location = object["location"];
    if(!parseFormat(object["type"], attribute.format))
    {
        Logger::failure("Failed to parse type!");
    }

    attribute.binding = object["binding"];
}

VkVertexInputAttributeDescription VertexAttribute::attributeDescription() {
    return attribute;
}

void VertexAttribute::setOffset(uint32_t offset) {
    attribute.offset = offset;
}
