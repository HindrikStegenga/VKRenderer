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
using std::unique_lock;
using std::lock_guard;
using std::condition_variable;

class EngineSystemThreadingContainer final {
private:
    unique_ptr<EngineSystem> engineSystem;

    mutex waitOnFixedMutex;
    mutex waitOnMainMutex;

    condition_variable mustWaitOnFixedCV;
    condition_variable mustWaitOnMainCV;

    bool waitForFixedUpdate = false;
    bool waitForUpdate      = false;
public:
    EngineSystemThreadingContainer() = default;
    explicit EngineSystemThreadingContainer(unique_ptr<EngineSystem>&& ptr);

    EngineSystemThreadingContainer(const EngineSystemThreadingContainer&) = delete;
    EngineSystemThreadingContainer(EngineSystemThreadingContainer&&) = delete;

    EngineSystemThreadingContainer& operator=(const EngineSystemThreadingContainer&) = delete;
    EngineSystemThreadingContainer& operator=(EngineSystemThreadingContainer&&) = delete;
public:
    EngineSystem& getEngineSystem();

    bool mustWaitForUpdateThread();
    void waitForUpdateThread();
    void haltFixedUpdateThread();
    void resumeFixedUpdateThread();

    bool mustWaitForFixedUpdate();
    void waitForFixedUpdateThread();
    void haltUpdateThread();
    void resumeUpdateThread();
};


#endif //VKRENDERER_ENGINESYSTEMTHREADINGCONTAINER_H
