#include "gamecontroller.h"
#include "pathfinderhelper.h"
#include "xenemy.h"
#include "difficultycontroller.h"
#include "ownenemy.h"
#include "ownpenemy.h"

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
    qCInfo(gameControllerCat) << "Setting new active level to: " << newActiveLevelIndex;
    *activeLevelIndex = newActiveLevelIndex;
    for (int i = 0; i < (int)(*levels).size(); i++) {
        if(i == newActiveLevelIndex){
            (*levels)[i]->setActiveLevel();
        } else {
            (*levels)[i]->setInActiveLevel();
        }
    }
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
    if(tileContainsEnemy(absoluteX, absoluteY)){
        isValidMove = false;
        // Attack the enemy
        attackEnemy(absoluteX, absoluteY);
    }

    // detect wall
    if(detectWall(absoluteX, absoluteY)){
        isValidMove = false;
    }

    // detect out of bounds
    if (absoluteX < 0 || absoluteY < 0 || absoluteY >= ((*levels)[*activeLevelIndex]->cols) || absoluteX >= ((*levels)[*activeLevelIndex]->rows)){
        isValidMove = false;
    }

    // can protagonist move?
    if((*levels)[*activeLevelIndex]->getProtagonistHealth() == 0.0f || (*levels)[*activeLevelIndex]->getProtagonistEnergy() == 0.0f){
        isValidMove = false;
        emit protagonistDeathVisualisation();
    }

    return isValidMove;
}

bool GameController::tileContainsEnemy(const int absoluteX, const int absoluteY)
{
    bool containsEnemy = false; // we assume there is no enemy, and perform checks to (dis)prove this
    for (int i = 0; i < (int)((*levels)[*activeLevelIndex]->enemies).size(); i++) {
        auto reference = (&(*((*levels)[*activeLevelIndex]->enemies[i])));
        if (reference->getXPos() == absoluteX && reference->getYPos() == absoluteY){
            // found an Enemy at the target position
            containsEnemy = true;
        }
    }
    return containsEnemy;
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
            emit protagonistHealthVisualisation();
        }
    }
}

void GameController::PoisonTileLogic(const int absoluteX, const int absoluteY)
{
    const int index = absoluteX + absoluteY * ((*levels)[*activeLevelIndex]->cols);
    auto tile = ((*levels)[*activeLevelIndex]->tiles)[index].get();
    const int poisonDmg = tile->damageMultiplier;
    if (poisonDmg) {
        emit protagonistPoisonVisualisation();
    }
}

