#include "autoplaycontroller.h"

QLoggingCategory autoplayControllerCat("autoplay");

AutoPlayController::AutoPlayController()
{
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void AutoPlayController::performAction()
{
    qCInfo(autoplayControllerCat) << "Invoking autoplay action";
    // find closest enemy
    auto closestEnemyIndex = findClosestEnemy();

    // find path to the closest enemy
    auto reference = (&(*((*levels)[*(gameController->getActiveLevelIndex())]->enemies[closestEnemyIndex])));
    auto enemyTileIndex = reference->getXPos() + reference->getYPos() *  (*levels)[*(gameController->getActiveLevelIndex())]->cols;
    auto pathToEnemy = getPathToDest(enemyTileIndex);
    qCInfo(autoplayControllerCat) << "Closest enemy path is: " << pathToEnemy;

}

int AutoPlayController::findClosestEnemy()
{
    float minDistance{1'000'000};
    auto closestEnemy{0};
    auto protagonist = &((*levels)[*(gameController->getActiveLevelIndex())]->protagonist);

    for (int i = 0; i < (int)((*levels)[*(gameController->getActiveLevelIndex())]->enemies).size(); i++) {
        auto reference = (&(*((*levels)[*(gameController->getActiveLevelIndex())]->enemies[i])));
        if(!reference->getDefeated()){
            auto distance = findDistance(**protagonist, *reference);
            if(distance < minDistance){
                closestEnemy = i;
                minDistance = distance;
            }
        }
    }
    return closestEnemy;
}

float AutoPlayController::findDistance(Tile &t1, Tile &t2)
{
    return std::abs(t1.getXPos() - t2.getXPos()) + std::abs(t1.getYPos() - t2.getYPos());
}

std::vector<std::pair<int, int> > AutoPlayController::getPathToDest(const int destIndex)
{
    PathFinderHelper pfHelper = PathFinderHelper();
    const int protagonistIndex = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getXPos() + (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getYPos()*(*levels)[*(gameController->getActiveLevelIndex())]->cols;
    return pfHelper.getPath((*levels)[*(gameController->getActiveLevelIndex())]->tiles, protagonistIndex, destIndex, (*levels)[*(gameController->getActiveLevelIndex())]->cols);
}
