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
    void moveProtagonistAbsolute(int absoluteX, int absoluteY, const QString& direction);
    std::shared_ptr<int> getActiveLevelIndex() const;
    void setActiveLevelIndex(int newActiveLevelIndex);
    float getActiveProtagonistHealth() const;
    float getActiveProtagonistEnergy() const;
    bool calculateValidMove(const int absoluteX, const int absoluteY);
    bool tileContainsEnemy(const int absoluteX, const int absoluteY);
    void healthPackLogic(const int absoluteX, const int absoluteY);
    void PoisonTileLogic(const int absoluteX, const int absoluteY);
    bool attackEnemy(const int absoluteX, const int absoluteY);
    void setPoisonTiles(const int centerX, const int centerY, const int radius);
    void detectXEnemyColision(const int absoluteX, const int absoluteY);
    bool detectWall(const int absoluteX, const int absoluteY);

    void addLevel();
    void initialGameLoad();
    void connectSlots();

public slots:
    void protagonistPositionUpdated(int xPos, int yPos);
    void requestUpdateUI();

signals:
    void updateUI();
    void protagonistIdleVisualisation();
    void protagonistMoveUpVisualisation();
    void protagonistMoveDownVisualisation();
    void protagonistMoveLeftVisualisation();
    void protagonistMoveRightVisualisation();
    void protagonistAttackVisualisation();
    void protagonistHealthVisualisation();
    void protagonistPoisonVisualisation();
    void protagonistDeathVisualisation();
    void textualWorldMoveUp();
    void textualWorldMoveDown();
    void textualWorldMoveLeft();
    void textualWorldMoveRight();
};

#endif // GAMECONTROLLER_H
