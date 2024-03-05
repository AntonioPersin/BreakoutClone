// Brick.h
#pragma once
#include "Interfaces.h"
#include <string>
#include <allegro5/allegro_image.h>

class CollisionManager;

class Brick : public Updatable, public Drawable{
protected:
    float x, y;
    float width, height;
    char id;
    bool destroyed;
    std::string texture;
    std::string hitSound;
    ALLEGRO_BITMAP* image;


public:
    Brick(float posX, float posY, char brickId, const std::string& brickTexture, const std::string& brickHitSound);
    ~Brick();
    float getWidth() const;
    float getHeight() const;
    virtual void update() override;
    virtual void draw() override;
    void handleCollision(CollisionManager collisionManager, char side = '0');
    bool isDestroyed() const;
    char getId();
    float getX() const;
    float getY() const;
    void updatePosition(int newX, int newY);
    std::string getTexture();
    std::string getHitSound();
};