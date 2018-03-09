//
// Created by Hindrik Stegenga on 31-10-17.
//

#ifndef VKRENDERER_RENDERWINDOW_H
#define VKRENDERER_RENDERWINDOW_H

#include "VulkanPlatform.h"

#define WINDOW_MIN_WIDTH 480
#define WINDOW_MIN_HEIGHT 320
#define WINDOW_MAX_WIDTH 16384
#define WINDOW_MAX_HEIGHT 16384

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
    GLFWwindow* window  = nullptr;
    uint32_t nextWidth  = 0;
    uint32_t nextHeight = 0;
private:
    static void onWindowResize(GLFWwindow* window, int width, int height);
public:
    bool pollWindowEvents() const;
    bool mustWindowResize(uint32_t& pWidth, uint32_t& pHeight);
    VkSurfaceKHR getWindowSurface(VkInstance instance);
    vector<const char*> processExtensions(const vector<const char *> & instanceExtensions) const;
};




#endif //VKRENDERER_RENDERWINDOW_H
