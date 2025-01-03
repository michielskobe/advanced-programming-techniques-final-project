#ifndef AUTOPLAYCONTROLLER_H
#define AUTOPLAYCONTROLLER_H

#include <QObject>
#include "level.h"
#include "gamecontroller.h"
#include "ownenemy.h"
#include "world.h"
#include "pathfinderhelper.h"

enum AutoPlayState{
    idle,
    running,
    stalled
};

class AutoPlayController : public QObject
{
    Q_OBJECT
public:
    AutoPlayController();
    static AutoPlayController* autoPlayController;

    // Singletons should not be cloneable or assignable.
    AutoPlayController(AutoPlayController &other) = delete;
    void operator=(const AutoPlayController &) = delete;

    // This is the static method that controls the access to the singleton instance.
    static AutoPlayController *GetInstance();



    std::optional<int> findClosestEnemy();
    std::optional<int> findClosestHealthPack();
    float findDistance(Tile & t1, Tile & t2);
    std::vector<std::pair<int, int>> getPathToDest(const int destIndex);
    void highlightCurrentPath();

    bool getActivated() const;
    void setActivated(bool newActivated);

protected:
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
    std::vector<std::pair<int, int>> currentPath;
    enum AutoPlayState state{idle};
    bool activated{false};
signals:

public slots:
    void walkPath();
    void performAction();
};

#endif // AUTOPLAYCONTROLLER_H
