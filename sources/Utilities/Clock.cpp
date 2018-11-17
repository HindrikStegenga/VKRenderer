//
// Created by Hindrik  Stegenga on 08/04/2018.
//

#include "Clock.h"

std::chrono::nanoseconds Clock::getDeltaTime() {
    const auto current = std::chrono::steady_clock::now();
    const auto elapsed = current - previousFrame;

    previousFrame = current;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed);
}