#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include <memory>
#include "level.h"

class LevelManager
{
protected:
    LevelManager();

    static LevelManager* levelManager;

    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;

public:
    // Singletons should not be cloneable or assignable.
    LevelManager(LevelManager &other) = delete;
    void operator=(const LevelManager &) = delete;

    // This is the static method that controls the access to the singleton instance.
    static LevelManager *GetInstance();

    void setLevels(std::vector<std::unique_ptr<Level>>& levelCollection);

    std::shared_ptr<std::vector<std::unique_ptr<Level>>> getLevels();
};
#endif // LEVELMANAGER_H
