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

    EngineSystem(const EngineSystem&) = delete;
    EngineSystem(EngineSystem&&) = delete;

    EngineSystem& operator=(const EngineSystem&) = delete;
    EngineSystem& operator=(EngineSystem&&) = delete;
public:
    void haltFixedUpdateThread();
    void resumeFixedUpdateThread();

    void haltUpdateThread();
    void resumeUpdateThread();
private:
    friend class Engine;
    //Is called by main thread to wait on fixedUpdate thread.
    void processFixedThreadSyncs();
public:
    void enqueueTask(function<void()> task);
    void enqueueTask(AwaitableTask& task);

    virtual void windowHasResized(uint32_t width, uint32_t height, RenderWindow *window) = 0;

    //Update function for dynamic updates
    virtual void update(std::chrono::nanoseconds deltaTime) = 0;

    //Function for getting status. Is called before fixedUpdate();
    virtual bool getSystemStatus() = 0;

    //Update function for fixed time updates and event handling
    virtual void fixedUpdate() = 0;
};

#endif //VKRENDERER_ENGINESYSTEM_H
