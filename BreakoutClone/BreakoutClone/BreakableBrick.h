#pragma once
#include "Brick.h"

class BreakableBrick : public Brick {
private:
    int hitPoints;
    std::string breakSound;
    int breakScore;
    int& playerScoreRef;

public:
    BreakableBrick(int& playerScoreRef, float posX, float posY, char brickId, const std::string& brickTexture,
        const std::string& brickHitSound, const std::string& brickBreakSound,
        int brickBreakScore, int brickHitPoints);
    virtual void draw() override;
    virtual void update() override;
    void markToDestroy();
    std::string getBreakSound();
    int getBreakScore();
    int getHitPoints();
};