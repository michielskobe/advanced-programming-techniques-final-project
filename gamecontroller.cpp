#include "gamecontroller.h"
#include "pathfinderhelper.h"
#include "xenemy.h"

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

bool GameController::calculateValidMove(const int absoluteX, const int absoluteY)
{
    qCInfo(gameControllerCat) << "Checking move validity of tile x=" << absoluteX << " y=" << absoluteY;
    // we assume a move is valid, and perform checks to (dis)prove this
    bool isValidMove = true;

    // Check for a PEnemy on a destination tile.
    if(tileContainsPEnemy(absoluteX, absoluteY)){
        isValidMove = false;
        // Attack the enemy
        attackPEnemy(absoluteX, absoluteY);
    }

    return isValidMove;
}

bool GameController::tileContainsPEnemy(const int absoluteX, const int absoluteY)
{
    bool containsPEnemy = false; // we assume there is no enemy, and perform checks to (dis)prove this
    for (int i = 0; i < (int)((*levels)[*activeLevelIndex]->enemies).size(); i++) {
        auto reference = (&(*((*levels)[*activeLevelIndex]->enemies[i])));
        auto temp = dynamic_cast<PEnemy*>(reference);
        if (temp != nullptr){
            // succesfully casted to a PEnemy at runtime
            // check if it is at the right place
            if (temp->getXPos() == absoluteX && temp->getYPos() == absoluteY){
                // found a PEnemy at the targetposition
                containsPEnemy = true;
            }
        }
    }
    return containsPEnemy;
}

void GameController::healthPackLogic(const int absoluteX, const int absoluteY)
{
    for (int i = 0; i < (int)((*levels)[*activeLevelIndex]->healthPacks).size(); i++) {
        auto reference = (&(*((*levels)[*activeLevelIndex]->healthPacks[i])));
        if (reference->getXPos() == absoluteX && reference->getYPos() == absoluteY){
            qCInfo(gameControllerCat) << "Healthpack detected";
            // Set stats to max
            (*levels)[*activeLevelIndex]->setProtagonistEnergy(100.f);
            (*levels)[*activeLevelIndex]->setProtagonistHealth(100.f);

            // Remove healthpack
            (*levels)[*activeLevelIndex]->healthPacks.erase((*levels)[*activeLevelIndex]->healthPacks.begin()+i);
        }
    }
}

void GameController::PoisonTileLogic(const int absoluteX, const int absoluteY)
{

}

bool GameController::attackPEnemy(const int absoluteX, const int absoluteY)
{
    qCInfo(gameControllerCat) << "Attacking PEnemy";
    for (int i = 0; i < (int)((*levels)[*activeLevelIndex]->enemies).size(); i++) {
        auto reference = (&(*((*levels)[*activeLevelIndex]->enemies[i])));
        auto temp = dynamic_cast<PEnemy*>(reference);
        if (temp != nullptr){
            // succesfully casted to a PEnemy at runtime
            // check if it is at the right place
            if (temp->getXPos() == absoluteX && temp->getYPos() == absoluteY){
                if(!temp->getDefeated()){ // check if the enemy is still alive
                    float newPLevel = temp->getPoisonLevel() - 10.0f; // TODO: this can change with dificulty level (hopefully)
                    (*levels)[*activeLevelIndex]->setProtagonistHealth((*levels)[*activeLevelIndex]->getProtagonistHealth() -10.0f);
                    temp->setPoisonLevel(newPLevel);
                    temp->poison();
                    setPoisonTiles(absoluteX, absoluteY, 2);
                    if(newPLevel <= 0.0f){
                        temp->setDefeated(true);
                    }
                } else {
                    qCInfo(gameControllerCat) << "Turns out PEnemy is dead ¯\_(ツ)_/¯";
                }
            }
        }
    }
    return true;
}

