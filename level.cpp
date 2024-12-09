#include "level.h"
#include "world.h"
QLoggingCategory LevelCat("level");

Level::Level(QString fileName)
{
    qCInfo(LevelCat) << "Generating level for " << fileName << ".";
    // add world to stack, generate what we need, and then add it to level
    World world = World();
    world.createWorld(fileName, 5, 5, 0.25f);

    tiles = world.getTiles();
    enemies = world.getEnemies();
    healthPacks = world.getHealthPacks();
    rows = world.getRows();
    cols = world.getCols();
    protagonist = world.getProtagonist();
    worldImageLocation = fileName;

}

/*
 * Move the protagonist relatively in the level
 */
void Level::moveProtagonistRelative(int relativeX, int relativeY)
{
    protagonist->setPos(protagonist->getXPos() + relativeX, protagonist ->getYPos() + relativeY);
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
    protagonist->setHealth(newHealth);
}

void Level::setProtagonistEnergy(const float newEnergy)
{
    protagonist->setEnergy(newEnergy);
}

