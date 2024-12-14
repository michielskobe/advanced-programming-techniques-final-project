#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "world.h"
#include "level.h"
#include "levelmanager.h"

class GameController: public QObject
{
    Q_OBJECT
public: // constructor/destructor
    GameController();
    ~GameController() override = default;

public: // attributes
    static GameController* gameController;

    Protagonist protagonist;
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    std::shared_ptr<int> activeLevelIndex;

public: // methods
    // Singletons should not be cloneable or assignable.
    GameController(GameController &other) = delete;
    void operator=(const GameController &) = delete;

    // This is the static method that controls the access to the singleton instance.
    static GameController *GetInstance();

    void startAutoPlay();
    void stopAutoPlay();

    void moveProtagonistRelative(int relativeX, int relativeY);
    void moveProtagonistAbsolute(int absoluteX, int absoluteY);
    std::shared_ptr<int> getActiveLevelIndex() const;
    void setActiveLevelIndex(int newActiveLevelIndex);
    float getActiveProtagonistHealth() const;
    float getActiveProtagonistEnergy() const;
    bool calculateValidMove(const int absoluteX, const int absoluteY);
    bool tileContainsPEnemy(const int absoluteX, const int absoluteY);
    void healthPackLogic(const int absoluteX, const int absoluteY);
    void PoisonTileLogic(const int absoluteX, const int absoluteY);
    bool attackPEnemy(const int absoluteX, const int absoluteY);
    void setPoisonTiles(const int centerX, const int centerY, const int radius);

    void addLevel();
    void initialGameLoad();
    void connectSlots();

public slots:
    void protagonistPositionUpdated(int xPos, int yPos);

signals:
    void updateUI();
};

#endif // GAMECONTROLLER_H
