#pragma once

class GameTicker {
private:
    float tickDuration;
    float accumulatedTime;

public:
    GameTicker(float ticksPerSecond);
    bool tick();
};
