// Game.cpp
#include "Game.h"
#include <allegro5/allegro_primitives.h>
#include "BreakableBrick.h"
#include "GlobalVariables.h"
#include <cmath>
#include <iostream>
#include <random>

int WINDOW_WIDTH = 905;
int WINDOW_HEIGHT = 600;

Game::Game() : display(nullptr), eventQueue(nullptr), font(nullptr), windowX(WINDOW_WIDTH), windowY(WINDOW_HEIGHT), quit(false), 
    gameStarted(false), gamePaused(false), paddle(nullptr), ball(nullptr), ticker(nullptr), level(nullptr), collisionManager() {
    if (!initializeAllegro()) {
        return; // Handle initialization error
    }

    if (!createDisplay()) {
        return; // Handle display creation error
    }

    initializeEventQueue();


    // Create a built-in font
    font = al_create_builtin_font();

    // Check if font creation was successful
    if (!font) {
        std::cerr << "Failed to create built-in font!" << std::endl;
        return;// Handle error
    }
}

Game::~Game() {
    cleanup();
}

void Game::run() {
    
    while (!quit) {
        processEvents(); // Process events outside the tick loop

        if (!gameStarted) {
            drawStartScreen();
            if (startGame()) {
                gameStarted = true;
                resetGame();
            }
        }
        else if (gamePaused){
            al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 
                ALLEGRO_ALIGN_CENTER, "Lost a life, press Space to continue.");
            resetBall();

            flipDisplay();
        }
        else if (playerScore >= 69420) {
            al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 
                ALLEGRO_ALIGN_CENTER, "Time wasted successfully.");
            flipDisplay();
            ALLEGRO_EVENT ev;

            while (al_get_next_event(eventQueue, &ev)) {
                if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                    quit = true;
                }
            }
        }
        else {  
            if (ticker->tick()) {
                updateGame();
                clearScreen();
                drawHUD();
                paddle->draw();
                ball->draw();
                level->draw();
                flipDisplay();
            }
        }
        
    }
}

void Game::processEvents() {
    ALLEGRO_EVENT ev;

    while (al_get_next_event(eventQueue, &ev)) {
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            handleKeyDown(ev);
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            handleKeyUp(ev);
        }
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            quit = true;
        }
    }
}

bool Game::initializeAllegro() {
    if (!al_init()) {
        // Handle initialization error
        return false;
    }

    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();

    return true;
}

bool Game::createDisplay() {
    display = al_create_display(windowX, windowY);
    return display != nullptr;
}

void Game::initializeEventQueue() {
    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));
}

void Game::resetGame() {
    delete level;
    delete ball;
    delete paddle;
    delete ticker;

    std::string filename = "Level_0.xml";

    paddle = new Paddle(450, 550, 100, 20, 0.1f, "sounds/bounce.mp3");
    ball = new Ball(450, 300, 10, 0.05f, -0.05f);
    ticker = new GameTicker(60.0f);
    level = new Level(playerScore, 5.0f, 50.0f, filename);

    playerScore = 0;
    playerLives = 3;
    clearScreen();
    drawHUD();
    paddle->draw();
    ball->draw();
    level->draw();

    //background = al_load_bitmap((level->getBackgroundImage()).c_str());

    flipDisplay();
}

void Game::newLevel()
{
    clearScreen();

    al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f,
        ALLEGRO_ALIGN_CENTER, "New level generating... Complete... Press Space to go to a new level.");

    ALLEGRO_EVENT ev;

    while (al_get_next_event(eventQueue, &ev)) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
            gamePaused = false;
        }
    }

    delete level;
    delete ball;
    delete paddle;

    std::string filename = "Level_";

    std::random_device rd;
    std::mt19937 gen(rd());

    // Generate a random number between 1 and 9
    std::uniform_int_distribution<int> distribution(1, 9);
    int randomNumber = distribution(gen);


    filename += std::to_string(randomNumber) + ".xml";

    std::cout << "New level: " << filename << std::endl;

    paddle = new Paddle(450, 550, 100, 20, 0.1f, "sounds/bounce.mp3");
    ball = new Ball(450, 300, 10, 0.05f, -0.05f);
    level = new Level(playerScore, 5.0f, 50.0f, filename);

    
    drawHUD();
    paddle->draw();
    ball->draw();
    level->draw();

    //background = al_load_bitmap((level->getBackgroundImage()).c_str());

    flipDisplay();
}

