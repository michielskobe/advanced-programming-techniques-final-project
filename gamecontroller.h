#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "world.h"
#include "level.h"
#include "gamegenerator.h"


class GameController
{
public: // constructor/destructor
    GameController();

public: // attributes
    Protagonist protagonist;
    std::vector<std::unique_ptr<Level>> levels;

public: // methods
    void startAutoPlay();
    void stopAutoPlay();

    // maybe we can split this initial game generation into its own class?
    void addLevel();
    void initialGameLoad();
};

#endif // GAMECONTROLLER_H
