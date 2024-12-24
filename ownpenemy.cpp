#include "ownpenemy.h"
#include "difficultycontroller.h"
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
#include "gamecontroller.h"

OwnPEnemy::OwnPEnemy(const PEnemy &worldPEnemy): OwnEnemy(worldPEnemy), poisonLevel{worldPEnemy.getPoisonLevel()}
{
    srand(time(nullptr));
}

bool OwnPEnemy::poison()
{
    poisonLevel -= 10.0f;
    if (poisonLevel > 0.0f)
    {
        emit poisonLevelUpdated(poisonLevel);
        int t = rand() % 5;
        std::cout << "starting timer for " << t << " seconds"
                  << " with poisonLevel = " << poisonLevel << std::endl;
        QTimer::singleShot(t * 1000, this, SLOT(poison()));
        return true;
    }
    else
    {
        poisonLevel = 0.0f;
        setDefeated(true);
        emit dead();
    }
    return false;
}

float OwnPEnemy::getAttacked(const float damage)
{
    if(!getDefeated()){
        float newValue = getValue() - damage;
        if(newValue <= 0.5f){
            setDefeated(true);
            setValue(0.0f);
        } else {
            setValue(newValue);
            setPoisonLevel(getPoisonLevel() -damage);
            poison();
            GameController::GetInstance()->setPoisonTiles(getXPos(), getYPos(), DifficultyController::GetInstance()->getPoisonTileSpreadRadius());
        }

        return DifficultyController::GetInstance()->getProtagonistHealthLossAttack();
    }
    return 0.0f;
}

float OwnPEnemy::getPoisonLevel() const
{
    return poisonLevel;
}

void OwnPEnemy::setPoisonLevel(float newPoisonLevel)
{
    poisonLevel = newPoisonLevel;
}
