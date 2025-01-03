#ifndef AUTOPLAYCONTROLLER_H
#define AUTOPLAYCONTROLLER_H

#include <QObject>
#include "level.h"
#include "gamecontroller.h"
#include "ownenemy.h"
#include "world.h"
#include "pathfinderhelper.h"

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


    void performAction();
    int findClosestEnemy();
    int findClosestHealthPack();
    float findDistance(Tile & t1, Tile & t2);
    std::vector<std::pair<int, int>> getPathToDest(const int destIndex);
    void highlightCurrentPath();

protected:
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
    std::vector<std::pair<int, int>> currentPath;
    bool idle{true};
signals:

public slots:
    void walkPath();
};

#endif // AUTOPLAYCONTROLLER_H
