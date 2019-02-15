//
// Created by hindrik on 15-2-19.
//

#define THREAD_DEBUG 0

#include "EngineSystemThreadingContainer.h"
#include "../Utilities/Logger.h"

EngineSystemThreadingContainer::EngineSystemThreadingContainer(unique_ptr<EngineSystem>&& ptr) : engineSystem(std::move(ptr)) {
}

EngineSystem &EngineSystemThreadingContainer::getEngineSystem() {
    return *engineSystem;
}

bool EngineSystemThreadingContainer::mustWaitForFixedUpdate() {
    return waitForFixedUpdate;
}

void EngineSystemThreadingContainer::haltUpdateThread() {
    //Is called by fixed update thread.

    { //Signal main thread to stop.
      lock_guard<mutex> lock(waitOnFixedMutex);
      waitForFixedUpdate = true;

#ifdef THREAD_DEBUG
    Logger::log("[Fixed] Send signal to main thread to wait.");
#endif
    }

#ifdef THREAD_DEBUG
    Logger::log("[Fixed] Waiting for main thread.");
#endif
    //Now we wait for signal from the main thread here.
    {
        unique_lock<mutex> lock(waitOnMainMutex);
        mustWaitOnMainCV.wait(lock, [&]{ return waitForUpdate; });
        waitForUpdate = false;

#ifdef THREAD_DEBUG
        Logger::log("[Fixed] Processing can begin.");
#endif
    }
    //We can do our tasks now.
}

void EngineSystemThreadingContainer::resumeUpdateThread() {
    //Is called by fixed update thread.

#ifdef THREAD_DEBUG
    Logger::log("[Fixed] Resuming main thread.");
#endif

    lock_guard<mutex> lock(waitOnFixedMutex);
    waitForFixedUpdate = true;
    mustWaitOnFixedCV.notify_one();
}

void EngineSystemThreadingContainer::waitForFixedUpdateThread() {
    //Is called by main thread

    waitForFixedUpdate = false;
    {
        lock_guard<mutex> lock(waitOnMainMutex);
        waitForUpdate = true;
    }
    //Notify fixed update thread.
    mustWaitOnMainCV.notify_one();

#ifdef THREAD_DEBUG
    Logger::log("[Main] Waited on fixedUpdate thread. Notified fixed thread.");
    Logger::log("[Main] Waiting on fixedUpdate thread to complete job.");
#endif

    //Wait for fixed update thread to complete work
    {
        unique_lock<mutex> lock(waitOnFixedMutex);
        mustWaitOnFixedCV.wait(lock, [&]{ return waitForFixedUpdate; });
        waitForFixedUpdate = false;
    }

#ifdef THREAD_DEBUG
    Logger::log("[Main] Resumed main thread.");
#endif
}



bool EngineSystemThreadingContainer::mustWaitForUpdateThread() {
    return false;
}

void EngineSystemThreadingContainer::waitForUpdateThread() {

}

void EngineSystemThreadingContainer::haltFixedUpdateThread() {

}

void EngineSystemThreadingContainer::resumeFixedUpdateThread() {

}


