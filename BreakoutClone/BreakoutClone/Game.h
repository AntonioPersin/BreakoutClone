#pragma once
#include "Paddle.h"
#include "Ball.h"
#include "GameTicker.h"
#include "Level.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <memory>
#include "CollisionManager.h"


class Game {
private:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* eventQueue;
    ALLEGRO_FONT* font;
    ALLEGRO_BITMAP* background;
    float windowX, windowY;
    int playerScore, playerLives;
    bool quit, gameStarted, gamePaused;
    Paddle* paddle;
    Ball* ball;
    GameTicker* ticker;
    Level* level;
    CollisionManager collisionManager;


public:
    Game();
    ~Game();
    void run();

private:
    bool initializeAllegro();
    bool createDisplay();
    void initializeEventQueue();
    void processEvents();
    void resetGame();
    void newLevel();
    void resetBall();
    void clearScreen();
    void flipDisplay();
    void updateGame();
    void drawHUD() const;
    void drawStartScreen();
    bool startGame();
    void cleanup();
    void handleKeyDown(const ALLEGRO_EVENT& ev);
    void handleKeyUp(const ALLEGRO_EVENT& ev);
};
