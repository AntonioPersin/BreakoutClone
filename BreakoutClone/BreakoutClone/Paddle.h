#pragma once
#include "Interfaces.h"
#include <string>
#include <allegro5/allegro_image.h>

class CollisionManager;

class Paddle : public Updatable, public Drawable {
private:
    float x, y;
    float width, height;
    float speed;
    bool moveLeft;
    bool moveRight;
    std::string bounceSound;
    ALLEGRO_BITMAP* image;

public:
    Paddle(float startX, float startY, float paddleWidth, float paddleHeight, float paddleSpeed, const std::string& sound);
    
    void startMovingLeft();
    void stopMovingLeft();
    void startMovingRight();
    void stopMovingRight();
    virtual void update() override;
    virtual void draw() override;
    void handleCollision(CollisionManager collisionManager, char side = '0');
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    std::string getBounceSound() const;
};