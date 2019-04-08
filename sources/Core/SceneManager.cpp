//
// Created by hindriks on 7-4-19.
//

#include "SceneManager.h"
#include "../Utilities/Logger.h"
#include "../Paths.h"
#include "../Utilities/JSONLoader.h"

void SceneManager::loadScene(const string &name) {

    //TODO: Fix this shit.
    //auto n = loadJSONFile<Scene>(PATH_SCENES + name + ".json");
    //loadedScenes.emplace_back();
    Logger::success("Loaded scenes: " + name);
}