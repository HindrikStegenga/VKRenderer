//
// Created by hindriks on 7-4-19.
//

#include "SceneManager.h"
#include "../Utilities/Logger.h"
#include "../Paths.h"
#include "../Utilities/JSONLoader.h"

void SceneManager::loadScene(const string &name) {

    loadedScenes.emplace_back(loadJSONFile<Scene>(PATH_SCENES + name + ".json"));
    Logger::success("Loaded scene: " + name);
}