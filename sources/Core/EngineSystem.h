//
// Created by hindrik on 6-2-19.
//

#ifndef VKRENDERER_ENGINESYSTEM_H
#define VKRENDERER_ENGINESYSTEM_H

#include <string>
#include <vector>
#include <chrono>

using std::vector;
using std::string;
using std::chrono::nanoseconds;

class EngineSystem {
public:
    EngineSystem() = default;
    virtual ~EngineSystem() = 0;

    EngineSystem(const EngineSystem&) = delete;
    EngineSystem(EngineSystem&&) = default;

    EngineSystem& operator=(const EngineSystem&) = delete;
    EngineSystem& operator=(EngineSystem&&) = default;
public:
    //Update function for dynamic updates
    virtual void update(std::chrono::nanoseconds deltaTime) = 0;

    //Function for getting status. Is called before fixedUpdate();
    virtual bool getSystemStatus() = 0;

    //Update function for fixed time updates and event handling
    virtual void fixedUpdate() = 0;
};

#endif //VKRENDERER_ENGINESYSTEM_H
