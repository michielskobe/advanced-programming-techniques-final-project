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
