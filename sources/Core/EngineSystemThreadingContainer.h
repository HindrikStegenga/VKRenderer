//
// Created by hindrik on 15-2-19.
//

#ifndef VKRENDERER_ENGINESYSTEMTHREADINGCONTAINER_H
#define VKRENDERER_ENGINESYSTEMTHREADINGCONTAINER_H

//
// Created by hindrik on 15-2-19.
//

#include <mutex>
#include <memory>
#include <condition_variable>

#include "ECS/EngineSystem.h"

using std::unique_ptr;
using std::mutex;
using std::condition_variable;

class EngineSystemThreadingContainer final {
private:
    unique_ptr<EngineSystem> engineSystem;
    mutex syncMutex;
    condition_variable conditionVariable;
public:
    EngineSystemThreadingContainer() = default;
    explicit EngineSystemThreadingContainer(unique_ptr<EngineSystem>&& ptr);

    EngineSystemThreadingContainer(const EngineSystemThreadingContainer&) = delete;
    EngineSystemThreadingContainer(EngineSystemThreadingContainer&&) = delete;

    EngineSystemThreadingContainer& operator=(const EngineSystemThreadingContainer&) = delete;
    EngineSystemThreadingContainer& operator=(EngineSystemThreadingContainer&&) = delete;
public:
    EngineSystem& getEngineSystem();

};

inline EngineSystemThreadingContainer::EngineSystemThreadingContainer(unique_ptr<EngineSystem>&& ptr) : engineSystem(std::move(ptr)) {
}

inline EngineSystem &EngineSystemThreadingContainer::getEngineSystem() {
    return *engineSystem;
}


#endif //VKRENDERER_ENGINESYSTEMTHREADINGCONTAINER_H
