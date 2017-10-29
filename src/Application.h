//
// Created by Hindrik Stegenga on 29-10-17.
//

#ifndef VKRENDERER_APPLICATION_H
#define VKRENDERER_APPLICATION_H

#include "CommonInclude.h"

class Application final {
public:
    Application();
    ~Application() = default;

    Application(const Application&) = default;
    Application(Application&&) = default;

    Application& operator= (const Application&) = default;
    Application& operator= (Application&&) = default;
public:
    void run();
    void stop();
private:
    string applicationName;
    bool   mustStop = false;
};


#endif //VKRENDERER_APPLICATION_H
