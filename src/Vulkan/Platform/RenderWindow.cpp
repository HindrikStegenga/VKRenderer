//
// Created by Hindrik Stegenga on 31-10-17.
//

#include "RenderWindow.h"
#include <cstring>

int  RenderWindow::windowCounter = 0;
bool RenderWindow::isGLFWinitialized = false;


RenderWindow::RenderWindow(uint32_t width, uint32_t height, bool resizable) {

    initGLFW();
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

    window = glfwCreateWindow(width, height, "VKRenderer", nullptr, nullptr);
    if (window == nullptr) {
        Logger::failure("Window creation failed!");
    }

    glfwShowWindow(window);

    windowCounter++;
}

static void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

void RenderWindow::initGLFW() {

    if (isGLFWinitialized) {
        glfwTerminate();
        isGLFWinitialized = false;
    }

    glfwSetErrorCallback(&glfwError);

    if (glfwInit() == GLFW_FALSE){
        isGLFWinitialized = false;
        Logger::failure("Could not initialize GLFW!");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    isGLFWinitialized = true;
}

RenderWindow::~RenderWindow() {

    if (window != nullptr){
        glfwDestroyWindow(window);
        window = nullptr;

        windowCounter--;
        if (windowCounter == 0){
            glfwTerminate();
            isGLFWinitialized = false;
        }
    }
}

bool RenderWindow::pollWindowEvents() const {

    bool shouldClose = glfwWindowShouldClose(window) == 1;
    if (!shouldClose)
    {
        glfwPollEvents();
        return true;
    }
    return false;
}

RenderWindow::RenderWindow(RenderWindow && rhs) noexcept {
    window = rhs.window;
    rhs.window = nullptr;
}

RenderWindow &RenderWindow::operator=(RenderWindow && rhs) noexcept {
    window = rhs.window;
    rhs.window = nullptr;
    return *this;
}

vector<const char*> RenderWindow::processExtensions(const vector<const char *>& instanceExtensions) const {

    vector<const char*> additionalExtensions(instanceExtensions);

    uint32_t glfwExtensionCount = 0;
    const char** extensions;

    extensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    for (uint32_t i = 0; i < glfwExtensionCount; ++i)
    {
        bool isFound = false;
        for (auto& instanceExtension : instanceExtensions)
        {
            if (strcmp(instanceExtension, extensions[i]) == 0)
            {
                isFound = true;
                continue;
            }
        }

        if (isFound)
        {
            continue;
        }
        additionalExtensions.push_back(extensions[i]);
    }

    return additionalExtensions;
}

VkSurfaceKHR RenderWindow::getWindowSurface(VkInstance instance)
{
    VkSurfaceKHR surface;
    VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
    if (result != VK_SUCCESS) {
        Logger::warn("Surface creation failed!");
        return VK_NULL_HANDLE;
    }
    return surface;
}
