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

struct MeshVertexPropertyBufferDescriptor {
    string fileName;
    string format;
    uint32_t offset;
    uint32_t byteSize;
};

struct MeshIndexBufferDescriptor {
    string fileName;
    uint32_t typeSize;
    uint32_t offset;
    uint32_t byteSize;
};

struct MeshDescriptor {
    string name;
    vector<MeshVertexPropertyBufferDescriptor> buffers;
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

SERIALIZE_START(MeshVertexPropertyBufferDescriptor)
    SERIALIZE_MEMBER("fileName", MeshVertexPropertyBufferDescriptor::fileName),
    SERIALIZE_MEMBER("format", MeshVertexPropertyBufferDescriptor::format),
    SERIALIZE_MEMBER("offset", MeshVertexPropertyBufferDescriptor::offset),
    SERIALIZE_MEMBER("byteSize", MeshVertexPropertyBufferDescriptor::byteSize)
SERIALIZE_END

SERIALIZE_START(MeshIndexBufferDescriptor)
    SERIALIZE_MEMBER("fileName", MeshIndexBufferDescriptor::fileName),
    SERIALIZE_MEMBER("typeSize", MeshIndexBufferDescriptor::typeSize),
    SERIALIZE_MEMBER("offset", MeshIndexBufferDescriptor::offset),
    SERIALIZE_MEMBER("byteOffset", MeshIndexBufferDescriptor::byteSize)
SERIALIZE_END

SERIALIZE_START(MeshDescriptor)
    SERIALIZE_MEMBER("name", MeshDescriptor::name),
    SERIALIZE_MEMBER("buffers", MeshDescriptor::buffers)
SERIALIZE_END

#endif //VKRENDERER_VULKANTYPES_H
