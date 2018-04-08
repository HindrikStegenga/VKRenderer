//
// Created by Hindrik  Stegenga on 08/04/2018.
//

#ifndef VKRENDERER_CLOCK_H
#define VKRENDERER_CLOCK_H


#include <chrono>

class Clock final {
private:
    std::chrono::time_point<std::chrono::steady_clock> previousFrame;
public:
    std::chrono::nanoseconds getDeltaTime();

};

#endif //VKRENDERER_CLOCK_H
