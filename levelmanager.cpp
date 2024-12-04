#include "levelmanager.h"

LevelManager::LevelManager()
    : levels(std::make_shared<std::vector<std::unique_ptr<Level>>>())
{}


LevelManager* LevelManager::levelManager= nullptr;

LevelManager *LevelManager::GetInstance()
{
    if(levelManager==nullptr){
        levelManager = new LevelManager();
    }
    return levelManager;
}



std::shared_ptr<std::vector<std::unique_ptr<Level>>> LevelManager::getLevels()
{
    return levels;
}

void LevelManager::setLevels(std::vector<QString> fileNames)
{
    levels->reserve(fileNames.size()); // reserve the memory to avoid re-alloc

    // generate levels based on the fileNames
    for (auto file: fileNames){
        levels->emplace_back(new Level(file));
    }
}

