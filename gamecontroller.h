#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "world.h"
#include "level.h"
#include "gamegenerator.h"
#include "protagonistview.h"
#include "textrender.h"
#include "graphicrender.h"


class GameController: public QObject
{
    Q_OBJECT
public: // constructor/destructor
    GameController();
    ~GameController() override = default;

public: // attributes
    Protagonist protagonist;
    std::vector<std::unique_ptr<Level>> levels;
    int activeLevelIndex = 0;

public: // methods
    void startAutoPlay();
    void stopAutoPlay();

    void moveProtagonistRelative(int relativeX, int relativeY);
    void moveProtagonistAbsolute(int absoluteX, int absoluteY);
    int getActiveLevelIndex() const;
    void setActiveLevelIndex(int newActiveLevelIndex);

    void addLevel();
    void initialGameLoad();
    void connectSlots();

public slots:
    void protagonistPositionUpdated(int xPos, int yPos);
};

#endif // GAMECONTROLLER_H
