#include "gamegenerator.h"

GameGenerator::GameGenerator()
{

}

GameGenerator::GameGenerator(std::vector<QString> fileNames)
{
    levels.reserve(fileNames.size()); // reserve the memory to avoid re-alloc

    // generate levels based on the fileNames
    for (auto file: fileNames){
        levels.emplace_back(new Level(file));
    }
}

std::vector<std::unique_ptr<Level> > GameGenerator::getLevels()
{
    return std::move(levels);
}
