#include <utility>

#include <utility>

//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "Engine.h"
#include "../Utilities/ConfigFileReader.h"
#include "../Serializables/ConfigTypes.h"
#include "Threading/AwaitableTask.h"

Engine::Engine(ApplicationSettings applicationSettings, GraphicsSettings graphicsSettings)
    : applicationSettings(std::move(applicationSettings)), graphicsSettings(graphicsSettings), threadpool(std::thread::hardware_concurrency())
    {
}

void Engine::run() {

    //Fixed update thread
    std::thread fixedUpdateThread([this](){

        while (!mustStop) {

            auto start = std::chrono::steady_clock::now();

            for(auto& systemPtr : engineSystems) {

                if (!systemPtr.getEngineSystem().fixedUpdate()) {
                    mustStop = true;
                    break;
                }
            }

            if(mustStop)
                break;

            auto delta = std::chrono::steady_clock::now() - start;
            auto sleepTime = std::chrono::milliseconds(20) - delta;

            if(sleepTime > nanoseconds(0))
            std::this_thread::sleep_for(sleepTime);
        }
    });

    //Current main thread
    while (!mustStop) {

        //Get delta time since previous frame.
        std::chrono::nanoseconds deltaTime = internalClock.getDeltaTime();

        for(auto& systemPtr : engineSystems) {
            EngineSystem& system = systemPtr.getEngineSystem();

            if(systemPtr.mustWaitForFixedUpdateThread()) {
                //Wait for fixedUpdate() here...
                systemPtr.waitForFixedUpdateThread();
            } //Resume after fixedUpdate() completed.

            system.update(deltaTime);
        }
    }
    fixedUpdateThread.join();
}

void Engine::stop() {
    mustStop = true;
}

void Engine::windowHasResized(uint32_t width, uint32_t height, RenderWindow *window) {

    for(auto& system : engineSystems)
        system.getEngineSystem().windowHasResized(width, height, window);
}

string Engine::getVersionString(uint32_t major, uint32_t minor, uint32_t patch) {
    using std::to_string;
    return to_string(major) + "." + to_string(minor) + "." + to_string(patch);
}

void Engine::enqueueTask(function<void()> task) {
    threadpool.enqueue(std::move(task));
}

void Engine::enqueueTask(AwaitableTask &task) {
    task.enqueue(threadpool);
}

vector<RenderWindow> &Engine::getRenderWindows() {
    return renderWindows;
}

void Engine::haltUpdateThread(EngineSystem *engineSystem) {
    for(auto& s : engineSystems) {
        if(&s.getEngineSystem() == engineSystem){
            s.haltUpdateThread();
            return;
        }
    }
    Logger::failure("Engine System not found? How can this be?");
}

void Engine::resumeUpdateThread(EngineSystem *engineSystem) {
    for(auto& s : engineSystems) {
        if(&s.getEngineSystem() == engineSystem){
            s.resumeUpdateThread();
            return;
        }
    }
    Logger::failure("Engine System not found? How can this be?");
}

void Engine::haltFixedUpdateThread(EngineSystem *engineSystem) {
    for(auto& s : engineSystems) {
        if(&s.getEngineSystem() == engineSystem){
            s.haltFixedUpdateThread();
            return;
        }
    }
    Logger::failure("Engine System not found? How can this be?");
}

void Engine::resumeFixedUpdateThread(EngineSystem *engineSystem) {
    for(auto& s : engineSystems) {
        if(&s.getEngineSystem() == engineSystem){
            s.resumeFixedUpdateThread();
            return;
        }
    }
    Logger::failure("Engine System not found? How can this be?");
}