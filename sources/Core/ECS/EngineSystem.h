//
// Created by hindrik on 6-2-19.
//

#ifndef VKRENDERER_ENGINESYSTEM_H
#define VKRENDERER_ENGINESYSTEM_H

#include <string>
#include <vector>
#include <chrono>
#include <functional>

using std::function;
using std::vector;
using std::string;
using std::chrono::nanoseconds;

class Engine;
class AwaitableTask;
class RenderWindow;

class EngineSystem {
private:
    Engine* engine = nullptr;
public:
    explicit EngineSystem(Engine* engine);
    virtual ~EngineSystem() = 0;

    EngineSystem(const EngineSystem&)   = delete;
    EngineSystem(EngineSystem&&)        = delete;

    EngineSystem& operator=(const EngineSystem&)    = delete;
    EngineSystem& operator=(EngineSystem&&)         = delete;
public:
    void enqueueTask(function<void()> task);
    void enqueueTask(AwaitableTask& task);

    virtual void windowHasResized(uint32_t width, uint32_t height, RenderWindow* window) = 0;

    //Update function for updates
    virtual bool update(std::chrono::nanoseconds deltaTime) = 0;
};

#endif //VKRENDERER_ENGINESYSTEM_H
