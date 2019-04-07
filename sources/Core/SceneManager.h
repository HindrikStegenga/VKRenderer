//
// Created by hindriks on 7-4-19.
//

#ifndef VKRENDERER_SCENEMANAGER_H
#define VKRENDERER_SCENEMANAGER_H

#include <vector>
#include "Scene.h"

using std::vector;

class SceneManager final {
private:
    vector<Scene> loadedScenes = {};
public:
    SceneManager() = default;
    ~SceneManager() = default;

    SceneManager(const SceneManager&) = delete;
    SceneManager(SceneManager&&) noexcept = default;

    SceneManager& operator=(const SceneManager&) = delete;
    SceneManager& operator=(SceneManager&&) noexcept = default;
public:
    void loadScene(const string& name);





};


#endif //VKRENDERER_SCENEMANAGER_H
