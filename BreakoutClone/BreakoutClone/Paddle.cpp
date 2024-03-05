// Paddle.cpp
#include "Paddle.h"
#include "GlobalVariables.h"
#include <allegro5/allegro_primitives.h>

Paddle::Paddle(float startX, float startY, float paddleWidth, float paddleHeight, float paddleSpeed, const std::string& sound)
    : x(startX), y(startY), width(paddleWidth), height(paddleHeight), speed(paddleSpeed), moveLeft(false), moveRight(false), bounceSound(sound) {}

void Paddle::startMovingLeft() {
    moveLeft = true;
}

void Paddle::stopMovingLeft() {
    moveLeft = false;
}

void Paddle::startMovingRight() {
    moveRight = true;
}

void Paddle::stopMovingRight() {
    moveRight = false;
}

void Paddle::update() {
    if (moveLeft) {
        x -= speed;
        if (x < 0) {
            x = 0;
        }
    }

    if (moveRight) {
        x += speed;
        if (x + width > WINDOW_WIDTH) { // Adjust the screen width accordingly
            x = WINDOW_WIDTH - width;
        }
    }
}

void Paddle::draw() {
    al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(255, 255, 255));
}

void Paddle::handleCollision(CollisionManager collisionManager, char side)
{
}

float Paddle::getX() const {
    return x;
}

float Paddle::getY() const {
    return y;
}

float Paddle::getWidth() const {
    return width;
}

float Paddle::getHeight() const {
    return height;
}

std::string Paddle::getBounceSound() const {
    return bounceSound;
}