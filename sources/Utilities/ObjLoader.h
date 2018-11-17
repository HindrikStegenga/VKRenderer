//
// Created by Hindrik  Stegenga on 10/04/2018.
//

#ifndef VKRENDERER_OBJLOADER_H
#define VKRENDERER_OBJLOADER_H

#include "../CommonInclude.h"
#include "BasicVectorTypes.h"
#include "Macros.h"
#include <regex>

class ObjLoader final {
private:
    string fileName;

    vector<vec3> loadedVertices;
    vector<vec2> loadedUVs;
    vector<vec3> loadedNormals;
public:
    explicit ObjLoader(string fileName);
    ~ObjLoader() = default;
public:
    vector<vec3>& vertices();
    vector<vec2>& UVs();
    vector<vec3>& normals();
private:
    void loadOBJ(string& fileName);
};


#endif //VKRENDERER_OBJLOADER_H
