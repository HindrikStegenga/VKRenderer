//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_APPLICATION_H
#define VKRENDERER_APPLICATION_H

#include "CommonInclude.h"
#include "Vulkan/VulkanRenderer.h"
#include "Utilities/Nullable.h"
#include "Utilities/Clock.h"

class Application final {
public:
    Application();
    ~Application() = default;

    Application(const Application&)     = delete;
    Application(Application&&) noexcept = delete;

    Application& operator= (const Application&)     = delete;
    Application& operator= (Application&&) noexcept = delete;
public:
    void run();
    void stop();
private:
    Nullable<VulkanRenderer> renderer;
    Clock internalClock;
    string applicationName;
    bool   mustStop = false;
public:



};


#endif //VKRENDERER_APPLICATION_H
