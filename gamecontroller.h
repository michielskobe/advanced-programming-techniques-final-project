#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "world.h"
#include "level.h"
#include "protagonistview.h"
#include "textrender.h"
#include "graphicrender.h"
#include "levelmanager.h"

class GameController: public QObject
{
    Q_OBJECT
public: // constructor/destructor
    GameController();
    ~GameController() override = default;

public: // attributes
    Protagonist protagonist;
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    std::shared_ptr<int> activeLevelIndex;

public: // methods
    void startAutoPlay();
    void stopAutoPlay();

    void moveProtagonistRelative(int relativeX, int relativeY);
    void moveProtagonistAbsolute(int absoluteX, int absoluteY);
    std::shared_ptr<int> getActiveLevelIndex() const;
    void setActiveLevelIndex(int newActiveLevelIndex);
    float getActiveProtagonistHealth() const;
    float getActiveProtagonistEnergy() const;

    void addLevel();
    void initialGameLoad();
    void connectSlots();

public slots:
    void protagonistPositionUpdated(int xPos, int yPos);

signals:
    void updateUI();
};

#endif // GAMECONTROLLER_H
