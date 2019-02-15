//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_APPLICATION_H
#define VKRENDERER_APPLICATION_H

#include "../CommonInclude.h"
#include "../EngineSystems/VulkanRenderSystem/Platform/RenderWindow.h"
#include "../EngineSystems/VulkanRenderSystem/VulkanRenderSystem.h"
#include "../Utilities/Nullable.h"
#include "../Utilities/Clock.h"
#include "../Serializables/ConfigTypes.h"
#include "ECS/EngineSystem.h"
#include "Threading/Threadpool.h"
#include "SceneManager.h"

class Engine final {
private:
    Threadpool                          threadpool;
    vector<RenderWindow>                renderWindows = {};

    StaticStack<unique_ptr<EngineSystem>, 16> engineSystems = {};
    SceneManager                        sceneManager;

    ApplicationSettings                 applicationSettings = {};
    GraphicsSettings                    graphicsSettings = {};

    Clock                               internalClock;
    bool                                mustStop = false;
public:
    Engine(ApplicationSettings applicationSettings, GraphicsSettings graphicsSettings);
    ~Engine() = default;

    Engine(const Engine&)     = delete;
    Engine(Engine&&) noexcept = delete;

    Engine& operator= (const Engine&)     = delete;
    Engine& operator= (Engine&&) noexcept = delete;
public:
    void windowHasResized(uint32_t width, uint32_t height, RenderWindow *window);
    void run();
    void stop();
private:
    void setupEngineSystems();
public:
    template<typename T, typename ...Args>
    void registerEngineSystem(Args... args);
    template<typename ...Args>
    void registerRenderWindow(Args... args);

    void registerRenderWindow(RenderWindow& renderWindow);
    void registerEngineSystem(EngineSystem& engineSystem);

    void enqueueTask(function<void()> task);
    void enqueueTask(AwaitableTask& task);

    vector<RenderWindow>& getRenderWindows();
public:
    static string getVersionString(uint32_t major, uint32_t minor, uint32_t patch);
};

template<typename T, typename... Args>
inline void Engine::registerEngineSystem(Args... args) {
    engineSystems.emplace(T(std::forward(args)...));
    engineSystems.top()->setEnginePointer(this);
}

template<typename... Args>
inline void Engine::registerRenderWindow(Args... args) {
    renderWindows.emplace_back(std::forward(args)...);
    renderWindows.back().setEnginePointer(this);
}

#endif //VKRENDERER_APPLICATION_H
