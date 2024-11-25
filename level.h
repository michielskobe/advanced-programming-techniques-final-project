#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include "world.h"
#include <QtLogging>
#include <QLoggingCategory>

class Level
{
public: //ctor + dctor
    Level();
    Level(QString fileName);

public: //attributes
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Tile>> healthPacks;
    int rows;
    int cols;
    QString worldImageLocation;
    std::unique_ptr<Protagonist> protagonist;

public: // methods
    void moveProtagonistRelative(int relativeX, int relativeY);
    void moveProtagonistAbsolute(int absoluteX, int absoluteY);
};

#endif // LEVEL_H
