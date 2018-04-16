//
// Created by Hindrik  Stegenga on 10/04/2018.
//

#include "ObjLoader.h"

vector<vec3>& ObjLoader::vertices() {
    return loadedVertices;
}

vector<vec2>& ObjLoader::UVs() {
    return loadedUVs;
}

vector<vec3>& ObjLoader::normals() {
    return loadedNormals;
}

ObjLoader::ObjLoader(string fileName) : fileName(fileName){
    loadOBJ(fileName);
}

void ObjLoader::loadOBJ(string& fileName) {

    std::ifstream file(PATH_MODELS + fileName);
    string line;

    std::regex match_vertex("^v\\s+([-+]?[0-9]*\\.?[0-9]+)\\s+([-+]?[0-9]*\\.?[0-9]+)\\s+([-+]?[0-9]*\\.?[0-9]+)\\s*$");
    std::regex match_uv("^vt\\s+([-+]?[0-9]*\\.?[0-9]+)\\s+([-+]?[0-9]*\\.?[0-9]+)\\s*$");
    std::regex match_normal("^vn\\s+([-+]?[0-9]*\\.?[0-9]+)\\s+([-+]?[0-9]*\\.?[0-9]+)\\s+([-+]?[0-9]*\\.?[0-9]+)\\s*$");

    if(!file.is_open())
    {
        file.close();
        Logger::failure("Could not load OBJ file! " + fileName);
    }

    while(std::getline(file, line))
    {
        std::smatch results;

        //Vertices
        if(std::regex_match(line, results, match_vertex))
        {
            float x = static_cast<float>(std::atof(string(results[1]).c_str()));
            float y = static_cast<float>(std::atof(string(results[2]).c_str()));
            float z = static_cast<float>(std::atof(string(results[3]).c_str()));

            loadedVertices.push_back(vec3{x,y,z});

            continue;
        }

        //Texture Coordinates
        if(std::regex_match(line, results, match_uv))
        {
            float x = static_cast<float>(std::atof(string(results[1]).c_str()));
            float y = static_cast<float>(std::atof(string(results[2]).c_str()));

            loadedUVs.push_back(vec2{x,y});

            continue;
        }

        //Normals
        if(std::regex_match(line, results, match_normal))
        {
            float x = static_cast<float>(std::atof(string(results[1]).c_str()));
            float y = static_cast<float>(std::atof(string(results[2]).c_str()));
            float z = static_cast<float>(std::atof(string(results[3]).c_str()));

            loadedNormals.push_back(vec3{x,y,z});

            continue;
        }
    }
    Logger::log("Loaded OBJ file: " + fileName);
    file.close();
}
