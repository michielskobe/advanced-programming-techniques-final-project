#include "gamecontroller.h"

GameController::GameController() {
    initialGameLoad();
}


void GameController::initialGameLoad()
{
    // get levels from GameGenerator;
    std::vector<QString> fileNames;
    fileNames.push_back(":/images/world_images/maze1.png");
    fileNames.push_back(":/images/world_images/maze2.png");

    GameGenerator generator = GameGenerator(fileNames);
    levels = generator.getLevels();
}
