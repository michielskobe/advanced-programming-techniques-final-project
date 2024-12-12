#include "gamecontroller.h"

QLoggingCategory gameControllerCat("gameController");

GameController::GameController(){
    initialGameLoad();
    connectSlots();
    emit updateUI();
}

GameController* GameController::gameController= nullptr;

GameController *GameController::GetInstance()
{
    if(gameController==nullptr){
        gameController = new GameController();
    }
    return gameController;
}

std::shared_ptr<int> GameController::getActiveLevelIndex() const
{
    return activeLevelIndex;
}

void GameController::setActiveLevelIndex(int newActiveLevelIndex)
{
    *activeLevelIndex = newActiveLevelIndex;
}

float GameController::getActiveProtagonistHealth() const
{
    return (*levels)[*activeLevelIndex]->getProtagonistHealth();
}

float GameController::getActiveProtagonistEnergy() const
{
    return (*levels)[*activeLevelIndex]->getProtagonistEnergy();
}

/*
 * Move the protagonist relatively in the active level
 * This also updates the energy of the protagonist, since movement has a cost associated with it
 */
void GameController::moveProtagonistRelative(int relativeX, int relativeY)
{
    qCInfo(gameControllerCat) << "Moving the player relatively: x=" << relativeX << " y=" << relativeY;
    // Move the protagonist
    (*levels)[*activeLevelIndex]->moveProtagonistRelative(relativeX, relativeY);

    // get the value of the destination tile
    float tileEnergy = (*levels)[*activeLevelIndex]->getTileValue((*levels)[*activeLevelIndex]->protagonist->getXPos(), (*levels)[*activeLevelIndex]->protagonist->getYPos());
    tileEnergy = 1/tileEnergy; // invert the tile value

    tileEnergy = tileEnergy * 0.2; // Make the game more easy TODO: Make difficulty modes for this if there is time

    // update energy based on movement
    (*levels)[*activeLevelIndex]->setProtagonistEnergy(((*levels)[*activeLevelIndex]->getProtagonistEnergy())-tileEnergy);
}

/*
 * Move the protagonist absolutely in the active level
 * This does NOT update the energy of the protagonist
 */
void GameController::moveProtagonistAbsolute(int absoluteX, int absoluteY)
{
    qCInfo(gameControllerCat) << "Moving the player absolutely: x=" << absoluteX << " y=" << absoluteY;
    (*levels)[*activeLevelIndex]->moveProtagonistAbsolute(absoluteX, absoluteY);
}


void GameController::initialGameLoad()
{
    qCInfo(gameControllerCat) << "Performing initial game load.";
    activeLevelIndex = std::make_shared<int>(0);
    // get levels from GameGenerator;
    std::vector<QString> fileNames;
    fileNames.push_back(":/images/world_images/worldmap.png");
    fileNames.push_back(":/images/world_images/maze2.png");

    LevelManager* levelManager = LevelManager::GetInstance();
    levelManager->setLevels(fileNames);
    levels = levelManager->getLevels();
}

void GameController::connectSlots()
{
    // connect protagonist position change signal to game controller
    for (int i = 0; i < (int)(*levels).size(); i++) {
        QObject::connect(&(*((*levels)[i]->protagonist)), &Protagonist::posChanged, this, &GameController::protagonistPositionUpdated);
    }
}

void GameController::protagonistPositionUpdated(int xPos, int yPos)
{
    qCInfo(gameControllerCat) << "Detected new protagonist location: x=" << xPos << " y=" << yPos;
    //protagonistView->renderModel(xPos,yPos);
    emit updateUI();
}
