#pragma once
#include <vector>
#include <map>
#include <string>
#include "Interfaces.h"
#include "Brick.h"
#include "BreakableBrick.h"
#include "pugixml.hpp"

class Level : public Updatable, public Drawable {
private:
    int& playerScoreRef;
    float startX, startY, padding;
    int bricksX, bricksY;
    bool cleared;
    std::string background;
    std::vector<std::vector<Brick*>> level;
    std::map<char, Brick*> brickTypeMap;
    std::string xmlFilePath;

public:
    Level(int& playerScoreRef, float start_X, float start_Y, std::string xmlFilePath);
    void loadLevelFromXML(std::string xmlFilePath);
    void generateLevelFromLayout(std::string bricksLayout);
    void update() override;
    void draw() override;
    Brick* getBrickAt(int x, int y) const;
    std::vector<std::vector<Brick*>> getLevel() const;
    int getBricksX() const;
    int getBricksY() const;
    bool isCleared() const;
    std::string getBackgroundImage();
};
