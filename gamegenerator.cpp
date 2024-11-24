#include "gamegenerator.h"

GameGenerator::GameGenerator()
{

}

GameGenerator::GameGenerator(std::vector<QString> fileNames)
{
    // generate levels based on the fileNames
    for (auto file: fileNames){
        levels.emplace_back(new Level(file));
    }
}

std::vector<std::unique_ptr<Level> > GameGenerator::getLevels()
{
    return std::move(levels);
}
