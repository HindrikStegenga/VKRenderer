//
// Created by Hindrik Stegenga on 31-10-17.
//

#ifndef VKRENDERER_RENDERWINDOW_H
#define VKRENDERER_RENDERWINDOW_H

#include "VulkanPlatform.h"

class RenderWindow final {
public:
    RenderWindow(uint32_t width, uint32_t height, bool resizable = false);
    ~RenderWindow();

    RenderWindow(const RenderWindow&) = delete;
    RenderWindow& operator=(const RenderWindow&) = delete;

    RenderWindow(RenderWindow&& rhs) noexcept;
    RenderWindow& operator=(RenderWindow&& rhs) noexcept;
private:
    static int  windowCounter;
    static void initGLFW();
    static bool isGLFWinitialized;
private:
    GLFWwindow* window = nullptr;
    VKUH<VkSurfaceKHR> surface = VKUH<VkSurfaceKHR>();
public:
    bool pollWindowEvents() const;
    VkSurfaceKHR getWindowSurface(VkInstance instance);
    vector<const char*> processExtensions(const vector<const char *> & instanceExtensions) const;
};


#endif //VKRENDERER_RENDERWINDOW_H
