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

void EngineSystem::haltFixedUpdateThread() {
    engine->haltFixedUpdateThread(this);
}

void EngineSystem::resumeFixedUpdateThread() {
    engine->resumeFixedUpdateThread(this);
}
