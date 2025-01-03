#ifndef AUTOPLAYCONTROLLER_H
#define AUTOPLAYCONTROLLER_H

#include <QObject>
#include "level.h"
#include "gamecontroller.h"
#include "ownenemy.h"
#include "world.h"

class AutoPlayController : public QObject
{
    Q_OBJECT
public:
    AutoPlayController();

    void performAction();
    int findClosestEnemy();
    float findDistance(Tile & t1, Tile & t2);

protected:
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
signals:
};

#endif // AUTOPLAYCONTROLLER_H
