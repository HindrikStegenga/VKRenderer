#include <utility>

//
// Created by hindrik on 6-2-19.
//

#include "EngineSystem.h"
#include "../Engine.h"

EngineSystem::EngineSystem(Engine* engine) : engine(engine) {}

EngineSystem::~EngineSystem() = default;

void EngineSystem::enqueueTask(function<void()> task) {
    engine->enqueueTask(std::move(task));
}

void EngineSystem::enqueueTask(AwaitableTask &task) {
    engine->enqueueTask(task);
}

void EngineSystem::resumeUpdateThread() {
    engine->resumeUpdateThread(this);
}

void EngineSystem::haltUpdateThread() {
    engine->haltUpdateThread(this);
}

void EngineSystem::processFixedThreadSyncs() {
    if(!engine->mustWaitForFixedUpdateThread(this))
        return;

    //Wait for fixed update here...
    engine->waitForFixedUpdateThread(this);
}

void EngineSystem::haltFixedUpdateThread() {

}

void EngineSystem::resumeFixedUpdateThread() {

}
