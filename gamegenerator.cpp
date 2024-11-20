#include "gamegenerator.h"

GameGenerator::GameGenerator()
{

}

GameGenerator::GameGenerator(std::vector<std::string> fileNames)
{
    // generate levels based on the fileNames
    throw "Not implemented";
}

std::vector<std::unique_ptr<Level> > GameGenerator::getLevels()
{
    return std::move(levels);
}
