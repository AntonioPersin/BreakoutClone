#pragma once
#include "CollisionManager.h"

class Updatable {
public:
    virtual void update() = 0;
};

class Drawable {
public:
    virtual void draw() = 0;
};