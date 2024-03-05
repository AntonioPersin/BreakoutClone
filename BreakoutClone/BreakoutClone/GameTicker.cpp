// GameTicker.cpp
#include "GameTicker.h"

GameTicker::GameTicker(float ticksPerSecond) : tickDuration(1.0f / ticksPerSecond), accumulatedTime(0.0f) {}

bool GameTicker::tick() {
    accumulatedTime += 1.0f / 30.0f; // Assume a fixed time step of X ticks per second

    if (accumulatedTime >= tickDuration) {
        accumulatedTime -= tickDuration;
        return true;
    }

    return false;
}
