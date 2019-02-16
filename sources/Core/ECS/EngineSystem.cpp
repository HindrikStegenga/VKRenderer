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