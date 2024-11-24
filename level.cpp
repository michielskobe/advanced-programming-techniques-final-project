#include "level.h"
#include "world.h"

Level::Level(QString fileName)
{
    // add world to stack, generate what we need, and then add it to level
    World world = World();
    world.createWorld(fileName, 1, 1, 0.25f);

    tiles = world.getTiles();
    enemies = world.getEnemies();
    healthPacks = world.getHealthPacks();
    rows = world.getRows();
    cols = world.getCols();
    protagonist = world.getProtagonist();

}
