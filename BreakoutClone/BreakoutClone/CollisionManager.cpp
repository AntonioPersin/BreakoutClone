#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "CollisionManager.h"
#include <allegro5/allegro.h>
#include <cmath>

char CollisionManager::checkPaddleCollision(Ball* ball, Paddle* paddle) {
    float dx = ball->getX() - std::max(paddle->getX(), std::min(ball->getX(), paddle->getX() + paddle->getWidth()));
    float dy = ball->getY() - std::max(paddle->getY(), std::min(ball->getY(), paddle->getY() + paddle->getHeight()));

    if ((dx * dx + dy * dy) < (ball->getRadius() * ball->getRadius())) {
        float angle = atan2(dy, dx);
        if (angle > -0.785 && angle <= 0.785)
            return 'e'; // Collision on the right side
        else if (angle > 0.785 && angle <= 3 * 0.785)
            return 's'; // Collision on the bottom side
        else if (angle > -3 * 0.785 && angle <= -0.785)
            return 'n'; // Collision on the top side
        else
            return 'w'; // Collision on the left side
    }
    // No collision with the paddle
    return '0';
}

char CollisionManager::checkBrickCollision(Ball* ball, Brick* brick) {
    float dx = ball->getX() - std::max(brick->getX(), std::min(ball->getX(), brick->getX() + brick->getWidth()));
    float dy = ball->getY() - std::max(brick->getY(), std::min(ball->getY(), brick->getY() + brick->getHeight()));

    if ((dx * dx + dy * dy) < (ball->getRadius() * ball->getRadius())) {
        float angle = atan2(dy, dx);
        if (angle > -0.785 && angle <= 0.785)
            return 'e'; // Collision on the right side
        else if (angle > 0.785 && angle <= 3 * 0.785)
            return 's'; // Collision on the bottom side
        else if (angle > -3 * 0.785 && angle <= -0.785)
            return 'n'; // Collision on the top side
        else
            return 'w'; // Collision on the left side
    }
    // No collision with the paddle
    return '0';
}

char CollisionManager::checkWindowEdgeCollision(Ball* ball, ALLEGRO_DISPLAY* display) {
    // Get the dimensions of the display
    int windowWidth = al_get_display_width(display);
    int windowHeight = al_get_display_height(display);

    // Check for collision with window edges
    if (ball->getX() - ball->getRadius() < 0) {
        // Ball hit the left edge
        return 'w';
    }

    if (ball->getX() + ball->getRadius() > windowWidth) {
        // Ball hit the right edge
        return 'e';
    }

    if (ball->getY() - ball->getRadius() < 0) {
        // Ball hit the top edge
        return 'n';
    }

    if (ball->getY() + ball->getRadius() > windowHeight) {
        // Ball hit the bottom edge
        return 's';
    }

    // No collision with window edges
    return '0';
}
