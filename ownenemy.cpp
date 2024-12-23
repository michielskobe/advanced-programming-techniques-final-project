#include "ownenemy.h"
#include "difficultycontroller.h"

OwnEnemy::OwnEnemy(int xPos, int yPos, int strength): Enemy(xPos, yPos, strength)
{
    idleImage = ":/images/Enemy_Idle.png";
    deadImage = ":/images/Enemy_Dead.png";
    textRepresentation = " E ";
}

OwnEnemy::OwnEnemy(const Enemy &worldEnemy): Enemy(worldEnemy.getXPos(), worldEnemy.getYPos(), worldEnemy.getValue())
{
    idleImage = ":/images/Enemy_Idle.png";
    deadImage = ":/images/Enemy_Dead.png";
    textRepresentation = " E ";
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

QString OwnEnemy::getImage() const
{
    if(getDefeated()){
        return deadImage;
    }
    return idleImage;
}

QString OwnEnemy::getTextRepresentation() const
{
    if(getDefeated()){
        return textRepresentation.toLower();
    }
    return textRepresentation;
}