void Game::resetBall()
{
    
    ALLEGRO_EVENT ev;

    while (al_get_next_event(eventQueue, &ev)) {
        ball->reset();
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
            gamePaused = false;
        }
    }
}

void Game::clearScreen() {
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Game::flipDisplay() {
    al_flip_display();
}

void Game::handleKeyDown(const ALLEGRO_EVENT& ev) {
    switch (ev.keyboard.keycode) {
    case ALLEGRO_KEY_A:
        paddle->startMovingLeft();
        break;
    case ALLEGRO_KEY_D:
        paddle->startMovingRight();
        break;
    case ALLEGRO_KEY_Q:
        if (gameStarted) {
            gameStarted = false;
            resetGame();
        }
        break;
    }
}

void Game::handleKeyUp(const ALLEGRO_EVENT& ev) {
    switch (ev.keyboard.keycode) {
    case ALLEGRO_KEY_A:
        paddle->stopMovingLeft();
        break;
    case ALLEGRO_KEY_D:
        paddle->stopMovingRight();
        break;
    }
}

void Game::updateGame() {
    paddle->update();
    ball->update();
    char side = '0';

    // Iterate through all bricks in the level
    for (int i = 0; i < level->getBricksX(); ++i) {
        for (int j = 0; j < level->getBricksY(); ++j) {
            Brick* brick = level->getBrickAt(i, j);
            if (brick) {
                side = collisionManager.checkBrickCollision(ball, brick);
                if (side != '0') {
                    ball->handleCollision(collisionManager, side);
                    //ball.playCollisionSound(brick->getHitSound());
                    brick->update();
                }
            }
        }
    }

    level->update();
    if (level->isCleared()) {
        newLevel();
    }

    // Check for paddle collisions
    // Check which side of the paddle was hit
    side = collisionManager.checkPaddleCollision(ball, paddle);
    if (side != '0') {
        ball->handleCollision(collisionManager, side);
    }
    
    // Check for window collisions
    // Check which side of the window was hit
    side = collisionManager.checkWindowEdgeCollision(ball, display);
    switch (side) {
    case 's':
        playerLives--;
        gamePaused = true;
        if (playerLives == 0) {
            gameStarted = false;
        }
        break;
    case '0':
        ;
        break;
    default:
        ball->handleCollision(collisionManager, side);
        break;
    }

    //al_draw_bitmap(background, 0, 0, 0);

}

void Game::drawHUD() const {
    al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, ("Score: " + std::to_string(playerScore)).c_str());
    al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2.0f, 10, ALLEGRO_ALIGN_CENTER, ("Lives: " + std::to_string(playerLives)).c_str());
}

void Game::drawStartScreen() {
    clearScreen();
    //background = al_load_bitmap("images/misc/start_background.jpg");
    //al_draw_bitmap(background, 0, 0, 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2.0f, 300, ALLEGRO_ALIGN_CENTER, "Press SPACE to Start");
    al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2.0f, 320, ALLEGRO_ALIGN_CENTER, "Press ESC to Quit");
    al_draw_text(font, al_map_rgb(255, 255, 255), WINDOW_WIDTH / 2.0f, 20, ALLEGRO_ALIGN_CENTER, ("Previous Score: " + std::to_string(playerScore)).c_str());
    al_flip_display();
}

bool Game::startGame() {
    ALLEGRO_EVENT ev;

    while (al_get_next_event(eventQueue, &ev)) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
            return true;
        }
        else if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            quit = true;
            return false; // Quit the game
        }
    }

    return false;
}

void Game::cleanup() {
    al_destroy_font(font);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);
    al_destroy_bitmap(background);
    delete level;
    delete ball;
    delete paddle;
    delete ticker;
}
