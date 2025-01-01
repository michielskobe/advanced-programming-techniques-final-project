#include "view.h"
#include "gamecontroller.h"
#include "levelmanager.h"

View::View() {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}
