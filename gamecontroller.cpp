#include "gamecontroller.h"

QLoggingCategory gameControllerCat("gameController");

GameController::GameController() {
    initialGameLoad();
}

void GameController::moveProtagonistRelative(int relativeX, int relativeY)
{
    qCInfo(gameControllerCat) << "Moving the player relatively: x=" << relativeX << " y=" << relativeY;
}


void GameController::initialGameLoad()
{
    qCInfo(gameControllerCat) << "Performing initial game load.";
    // get levels from GameGenerator;
    std::vector<QString> fileNames;
    fileNames.push_back(":/images/world_images/maze1.png");
    fileNames.push_back(":/images/world_images/maze2.png");

    GameGenerator generator = GameGenerator(fileNames);
    levels = generator.getLevels();
}
