#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include "world.h"
#include "pathfindernode.h"
#include <QtLogging>
#include <QLoggingCategory>
#include <ownenemy.h>

class Level
{
public: //ctor + dctor
    Level();
    Level(QString fileName, unsigned int nrOfEnemies = 20, unsigned int nrOfHealthpacks = 15, float pRatio = 0.25f);

public: //attributes
    std::vector<std::unique_ptr<PathFinderNode>> tiles;
    std::vector<std::unique_ptr<OwnEnemy>> enemies;
    std::vector<std::unique_ptr<Tile>> healthPacks;
    int rows;
    int cols;
    QString worldImageLocation;
    QString worldOverlayLocation;
    std::unique_ptr<Protagonist> protagonist;

public: // methods
    void moveProtagonistRelative(int relativeX, int relativeY);
    void moveProtagonistAbsolute(int absoluteX, int absoluteY);
    float getProtagonistHealth() const;
    float getProtagonistEnergy() const;
    void setProtagonistHealth(const float newHealth);
    void setProtagonistEnergy(const float newEnergy);
    float getTileValue(const int absoluteX, const int absoluteY) const;
    void setTileValue(const int absoluteX, const int absoluteY, const float newValue);
    void makePoisonTile(const int tileIndex);
    float getDamageMultiplier(const int absoluteX, const int absoluteY);
    void markTileVisited(const int absoluteX, const int absoluteY);
    void initXEnemy();
    void setActiveLevel();
    void setInActiveLevel();

};

#endif // LEVEL_H
