#ifndef GAMEGENERATOR_H
#define GAMEGENERATOR_H
#include "level.h"
#include <string>
#include <sstream>

class GameGenerator
{
public: // ctor
    GameGenerator();
    GameGenerator(std::vector<std::string> fileNames);

public: // attributes
    std::vector<std::unique_ptr<Level>> levels;

public: // methods
    std::vector<std::unique_ptr<Level>> getLevels();
};

#endif // GAMEGENERATOR_H
