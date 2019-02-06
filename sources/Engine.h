//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_APPLICATION_H
#define VKRENDERER_APPLICATION_H

#include "CommonInclude.h"
#include "Vulkan/Platform/RenderWindow.h"
#include "Vulkan/VulkanRenderer.h"
#include "Utilities/Nullable.h"
#include "Utilities/Clock.h"
#include "Serializables/ConfigTypes.h"

class Engine final {
private:
    vector<RenderWindow>    renderWindows = {};
    VulkanRenderer          renderer;
    Clock                   internalClock;
    bool                    mustStop = false;
public:
    Engine(ApplicationSettings applicationSettings, GraphicsSettings graphicsSettings);
    ~Engine() = default;

    Engine(const Engine&)     = delete;
    Engine(Engine&&) noexcept = delete;

    Engine& operator= (const Engine&)     = delete;
    Engine& operator= (Engine&&) noexcept = delete;
public:
    void resizeWindow(uint32_t width, uint32_t height, RenderWindow* window);
    void run();
    void stop();
private:
    static string getVersionString(uint32_t major, uint32_t minor, uint32_t patch);
};


#endif //VKRENDERER_APPLICATION_H