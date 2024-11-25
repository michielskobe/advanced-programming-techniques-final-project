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

    void moveProtagonistRelative(int relativeX, int relativeY);
    void moveProtagonistAbsolute(int absoluteX, int absoluteY);

    void addLevel();
    void initialGameLoad();
};

#endif // GAMECONTROLLER_H
