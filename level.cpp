#include "level.h"
#include "world.h"
#include "poisontile.h"
#include "xenemy.h"
#include "gamecontroller.h"
#include "ownenemy.h"
#include "ownpenemy.h"
QLoggingCategory LevelCat("level");

Level::Level(QString fileName, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio)
{
    qCInfo(LevelCat) << "Generating level for " << fileName << ".";
    // add world to stack, generate what we need, and then add it to level
    World world = World();
    world.createWorld(fileName, nrOfEnemies, nrOfHealthpacks, pRatio);

    rows = world.getRows();
    cols = world.getCols();

    auto tempTiles = world.getTiles();
    for (int i = 0; i < (int)(tempTiles).size(); i++){
        auto reference = (&(*(tempTiles[i])));
        auto pathFinderNode = new PathFinderNode(*reference);
        tiles.emplace_back(pathFinderNode);
    }
    auto tempEnemies = world.getEnemies();
    for (int i = 0; i < (int)(tempEnemies).size(); i++) {
        auto reference = (&(*(tempEnemies[i])));
        // Make sure enemy is not located on level switching portal
        if (reference->getXPos() != 8 && reference->getYPos() != 2){
            auto temp = dynamic_cast<PEnemy*>(reference);
            if (temp != nullptr) {
                auto newEnemy = new OwnPEnemy(*temp);
                enemies.emplace_back(newEnemy);
            }else {
                auto newEnemy = new OwnEnemy(*reference);
                enemies.emplace_back(newEnemy);
            }
            // Set the tile value under enemy high, so that pathfinder tries to avoid it
            setTileValue(reference->getXPos(), reference->getYPos(), 10000000000000000000000000.0f);
        }
    }

    healthPacks = world.getHealthPacks();
    protagonist = world.getProtagonist();
    worldImageLocation = fileName;
    worldOverlayLocation = fileName;
    worldOverlayLocation = worldOverlayLocation.replace("world_images", "overlay_images");
    initXEnemy();

}

/*
 * Move the protagonist relatively in the level
 */
void Level::moveProtagonistRelative(int relativeX, int relativeY)
{
    int absoluteX = protagonist->getXPos() + relativeX;
    int absoluteY = protagonist ->getYPos() + relativeY;
    moveProtagonistAbsolute(absoluteX, absoluteY);
}

/*
 * Move the protagonist Absolutely in the level
 */
void Level::moveProtagonistAbsolute(int absoluteX, int absoluteY)
{
    protagonist->setPos(absoluteX, absoluteY);
}

float Level::getProtagonistHealth() const
{
    return protagonist->getHealth();
}

float Level::getProtagonistEnergy() const
{
    return protagonist->getEnergy();
}

void Level::setProtagonistHealth(const float newHealth)
{
    if (newHealth <= 0.5f){ // ensuring 0 health when health gets to low
        protagonist->setHealth(0.0f);
    } else {
        protagonist->setHealth(newHealth);
    }
}

void Level::setProtagonistEnergy(const float newEnergy)
{
    if (newEnergy <= 0.5f){ // ensuring 0 energy when energy gets to low
        protagonist->setEnergy(0.0f);
    } else {
        protagonist->setEnergy(newEnergy);
    }
}

float Level::getTileValue(const int absoluteX, const int absoluteY) const
{
    // check for non valid positions
    if (absoluteX < 0 || absoluteY < 0 || absoluteY >= cols || absoluteX >= rows){
        qCInfo(LevelCat) << "Invalid tile position, can not get energy for position x=" << absoluteX << " y=" << absoluteY;
        return 0.0f;
    }

    // Calculate tile index:
    const int index = absoluteX + absoluteY * cols;

    // check if index is out of bounds
    if (index < 0 || index >= cols*rows){
        qCInfo(LevelCat) << "Tile index is out of bounds, can not get energy for position x=" << absoluteX << " y=" << absoluteY;
        return 0.0f;
    }

    // Get the value of the requested tile
    return tiles[index].get()->getValue();
}

