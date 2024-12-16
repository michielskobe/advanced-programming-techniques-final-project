#include "difficultycontroller.h"

DifficultyController::DifficultyController() {}

DifficultyController* DifficultyController::difficultyController= nullptr;

DifficultyController *DifficultyController::GetInstance()
{
    if(difficultyController==nullptr){
        difficultyController = new DifficultyController();
    }
    return difficultyController;
}

int DifficultyController::getXEnemyUpdateTime()
{
    return xEnemyUpdateTime.at(difficultySetting);
}

float DifficultyController::getXEnemyHealthLossMove()
{
    return xEnemyHealthLossMove.at(difficultySetting);
}

int DifficultyController::getPoisonTileLingeringTime()
{
    return PoisonTileLingeringTime.at(difficultySetting);
}

float DifficultyController::getPoisonTileDamageMul()
{
    return PoisonTileDamageMul.at(difficultySetting);
}

int DifficultyController::getPoisonTileSpreadRadius()
{
    return PoisonTileSpreadRadius.at(difficultySetting);
}

float DifficultyController::getWalkingEnergyLoss()
{
    return WalkingEnergyLoss.at(difficultySetting);
}

float DifficultyController::getPEnemyHealthLossAttack()
{
    return PEnemyHealthLossAttack.at(difficultySetting);
}

float DifficultyController::getProtagonistHealthLossAttack()
{
    return ProtagonistHealthLossAttack.at(difficultySetting);
}

int DifficultyController::getDifficultySetting() const
{
    return difficultySetting;
}

void DifficultyController::setDifficultySetting(int newDifficultySetting)
{
    difficultySetting = newDifficultySetting;
}
