//
// Created by hindrik on 15-2-19.
//

//#define THREAD_DEBUG

#include "EngineSystemThreadingContainer.h"
#include "../../Utilities/Logger.h"

EngineSystemThreadingContainer::EngineSystemThreadingContainer(unique_ptr<EngineSystem>&& ptr) : engineSystem(std::move(ptr)) {
}

EngineSystem &EngineSystemThreadingContainer::getEngineSystem() {
    return *engineSystem;
}

bool EngineSystemThreadingContainer::mustWaitForFixedUpdateThread() {
    return waitForFixedUpdate;
}

void EngineSystemThreadingContainer::haltUpdateThread() {
    //Is called by fixed update thread.

    { //Signal main thread to stop.
      lock_guard<mutex> lock(waitForFixedUpdateMutex);
      waitForFixedUpdate = true;

#ifdef THREAD_DEBUG
    Logger::warn("[FixedUpdate Thread] Send signal to update thread to wait.");
#endif
    }

#ifdef THREAD_DEBUG
    Logger::warn("[FixedUpdate Thread] Waiting for update thread.");
#endif
    //Now we wait for signal from the update thread here.
    {
        unique_lock<mutex> lock(waitForUpdateMutex);
        mustWaitForUpdateCV.wait(lock, [&]{ return waitForUpdate; });
        waitForUpdate = false;

#ifdef THREAD_DEBUG
        Logger::warn("[FixedUpdate Thread] Processing can begin.");
#endif
    }
    //We can do our tasks now.
}

void EngineSystemThreadingContainer::resumeUpdateThread() {
    //Is called by fixed update thread.

#ifdef THREAD_DEBUG
    Logger::warn("[FixedUpdate Thread] Resuming update thread.");
#endif

    lock_guard<mutex> lock(waitForFixedUpdateMutex);
    waitForFixedUpdate = true;
    mustWaitForFixedUpdateCV.notify_one();
}

void EngineSystemThreadingContainer::waitForFixedUpdateThread() {
    //Is called by update thread

    waitForFixedUpdate = false;
    {
        lock_guard<mutex> lock(waitForUpdateMutex);
        waitForUpdate = true;
    }
    //Notify fixed update thread.
    mustWaitForUpdateCV.notify_one();

#ifdef THREAD_DEBUG
    Logger::warn("[Update Thread] Notified fixedUpdate thread.");
    Logger::warn("[Update Thread] Waiting on fixedUpdate thread to complete job.");
#endif

    //Wait for fixed update thread to complete work
    {
        unique_lock<mutex> lock(waitForFixedUpdateMutex);
        mustWaitForFixedUpdateCV.wait(lock, [&]{ return waitForFixedUpdate; });
        waitForFixedUpdate = false;
    }

#ifdef THREAD_DEBUG
    Logger::warn("[Update Thread] Resumed Update thread.");
#endif
}

bool EngineSystemThreadingContainer::mustWaitForUpdateThread() {
    return waitForUpdate;
}

void EngineSystemThreadingContainer::haltFixedUpdateThread() {

    //Is called by update thread.

    { //Signal fixed update thread to stop.
        lock_guard<mutex> lock(waitForUpdateMutex);
        waitForUpdate = true;

#ifdef THREAD_DEBUG
        Logger::warn("[Update Thread] Send signal to fixedUpdate thread to wait.");
#endif
    }

#ifdef THREAD_DEBUG
    Logger::warn("[Update Thread] Waiting for fixedUpdate thread.");
#endif
    //Now we wait for signal from the fixedUpdate thread here.
    {
        unique_lock<mutex> lock(waitForFixedUpdateMutex);
        mustWaitForFixedUpdateCV.wait(lock, [&]{ return waitForFixedUpdate; });
        waitForFixedUpdate = false;

#ifdef THREAD_DEBUG
        Logger::warn("[Update Thread] Processing can begin.");
#endif
    }
    //We can do our tasks now.
}

void EngineSystemThreadingContainer::resumeFixedUpdateThread() {
    //Is called by update thread.

#ifdef THREAD_DEBUG
    Logger::warn("[Update Thread] Resuming fixedUpdate thread.");
#endif

    lock_guard<mutex> lock(waitForUpdateMutex);
    waitForUpdate = true;
    mustWaitForUpdateCV.notify_one();
}

void EngineSystemThreadingContainer::waitForUpdateThread() {
    //Is called by fixedUpdate thread

    waitForUpdate = false;
    {
        lock_guard<mutex> lock(waitForFixedUpdateMutex);
        waitForFixedUpdate = true;
    }
    //Notify update thread.
    mustWaitForFixedUpdateCV.notify_one();

#ifdef THREAD_DEBUG
    Logger::warn("[FixedUpdate Thread] Notified update thread.");
    Logger::warn("[FixedUpdate Thread] Waiting on update thread to complete job.");
#endif

    //Wait for update thread to complete work
    {
        unique_lock<mutex> lock(waitForUpdateMutex);
        mustWaitForUpdateCV.wait(lock, [&]{ return waitForUpdate; });
        waitForUpdate = false;
    }

#ifdef THREAD_DEBUG
    Logger::warn("[FixedUpdate Thread] Resumed fixedUpdate thread.");
#endif
}