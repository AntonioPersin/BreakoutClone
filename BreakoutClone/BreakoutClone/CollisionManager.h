#pragma once
#include <vector>
#include <allegro5/allegro_primitives.h>

class Ball;
class Paddle;
class Level;
class Brick;

class CollisionManager {
public:
    static char checkPaddleCollision(Ball* ball, Paddle* paddle);
    static char checkBrickCollision(Ball* ball, Brick* brick);
    static char checkWindowEdgeCollision(Ball* ball, ALLEGRO_DISPLAY* display);
};
