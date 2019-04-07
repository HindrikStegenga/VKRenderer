//
// Created by hindriks on 7-4-19.
//

#ifndef VKRENDERER_JSONLOADER_H
#define VKRENDERER_JSONLOADER_H

#include <string>
#include "nlohmannJSON/json.hpp"
#include <fstream>
#include "Logger.h"

using std::string;
using nlohmann::json;

template<typename T>
T loadJSONFile(const string& fileName) {

    std::ifstream inputFileStream(fileName);
    if (!inputFileStream.is_open()) {
        Logger::failure("Could not open file: " + fileName);
    }

    std::stringstream stringBuffer;
    stringBuffer << inputFileStream.rdbuf();

    auto JSONRepresentation = json::parse(stringBuffer.str());

    inputFileStream.close();
    stringBuffer.clear();

    return JSONRepresentation.get<T>();
}

#endif //VKRENDERER_JSONLOADER_H
