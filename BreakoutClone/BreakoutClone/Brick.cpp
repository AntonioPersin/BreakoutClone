#include "Brick.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>


float DEFAULT_BRICK_WIDTH = 40.0f;
float DEFAULT_BRICK_HEIGHT = 10.0f;


Brick::Brick(float posX, float posY, char brickId, const std::string& brickTexture, const std::string& brickHitSound)
    : x(posX), y(posY), width(DEFAULT_BRICK_WIDTH), height(DEFAULT_BRICK_HEIGHT), id(brickId), destroyed(false), texture(brickTexture), hitSound(brickHitSound) {
    //image = al_load_bitmap(texture.c_str());
}

Brick::~Brick()
{
    //al_destroy_bitmap(image);
}

void Brick::update(){
    //std::cout << "Bounce sound." << std::endl;
}

void Brick::draw() {
    //If it's a regular Brick class it's invincible one
    //al_draw_bitmap(image, x, y, 0);
    al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(150, 150, 150));
}

void Brick::handleCollision(CollisionManager collisionManager, char side)
{
    //Sound etc.
}

bool Brick::isDestroyed() const
{
    return destroyed;
}

char Brick::getId()
{
    return id;
}

float Brick::getWidth() const {
    return width;
}

float Brick::getHeight() const {
    return height;
}

float Brick::getX() const {
    return x;
}

float Brick::getY() const {
    return y;
}

void Brick::updatePosition(int newX, int newY) {
    x = newX;
    y = newY;
}

std::string Brick::getTexture()
{
    return texture;
}

std::string Brick::getHitSound()
{
    return hitSound;
}
