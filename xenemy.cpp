#include "xenemy.h"
#include <QDateTime>
#include <QImage>
#include <QRgb>
#include <QTimer>
#include <QtDebug>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <QtLogging>
#include <QLoggingCategory>
#include "levelmanager.h"
#include "gamecontroller.h"
#include "pathfinderhelper.h"
QLoggingCategory XEnemyCat("XEnemy");

XEnemy::XEnemy(int xPosition, int yPosition, float strength): Enemy(xPosition, yPosition, strength)
{
    health = 100.0f; // this should be determined by difficulty (hopefully)

    qCInfo(XEnemyCat) <<  "Created an XEnemy";
    constexpr const int initUpdateTime = 10;
    QTimer::singleShot(initUpdateTime * 1000, this, SLOT(updateXEnemyPosition()));
}

bool XEnemy::getUpdatePositionAllowed() const
{
    return updatePositionAllowed;
}

void XEnemy::setUpdatePositionAllowed(bool newUpdatePositionAllowed)
{
    updatePositionAllowed = newUpdatePositionAllowed;
}

void XEnemy::updateXEnemyPosition()
{
    // restart timer for updating
    const int updateTime = 1; // this should be determined by difficulty (hopefully)
    QTimer::singleShot(updateTime * 1000, this, SLOT(updateXEnemyPosition()));

    // if (getUpdatePositionAllowed()){
    if (true){
        PathFinderHelper pfHelper = PathFinderHelper();
        LevelManager* levelManager = LevelManager::GetInstance();
        auto levels = levelManager->getLevels();
        GameController* gctrl = GameController::GetInstance();
        auto activeIndex = gctrl->getActiveLevelIndex();
        auto moves = pfHelper.getPath((*levels)[*activeIndex]->tiles, 50, 300, (*levels)[*activeIndex]->cols);
        qCInfo(XEnemyCat) <<  "Update position of XEnemy. Got path : " << moves;
    }
}

float XEnemy::getHealth() const
{
    return health;
}

void XEnemy::setHealth(float newHealth)
{
    health = newHealth;
    if(newHealth <= 0.5f){
        emit(dead());
    }
}
