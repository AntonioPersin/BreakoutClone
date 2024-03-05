#pragma once
#include "Interfaces.h"
#include "SoundManager.h"
#include <string>
#include <allegro5/allegro_image.h>

class Ball : public Updatable, public Drawable {
private:
    float x, y, startingX, startingY;
    float radius;
    float speedX, speedY, startingSpeedX, startingSpeedY;
    ALLEGRO_BITMAP* image;
    SoundManager soundManager;

public:
    Ball(float startX, float startY, float ballRadius, float ballSpeedX, float ballSpeedY);
    virtual void update() override;
    virtual void draw() override;
    void handleCollision(CollisionManager collisionManager, char side = '0');
    float getX() const;
    float getY() const;
    float getRadius() const;
    void setSpeed(float ballSpeedX, float ballSpeedY);
    void reverseXDirection();
    void reverseYDirection();
    void playCollisionSound(const std::string& soundFilePath);
    void reset();
};