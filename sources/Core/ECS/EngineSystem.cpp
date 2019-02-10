#include <utility>

//
// Created by hindrik on 6-2-19.
//

#include "EngineSystem.h"
#include "../Engine.h"

EngineSystem::~EngineSystem() = default;


void EngineSystem::setEnginePointer(Engine* engine) {
    this->engine = engine;
}

void EngineSystem::enqueueTask(function<void()> task) {
    engine->enqueueTask(std::move(task));
}

void EngineSystem::enqueueTask(AwaitableTask &task) {
    engine->enqueueTask(task);
}