bool GameController::attackEnemy(const int absoluteX, const int absoluteY)
{
    qCInfo(gameControllerCat) << "Attacking Enemy";
    for (int i = 0; i < (int)((*levels)[*activeLevelIndex]->enemies).size(); i++) {
        auto reference = (&(*((*levels)[*activeLevelIndex]->enemies[i])));

        if (reference->getXPos() == absoluteX && reference->getYPos() == absoluteY){
            const float healthLoss = reference->getAttacked(DifficultyController::GetInstance()->getPEnemyHealthLossAttack());
            (*levels)[*activeLevelIndex]->setProtagonistHealth((*levels)[*activeLevelIndex]->getProtagonistHealth() - healthLoss);
        }
    }
    emit protagonistAttackVisualisation();
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

void GameController::detectXEnemyColision(const int absoluteX, const int absoluteY)
{
    for (int i = 0; i < (int)((*levels)[*activeLevelIndex]->enemies).size(); i++) {
        auto reference = (&(*((*levels)[*activeLevelIndex]->enemies[i])));
        auto temp = dynamic_cast<XEnemy*>(reference);
        if (temp != nullptr){
            // succesfully casted to a XEnemy at runtime
            // check if it is at the right place
            if (temp->getXPos() == absoluteX && temp->getYPos() == absoluteY){
                // found a XEnemy at the targetposition
                qCInfo(gameControllerCat) << "Protagonist has been caught by XEnemy";
                (*levels)[*activeLevelIndex]->setProtagonistHealth(0.0f);
                emit protagonistDeathVisualisation();
            }
        }
    }
}

bool GameController::detectWall(const int absoluteX, const int absoluteY)
{
    bool isWallPresent{false};
    float tileValue = (*levels)[*activeLevelIndex]->getTileValue(absoluteX, absoluteY);
    if(tileValue == std::numeric_limits<float>::infinity()){
        isWallPresent = true;
    }
    return isWallPresent;
}

/*
 * Move the protagonist relatively in the active level
 * This also updates the energy of the protagonist, since movement has a cost associated with it
 */
void GameController::moveProtagonistRelative(int relativeX, int relativeY)
{
    qCInfo(gameControllerCat) << "Moving player on level: " << *getActiveLevelIndex();
    qCInfo(gameControllerCat) << "Moving the player relatively: x=" << relativeX << " y=" << relativeY;
    int newXPos = (*levels)[*activeLevelIndex]->protagonist->getXPos() + relativeX;
    int newYPos = (*levels)[*activeLevelIndex]->protagonist->getYPos() + relativeY;
    if (relativeX == 0 && relativeY == -1) {
        moveProtagonistAbsolute(newXPos, newYPos, "up");
    } else if (relativeX == 0) {
        moveProtagonistAbsolute(newXPos, newYPos, "down");

    } else if (relativeX == 1) {
        moveProtagonistAbsolute(newXPos, newYPos, "right");

    } else {
        moveProtagonistAbsolute(newXPos, newYPos, "left");
    }

    /*
     * When moving relatively, we need to take into account the energy loss
     */

    // get the value of the destination tile (this can be the original tile if absolute move could not happen, that is why we get the curr pos of the prot)
    float tileEnergy = (*levels)[*activeLevelIndex]->getTileValue((*levels)[*activeLevelIndex]->protagonist->getXPos(), (*levels)[*activeLevelIndex]->protagonist->getYPos());
    float dmgmul = (*levels)[*activeLevelIndex]->getDamageMultiplier((*levels)[*activeLevelIndex]->protagonist->getXPos(), (*levels)[*activeLevelIndex]->protagonist->getYPos());
    tileEnergy = 1/tileEnergy; // invert the tile value

    tileEnergy = tileEnergy * DifficultyController::GetInstance()->getWalkingEnergyLoss(); // Make the game more easy 

    // update energy based on movement
    (*levels)[*activeLevelIndex]->setProtagonistEnergy(((*levels)[*activeLevelIndex]->getProtagonistEnergy())-tileEnergy);

    // update health if we are on poison tile
    (*levels)[*activeLevelIndex]->setProtagonistHealth(((*levels)[*activeLevelIndex]->getProtagonistHealth())-tileEnergy*dmgmul);
}

/*
 * Move the protagonist absolutely in the active level
 * This does NOT update the energy of the protagonist
 */
void GameController::moveProtagonistAbsolute(int absoluteX, int absoluteY, const QString& direction)
{
    qCInfo(gameControllerCat) << "Moving the player absolutely: x=" << absoluteX << " y=" << absoluteY;
    if(calculateValidMove(absoluteX, absoluteY)){
        if (absoluteX == 8 && absoluteY == 2){
            (*levels)[*activeLevelIndex]->moveProtagonistAbsolute(0, 0);
            *activeLevelIndex = (*activeLevelIndex + 1) % (levels->size());
            setActiveLevelIndex(*activeLevelIndex);
        }
        else {
            (*levels)[*activeLevelIndex]->moveProtagonistAbsolute(absoluteX, absoluteY);
            (*levels)[*activeLevelIndex]->markTileVisited(absoluteX, absoluteY);
            if (direction == "up") {
                emit protagonistMoveUpVisualisation();
                emit textualWorldMoveUp();
            } else if (direction == "down") {
                emit protagonistMoveDownVisualisation();
                emit textualWorldMoveDown();
            } else if (direction == "right") {
                emit protagonistMoveRightVisualisation();
                emit textualWorldMoveRight();
            } else if (direction == "left"){
                emit protagonistMoveLeftVisualisation();
                emit textualWorldMoveLeft();
            }
            healthPackLogic(absoluteX, absoluteY);
            PoisonTileLogic(absoluteX, absoluteY);
        }
    }
    emit updateUI(); // update UI after calculating changes due to attempted move
}


void GameController::initialGameLoad()
{
    qCInfo(gameControllerCat) << "Performing initial game load.";
    activeLevelIndex = std::make_shared<int>(0);
    // get levels from GameGenerator;
    std::vector<std::unique_ptr<Level>> levelCollection;
    levelCollection.emplace_back(std::make_unique<Level>(":/images/world_images/worldmap.png"));
    levelCollection.emplace_back(std::make_unique<Level>(":/images/world_images/worldmap2.png"));
    levelCollection.emplace_back(std::make_unique<Level>(":/images/world_images/worldmap4.png", 500, 500));

    LevelManager* levelManager = LevelManager::GetInstance();
    levelManager->setLevels(levelCollection);
    levels = levelManager->getLevels();
    setActiveLevelIndex(*activeLevelIndex);
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
    detectXEnemyColision(xPos, yPos);
}

void GameController::requestUpdateUI()
{
    qCInfo(gameControllerCat) << "An update of the UI has been requested";
    emit updateUI();
    auto xPos = (*levels)[*activeLevelIndex]->protagonist->getXPos();
    auto yPos = (*levels)[*activeLevelIndex]->protagonist->getYPos();
    PoisonTileLogic(xPos, yPos);
    detectXEnemyColision(xPos, yPos);
}
