#include "Ball.h"
#include <allegro5/allegro_primitives.h>

Ball::Ball(float startX, float startY, float ballRadius, float ballSpeedX, float ballSpeedY)
    : x(startX), y(startY), radius(ballRadius), speedX(ballSpeedX), speedY(ballSpeedY), soundManager() {
    this->startingX = startX;
    this->startingY = startY;
    this->startingSpeedX = ballSpeedX;
    this->startingSpeedY = ballSpeedY;
}

void Ball::update() {
    x += speedX;
    y += speedY;
}

void Ball::draw() {
    al_draw_filled_circle(x, y, radius, al_map_rgb(255, 255, 255));
}

void Ball::handleCollision(CollisionManager collisionManager, char side) {
    // Handle collision based on the side
    switch (side) {
    case 'n':
        reverseYDirection(); // Hit the top edge, reverse Y direction
        break;
    case 's':
        reverseYDirection(); // Hit the bottom edge, reverse Y direction
        break;
    case 'w':
        reverseXDirection(); // Hit the left edge, reverse X direction
        break;
    case 'e':
        reverseXDirection(); // Hit the right edge, reverse X direction
        break;
    default:
        // No collision
        break;
    }
}

void Ball::playCollisionSound(const std::string& soundFilePath) {
    //soundManager.playSound(soundFilePath);
}

float Ball::getX() const {
    return x;
}

float Ball::getY() const {
    return y;
}

float Ball::getRadius() const {
    return radius;
}

void Ball::setSpeed(float ballSpeedX, float ballSpeedY) {
    speedX = ballSpeedX;
    speedY = ballSpeedY;
}

void Ball::reverseXDirection() {
    speedX = -speedX;
}

void Ball::reverseYDirection() {
    speedY = -speedY;
}

void Ball::reset() {
    x = startingX;
    y = startingY;
    speedX = startingSpeedX;
    speedY = startingSpeedY;
}