void Level::setTileValue(const int absoluteX, const int absoluteY, const float newValue)
{
    bool canSet{true};
    // check for non valid positions
    if (absoluteX < 0 || absoluteY < 0 || absoluteY >= cols || absoluteX >= rows){
        qCInfo(LevelCat) << "Invalid tile position, can not set value for position x=" << absoluteX << " y=" << absoluteY;
        canSet = false;
    }

    // Calculate tile index:
    const int index = absoluteX + absoluteY * cols;

    // check if index is out of bounds
    if (index < 0 || index >= cols*rows){
        qCInfo(LevelCat) << "Tile index is out of bounds, can not set value for position x=" << absoluteX << " y=" << absoluteY;
        canSet = false;
    }

    // Set the value of the requested tile
    if(canSet){
        tiles[index].get()->setValue(newValue);
    }
}

void Level::makePoisonTile(const int tileIndex)
{
    tiles[tileIndex]->setPoison();
}

float Level::getDamageMultiplier(const int absoluteX, const int absoluteY)
{
    // check for non valid positions
    if (absoluteX < 0 || absoluteY < 0 || absoluteY >= cols || absoluteX >= rows){
        qCInfo(LevelCat) << "Invalid tile position, can not get poison status for position x=" << absoluteX << " y=" << absoluteY;
        return 0.0f;
    }

    // Calculate tile index:
    const int index = absoluteX + absoluteY * cols;

    // check if index is out of bounds
    if (index < 0 || index >= cols*rows){
        qCInfo(LevelCat) << "Tile index is out of bounds, can not get poison status for position x=" << absoluteX << " y=" << absoluteY;
        return 0.0f;
    }
    return tiles[index].get()->getDamageMultiplier();
}

void Level::markTileVisited(const int absoluteX, const int absoluteY)
{
    bool valid{true};
    // check for non valid positions
    if (absoluteX < 0 || absoluteY < 0 || absoluteY >= cols || absoluteX >= rows){
        qCInfo(LevelCat) << "Invalid tile position, can not set visitedd status for position x=" << absoluteX << " y=" << absoluteY;
        valid = false;
    }

    // Calculate tile index:
    const int index = absoluteX + absoluteY * cols;

    // check if index is out of bounds
    if (index < 0 || index >= cols*rows){
        qCInfo(LevelCat) << "Tile index is out of bounds, can not set visited status for position x=" << absoluteX << " y=" << absoluteY;
        valid = false;
    }
    if(valid){
        tiles[index].get()->setPlayerVisited(true);
    }
}

void Level::initXEnemy()
{
    for (int i = 0; i < (int)(enemies).size(); i++) {
        auto reference = (&(*(enemies[i])));
        auto temp = dynamic_cast<OwnPEnemy*>(reference);
        if (temp == nullptr){ // We have a regular enemy
            const int xpos = enemies[i]->getXPos();
            const int ypos = enemies[i]->getYPos();
            const float value = enemies[i]->getValue();
            auto newEnemy = new XEnemy(xpos, ypos, value);
            newEnemy->setHealth(cols*rows);
            enemies[i].reset(newEnemy);
            setTileValue(xpos, ypos, 1.0f);
            // stop making XEnemy after 1 has been made, leave the rest as regular enemy
            break;
        }
    }
}

void Level::setActiveLevel()
{
    for (int i = 0; i < (int)(enemies).size(); i++) {
        auto reference = (&(*(enemies[i])));
        auto temp = dynamic_cast<XEnemy*>(reference);
        if (temp != nullptr){
            temp->setUpdatePositionAllowed(true);
        }
    }
}

void Level::setInActiveLevel()
{
    for (int i = 0; i < (int)(enemies).size(); i++) {
        auto reference = (&(*(enemies[i])));
        auto temp = dynamic_cast<XEnemy*>(reference);
        if (temp != nullptr){
            temp->setUpdatePositionAllowed(false);
        }
    }
}

