#include "level.h"
#include "world.h"
#include "poisontile.h"
#include "xenemy.h"
QLoggingCategory LevelCat("level");

Level::Level(QString fileName)
{
    qCInfo(LevelCat) << "Generating level for " << fileName << ".";
    // add world to stack, generate what we need, and then add it to level
    World world = World();
    world.createWorld(fileName, 5, 5, 0.50f);

    tiles = world.getTiles();
    enemies = world.getEnemies();
    healthPacks = world.getHealthPacks();
    rows = world.getRows();
    cols = world.getCols();
    protagonist = world.getProtagonist();
    worldImageLocation = fileName;
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
    // first check if this is a valid position
    if (absoluteX < 0 || absoluteY < 0 || absoluteY >= cols || absoluteX >= rows){
        qCInfo(LevelCat) << "Invalid tile position, can not move Protagonist to x=" << absoluteX << " y=" << absoluteY;
    }
    else  {
        protagonist->setPos(absoluteX, absoluteY);
    }
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
    protagonist->setHealth(newHealth);
}

void Level::setProtagonistEnergy(const float newEnergy)
{
    protagonist->setEnergy(newEnergy);
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

void Level::makePoisonTile(const int tileIndex)
{
    const int tileXPos = tiles[tileIndex].get()->getXPos();
    const int tileYPos = tiles[tileIndex].get()->getYPos();
    const float tileValue = tiles[tileIndex].get()->getValue();
    tiles[tileIndex].reset(new PoisonTile(tileXPos, tileYPos, tileValue));
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

    auto reference = (&(*(tiles[index])));
    auto temp = dynamic_cast<PoisonTile*>(reference);
    if (temp != nullptr){
        qCInfo(LevelCat) << "Poison tile detected, damage multiplier of it is: " << temp->getDamageMultiplier();
        return temp->getDamageMultiplier();
    }
    return 0.0f;

}

void Level::initXEnemy()
{
    for (int i = 0; i < (int)(enemies).size(); i++) {
        auto reference = (&(*(enemies[i])));
        auto temp = dynamic_cast<PEnemy*>(reference);
        if (temp == nullptr){ // We have a regular enemy
            const int xpos = enemies[i]->getXPos();
            const int ypos = enemies[i]->getYPos();
            const float value = enemies[i]->getValue();
            enemies[i].reset(new XEnemy(xpos, ypos, value));
        }
    }
}

