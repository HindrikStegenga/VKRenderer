//
// Created by Hindrik Stegenga on 31-10-17.
//

#include "RenderWindow.h"

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
