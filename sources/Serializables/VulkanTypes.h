//
// Created by Hindrik Stegenga on 11/11/2018.
//

#ifndef VKRENDERER_VULKANTYPES_H
#define VKRENDERER_VULKANTYPES_H

#include <MetaStuff/JsonCast.h>
#include <MetaStuff/Meta.h>
#include "SerializeMacro.h"

#include <string>
#include <cstdint>
#include <vector>

using std::string;
using std::vector;

struct VertexFormatDescriptor {
    string name;
    string type;
    uint32_t location;
};

struct VertexBufferFormatDescriptor {
    string name;
    vector<VertexFormatDescriptor> formats;
};

struct MeshBufferDescriptor {
    string vertexBufferFileName;
    string vertexFormat;
    string indexBufferFileName;
    uint32_t indexBufferTypeSize;
};

struct MeshDescriptor {
    string name;
    vector<MeshBufferDescriptor> buffers;
};


SERIALIZE_START(VertexFormatDescriptor)
    SERIALIZE_MEMBER("name", VertexFormatDescriptor::name),
    SERIALIZE_MEMBER("type", VertexFormatDescriptor::type),
    SERIALIZE_MEMBER("location", VertexFormatDescriptor::location)
SERIALIZE_END

SERIALIZE_START(VertexBufferFormatDescriptor)
    SERIALIZE_MEMBER("name", VertexBufferFormatDescriptor::name),
    SERIALIZE_MEMBER("formats", VertexBufferFormatDescriptor::formats)
SERIALIZE_END

SERIALIZE_START(MeshBufferDescriptor)
    SERIALIZE_MEMBER("vertexBufferFileName", MeshBufferDescriptor::vertexBufferFileName),
    SERIALIZE_MEMBER("vertexFormat", MeshBufferDescriptor::vertexFormat),
    SERIALIZE_MEMBER("indexBufferFileName", MeshBufferDescriptor::indexBufferFileName),
    SERIALIZE_MEMBER("indexBufferTypeSize", MeshBufferDescriptor::indexBufferTypeSize)
SERIALIZE_END

SERIALIZE_START(MeshDescriptor)
    SERIALIZE_MEMBER("name", MeshDescriptor::name),
    SERIALIZE_MEMBER("buffers", MeshDescriptor::buffers)
SERIALIZE_END

#endif //VKRENDERER_VULKANTYPES_H
