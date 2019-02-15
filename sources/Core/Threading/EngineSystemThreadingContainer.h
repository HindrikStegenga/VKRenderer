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

#include "../ECS/EngineSystem.h"

using std::unique_ptr;
using std::mutex;
using std::unique_lock;
using std::lock_guard;
using std::condition_variable;

class EngineSystemThreadingContainer final {
private:
    unique_ptr<EngineSystem> engineSystem;

    mutex waitForFixedUpdateMutex;
    mutex waitForUpdateMutex;

    condition_variable mustWaitForFixedUpdateCV;
    condition_variable mustWaitForUpdateCV;

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

    // May only be called from fixedUpdate()
    bool mustWaitForUpdateThread();
    void waitForUpdateThread();
    void haltFixedUpdateThread();
    void resumeFixedUpdateThread();

    // May only be called from Update()
    bool mustWaitForFixedUpdateThread();
    void waitForFixedUpdateThread();
    void haltUpdateThread();
    void resumeUpdateThread();
};


#endif //VKRENDERER_ENGINESYSTEMTHREADINGCONTAINER_H
