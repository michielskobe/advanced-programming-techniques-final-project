#include "gamecontroller.h"

GameController::GameController() {}


void GameController::initialGameLoad()
{
    // get levels from GameGenerator;
    std::vector<std::string> fileNames;
    fileNames.push_back(":/images/world_images/maze1.png");
    fileNames.push_back(":/images/world_images/maze2.png");

    GameGenerator generator = GameGenerator(fileNames);
    levels = generator.getLevels();
}
