#include <utility>

#include <utility>

//
// Created by Hindrik Stegenga on 29-10-17.
//

#include "Engine.h"
#include "../Utilities/ConfigFileReader.h"
#include "../Serializables/ConfigTypes.h"
#include "Threading/AwaitableTask.h"

using std::thread;

Engine::Engine(ApplicationSettings applicationSettings, GraphicsSettings graphicsSettings)
    : applicationSettings(std::move(applicationSettings)), graphicsSettings(graphicsSettings), threadpool(std::thread::hardware_concurrency())
    {
}

void Engine::run() {

    while (!mustStop) {

        //Get delta time since previous frame.
        std::chrono::nanoseconds deltaTime = internalClock.getDeltaTime();

        for(auto& systemPtr : engineSystems) {
            EngineSystem& system = *systemPtr;

            if(!system.update(deltaTime)) {
                mustStop = true;
                break;
            }
        }
    }
}

void Engine::stop() {
    mustStop = true;
}

void Engine::windowHasResized(uint32_t width, uint32_t height, RenderWindow *window) {

    for(auto& system : engineSystems)
        system->windowHasResized(width, height, window);
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

float Engine::getTimeScale() const {
    return timeScale;
}

void Engine::setTimeScale(float scale) {
    if (scale < 0.0f) {
        Logger::warn("Time scale cannot be set to a negative number. It will be set to 0");
        timeScale = 0.0f;
        return;
    }
    timeScale = scale;
}