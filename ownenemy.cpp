#include "ownenemy.h"
#include "difficultycontroller.h"

OwnEnemy::OwnEnemy(int xPos, int yPos, int strength): Enemy(xPos, yPos, strength)
{
    deadPixmap = QPixmap(":/images/Enemy_Dead.png");
    idlePixmap = QPixmap(":/images/Enemy_Idle.png");
}

OwnEnemy::OwnEnemy(const Enemy &worldEnemy): Enemy(worldEnemy.getXPos(), worldEnemy.getYPos(), worldEnemy.getValue())
{
    deadPixmap = QPixmap(":/images/Enemy_Dead.png");
    idlePixmap = QPixmap(":/images/Enemy_Idle.png");
}

/*
 * This function handles logic for getting attacked.
 * It returns the damage which should be dealt to the protagonist
 */
float OwnEnemy::getAttacked(const float damage)
{
    if(!getDefeated()){
        float newValue = getValue() - damage;
        if(newValue <= 0.5f){
            setDefeated(true);
            setValue(0.0f);
        } else {
            setValue(getValue()-damage);
        }

        return DifficultyController::GetInstance()->getProtagonistHealthLossAttack();
    }
    return 0.0f;
}

QPixmap OwnEnemy::getPixmap()
{
    if(getDefeated()){
        return deadPixmap;
    }
    return idlePixmap;
}

