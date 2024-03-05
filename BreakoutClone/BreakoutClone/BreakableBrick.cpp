// BreakableBrick.cpp
#include "BreakableBrick.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

BreakableBrick::BreakableBrick(int& playerScoreRef, float posX, float posY, char brickId, const std::string& brickTexture,
    const std::string& brickHitSound, const std::string& brickBreakSound,
    int brickBreakScore, int brickHitPoints)
    : Brick(posX, posY, brickId, brickTexture, brickHitSound), playerScoreRef(playerScoreRef), hitPoints(brickHitPoints), breakSound(brickBreakSound),
    breakScore(brickBreakScore) {
    //image = al_load_bitmap(texture.c_str());
}

void BreakableBrick::draw()
{
    //switch-case depending on HP
    switch (hitPoints) {
    case 1:
        //image = al_load_bitmap("images/bricks/green_brick.jpg");
        al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(0, 255, 0));
        break;
    case 2:
        //image = al_load_bitmap("images/bricks/yellow_brick.jpg");
        al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(255, 255, 0));
        break;
    case 3:
        //image = al_load_bitmap("images/bricks/red_brick.jpg");
        al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(255, 0, 0));
        break;
    default:
        Brick::draw();
    }
    //al_draw_bitmap(image, x, y, 0);
}

void BreakableBrick::update(){
    hitPoints--;
    if (hitPoints == 0) {
        markToDestroy();
        playerScoreRef += breakScore;
    }
    else {
        Brick::update();
    }
}

void BreakableBrick::markToDestroy()
{
    this->destroyed = true;
}

std::string BreakableBrick::getBreakSound()
{
    return breakSound;
}

int BreakableBrick::getBreakScore()
{
    return breakScore;
}

int BreakableBrick::getHitPoints()
{
    return hitPoints;
}
