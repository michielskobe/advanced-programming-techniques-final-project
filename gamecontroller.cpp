#include "gamecontroller.h"

QLoggingCategory gameControllerCat("gameController");

GameController::GameController(){
    initialGameLoad();
    connectSlots();
    emit updateUI();
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
    // update energy based on movement
    (*levels)[*activeLevelIndex]->setProtagonistEnergy((*levels)[*activeLevelIndex]->getProtagonistEnergy()-2.0f);
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
    fileNames.push_back(":/images/world_images/maze1.png");
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