void GameController::setPoisonTiles(const int centerX, const int centerY, const int radius)
{
    const int centerIndex = centerX + centerY * (*levels)[*activeLevelIndex]->cols;
    std::vector<int> indexes;
    indexes.reserve(radius*radius);
    for (int y = -radius; y <= radius; ++y) {
        for (int x = -radius; x <= radius; ++x) {
            const int index = y*(*levels)[*activeLevelIndex]->cols+x + centerIndex;
            if(index < (*levels)[*activeLevelIndex]->cols * (*levels)[*activeLevelIndex]->rows && index >= 0){
                indexes.push_back(index);
            }
        }
    }

    for(auto index : indexes)
    {
        (*levels)[*activeLevelIndex]->makePoisonTile(index);
    }
}

/*
 * Move the protagonist relatively in the active level
 * This also updates the energy of the protagonist, since movement has a cost associated with it
 */
void GameController::moveProtagonistRelative(int relativeX, int relativeY)
{
    qCInfo(gameControllerCat) << "Moving the player relatively: x=" << relativeX << " y=" << relativeY;
    int newXPos = (*levels)[*activeLevelIndex]->protagonist->getXPos() + relativeX;
    int newYPos = (*levels)[*activeLevelIndex]->protagonist->getYPos() + relativeY;
    moveProtagonistAbsolute(newXPos, newYPos);

    /*
     * When moving relatively, we need to take into account the energy loss
     */

    // get the value of the destination tile
    float tileEnergy = (*levels)[*activeLevelIndex]->getTileValue((*levels)[*activeLevelIndex]->protagonist->getXPos(), (*levels)[*activeLevelIndex]->protagonist->getYPos());
    float dmgmul = (*levels)[*activeLevelIndex]->getDamageMultiplier((*levels)[*activeLevelIndex]->protagonist->getXPos(), (*levels)[*activeLevelIndex]->protagonist->getYPos());
    tileEnergy = 1/tileEnergy; // invert the tile value

    tileEnergy = tileEnergy * 0.2; // Make the game more easy TODO: Make difficulty modes for this if there is time

    // update energy based on movement
    (*levels)[*activeLevelIndex]->setProtagonistEnergy(((*levels)[*activeLevelIndex]->getProtagonistEnergy())-tileEnergy);

    // update health if we are on poison tile
    (*levels)[*activeLevelIndex]->setProtagonistHealth(((*levels)[*activeLevelIndex]->getProtagonistHealth())-tileEnergy*dmgmul);
}

/*
 * Move the protagonist absolutely in the active level
 * This does NOT update the energy of the protagonist
 */
void GameController::moveProtagonistAbsolute(int absoluteX, int absoluteY)
{
    qCInfo(gameControllerCat) << "Moving the player absolutely: x=" << absoluteX << " y=" << absoluteY;
    if(calculateValidMove(absoluteX, absoluteY)){
        healthPackLogic(absoluteX, absoluteY);
        (*levels)[*activeLevelIndex]->moveProtagonistAbsolute(absoluteX, absoluteY);
    }
    emit updateUI(); // update UI after calculating changes due to attempted move
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
    // TODO: TEMP FIX FOR ENABLING XENEMY IN FIRST LEVEL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    (*levels)[*activeLevelIndex]->setActiveLevel();
}

void GameController::connectSlots()
{
    // connect protagonist position change signal to game controller
    for (int i = 0; i < (int)(*levels).size(); i++) {
        QObject::connect(&(*((*levels)[i]->protagonist)), &Protagonist::posChanged, this, &GameController::protagonistPositionUpdated);

        for (int i = 0; i < (int)((*levels)[*activeLevelIndex]->enemies).size(); i++) {
            auto reference = (&(*((*levels)[*activeLevelIndex]->enemies[i])));
            auto temp = dynamic_cast<XEnemy*>(reference);
            if (temp != nullptr){
                // succesfully casted to a XEnemy at runtime
                // connect slots
                QObject::connect(temp, &XEnemy::positionXEnemyUpdated, this, &GameController::requestUpdateUI);
            }
        }
    }
}

void GameController::protagonistPositionUpdated(int xPos, int yPos)
{
    qCInfo(gameControllerCat) << "Detected new protagonist location: x=" << xPos << " y=" << yPos;
    //protagonistView->renderModel(xPos,yPos);
    emit updateUI();
}

void GameController::requestUpdateUI()
{
    qCInfo(gameControllerCat) << "An update of the UI has been requested";
    emit updateUI();
}
