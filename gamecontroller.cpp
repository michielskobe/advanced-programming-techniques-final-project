#include "gamecontroller.h"

QLoggingCategory gameControllerCat("gameController");

GameController::GameController() {
    initialGameLoad();
    connectSlots();
}

/*
 * Move the protagonist relatively in the active level
 */
void GameController::moveProtagonistRelative(int relativeX, int relativeY)
{
    qCInfo(gameControllerCat) << "Moving the player relatively: x=" << relativeX << " y=" << relativeY;
    levels[activeLevelIndex]->moveProtagonistRelative(relativeX, relativeY);
}

/*
 * Move the protagonist absolutely in the active level
 */
void GameController::moveProtagonistAbsolute(int absoluteX, int absoluteY)
{
    qCInfo(gameControllerCat) << "Moving the player absolutely: x=" << absoluteX << " y=" << absoluteY;
    levels[activeLevelIndex]->moveProtagonistRelative(absoluteX, absoluteY);
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

void GameController::connectSlots()
{
    // connect protagonist position change signal to game controller
    for (int i = 0; i < (int)levels.size(); i++) {
        QObject::connect(&(*(levels[i]->protagonist)), &Protagonist::posChanged, this, &GameController::protagonistPositionUpdated);
    }
}

void GameController::protagonistPositionUpdated(int xPos, int yPos)
{
    qCInfo(gameControllerCat) << "Detected new protagonist location: x=" << xPos << " y=" << yPos;
}
