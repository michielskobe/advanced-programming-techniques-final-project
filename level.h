#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>
#include "world.h"

class Level
{
public: //ctor + dctor
    Level();
    Level(std::string fileName);

public: //attributes
    std::vector<std::unique_ptr<Tile>> tiles;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Tile>> healthPacks;

public: // methods
};

#endif // LEVEL_H
