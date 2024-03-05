#include "Level.h"
#include <allegro5/allegro_primitives.h>
#include <iostream>

Level::Level(int& playerScoreRef, float start_X, float start_Y, std::string xmlFilePath)
    : playerScoreRef(playerScoreRef), startX(start_X), startY(start_Y), cleared(false), xmlFilePath(xmlFilePath), brickTypeMap() {
    loadLevelFromXML(xmlFilePath);
}

void Level::loadLevelFromXML(std::string xmlFilePath) {
    pugi::xml_document doc;
    if (!doc.load_file(xmlFilePath.c_str())) {
        // Failed to load XML file
        return;
    }

    pugi::xml_node levelNode = doc.child("Level");
    if (!levelNode) {
        // Invalid XML format
        return;
    }

    // Read level attributes
    bricksX = levelNode.attribute("ColumnCount").as_int();
    bricksY = levelNode.attribute("RowCount").as_int();
    padding = levelNode.attribute("Padding").as_float();
    background = levelNode.attribute("BackgroundTexture").as_string();

    // Read brick types
    pugi::xml_node brickTypesNode = levelNode.child("BrickTypes");
    for (pugi::xml_node brickTypeNode = brickTypesNode.child("BrickType"); brickTypeNode; brickTypeNode = brickTypeNode.next_sibling("BrickType")) {
        char id = brickTypeNode.attribute("Id").as_string()[0];
        std::string texture = brickTypeNode.attribute("Texture").as_string();
        std::string hitSound = brickTypeNode.attribute("HitSound").as_string();

        // Create and store brick object
        if (id != 'I') {
            // For bricks other than 'I' (invincible), create BreakableBrick objects
            int hitPoints = brickTypeNode.attribute("HitPoints").as_int();
            std::string breakSound = brickTypeNode.attribute("BreakSound").as_string();
            int breakScore = brickTypeNode.attribute("BreakScore").as_int();

            Brick* brick = new BreakableBrick(playerScoreRef, 0, 0, id, texture, hitSound, breakSound, breakScore, hitPoints);
            brickTypeMap[id] = brick;
        }
        else {
            // For invincible bricks ('I'), create Brick objects without hit points, break sound, and break score
            Brick* brick = new Brick(0, 0, id, texture, hitSound);
            brickTypeMap[id] = brick;
        }
    }

    // Read bricks layout
    pugi::xml_node bricksNode = levelNode.child("Bricks");
    std::string bricksLayout = bricksNode.text().as_string();

    // Process bricks layout and create bricks
    generateLevelFromLayout(bricksLayout);
}

void Level::generateLevelFromLayout(std::string bricksLayout) {
    level.clear(); // Clear existing data
    float currPosX = startX;
    float currPosY = startY;

    bricksLayout.erase(std::remove_if(bricksLayout.begin(), bricksLayout.end(), [](char c) {
        return c == ' ' || c == '\n' || c == '\r';
    }), bricksLayout.end());

    //Resize vectors beforehand
    level.resize(bricksX);
    for (auto& col : level) {
        col.resize(bricksY, nullptr); // Initialize all elements in each row to nullptr
    }

    //Get dimensions of bricks 
    float brickWidth = 0;
    float brickHeight = 0;
    auto iter = brickTypeMap.begin();
    if (iter != brickTypeMap.end()) {
        Brick* brick = iter->second;
        brickWidth = brick->getWidth();
        brickHeight = brick->getHeight();
    }
    
    for (int i = 0; i < bricksX; ++i) {
        for (int j = 0; j < bricksY; ++j) {
            char lookupId = bricksLayout[j * bricksX + i];
            auto iter = brickTypeMap.find(lookupId);
            if (iter != brickTypeMap.end()) {
                Brick* brick = iter->second;
                if (lookupId == 'I') {
                    level[i][j] = new Brick(currPosX, currPosY, brick->getId(), brick->getTexture(), brick->getHitSound());
                }
                else {
                    BreakableBrick* breakableBrick = dynamic_cast<BreakableBrick*>(brick);
                    level[i][j] = new BreakableBrick(playerScoreRef, currPosX, currPosY, breakableBrick->getId(), breakableBrick->getTexture(),
                        breakableBrick->getHitSound(), breakableBrick->getBreakSound(), breakableBrick->getBreakScore(), breakableBrick->getHitPoints());
                }
            }
            currPosY += brickHeight + padding;
        }
        currPosX += brickWidth + padding;
        currPosY = startY;
    }
}

void Level::update() {
    if (!level.empty()) {
        bool anyBreakableBricksLeft = false;
        // Iterate through the level
        for (int i = 0; i < bricksX; ++i) {
            for (int j = 0; j < bricksY; ++j) {
                Brick* currentBrick = level[i][j];
                if (currentBrick && dynamic_cast<BreakableBrick*>(currentBrick)) {
                    anyBreakableBricksLeft = true;
                    if (currentBrick->isDestroyed()) {
                        level[i][j] = nullptr; // Remove destroyed BreakableBrick
                    }
                }
            }
        }
        if (!anyBreakableBricksLeft) {
            cleared = true;
        }
    }
}

void Level::draw() {
    if (!level.empty()) {
        for (int i = 0; i < bricksX; ++i) {
            for (int j = 0; j < bricksY; ++j) {
                if (level[i][j]) {
                    level[i][j]->draw();
                }
            }
        }
    }
}

Brick* Level::getBrickAt(int x, int y) const {
    if (x >= 0 && x < level.size() && y >= 0 && y < level[x].size()) {
        return level[x][y];
    }
    else {
        return nullptr; // Return nullptr if coordinates are out of bounds
    }
}

std::vector<std::vector<Brick*>> Level::getLevel() const {
    return level;
}

int Level::getBricksX() const {
    return bricksX;
}

int Level::getBricksY() const {
    return bricksY;
}

bool Level::isCleared() const
{
    return cleared;
}

std::string Level::getBackgroundImage()
{
    return background;
}
