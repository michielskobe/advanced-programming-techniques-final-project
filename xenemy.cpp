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
#include "difficultycontroller.h"
QLoggingCategory XEnemyCat("XEnemy");

XEnemy::XEnemy(int xPosition, int yPosition, float strength): OwnEnemy(xPosition, yPosition, strength)
{
    health = 100.0f; 
    deadPixmap = QPixmap(":/images/XEnemy_Dead.png");
    idlePixmap = QPixmap(":/images/XEnemy_Idle.png");

    qCInfo(XEnemyCat) <<  "Created an XEnemy";

    constexpr const int initUpdateTime = 10;
    QTimer::singleShot(initUpdateTime * 1000, this, SLOT(updateXEnemyPosition()));
}

XEnemy::XEnemy(const Enemy &enemy): OwnEnemy(enemy)
{
    XEnemy(enemy.getXPos(), enemy.getYPos(), enemy.getValue());
}

bool XEnemy::getUpdatePositionAllowed() const
{
    return updatePositionAllowed;
}

void XEnemy::setUpdatePositionAllowed(bool newUpdatePositionAllowed)
{
    updatePositionAllowed = newUpdatePositionAllowed;
}

void XEnemy::updatePosition(std::pair<int, int> move)
{
    // perform move
    auto [dx, dy] = move;
    xPos += dx;
    yPos += dy;

    // update health and UI
    setHealth(getHealth()-DifficultyController::GetInstance()->getXEnemyHealthLossMove());
    emit(positionXEnemyUpdated());
}

int XEnemy::protagonistDistance() const
{
    LevelManager* levelManager = LevelManager::GetInstance();
    auto levels = levelManager->getLevels();
    GameController* gctrl = GameController::GetInstance();
    auto activeIndex = gctrl->getActiveLevelIndex();
    return std::abs(xPos - (*levels)[*activeIndex]->protagonist->getXPos()) + std::abs(yPos - (*levels)[*activeIndex]->protagonist->getYPos());
}

float XEnemy::getAttacked(const float damage)
{
    // You can not attack an XEnemy, it can only die from walking around too much.
    // Once you touch the XEnemy, you die.
    // This implementation does not punish you if you try to attack it without knowing the result of getting caught
    return 0.0f;
}

void XEnemy::updateXEnemyPosition()
{
    // restart timer for updating
    const int updateTime = DifficultyController::GetInstance()->getXEnemyUpdateTime();
    QTimer::singleShot(updateTime * 100, this, SLOT(updateXEnemyPosition()));

    if (getUpdatePositionAllowed() && !getDefeated()){
        PathFinderHelper pfHelper = PathFinderHelper();
        LevelManager* levelManager = LevelManager::GetInstance();
        auto levels = levelManager->getLevels();
        GameController* gctrl = GameController::GetInstance();
        auto activeIndex = gctrl->getActiveLevelIndex();
        const int ownIndex = xPos + yPos*(*levels)[*activeIndex]->cols;
        const int protagonistIndex = (*levels)[*activeIndex]->protagonist->getXPos() + (*levels)[*activeIndex]->protagonist->getYPos()*(*levels)[*activeIndex]->cols;
        if(protagonistDistance() <= 200){
            auto moves = pfHelper.getPath((*levels)[*activeIndex]->tiles, ownIndex, protagonistIndex, (*levels)[*activeIndex]->cols);
            if (!moves.empty()){
               updatePosition(moves[0]);
            }
            qCInfo(XEnemyCat) <<  "Update position of XEnemy. Got path : " << moves;
        } else {
            qCInfo(XEnemyCat) <<  "Protagonist too far away. Did not move XEnemy";
        }

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
        qCInfo(XEnemyCat) <<  "XEnemy has died (⌐■_■)︻╦╤─ (╥﹏╥)";
        setDefeated(true);
        emit(dead());
    }
}
