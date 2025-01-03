#include "autoplaycontroller.h"
#include <unistd.h>
#include <QTimer>

QLoggingCategory autoplayControllerCat("autoplay");

AutoPlayController* AutoPlayController::autoPlayController= nullptr;


AutoPlayController::AutoPlayController()
{
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

AutoPlayController *AutoPlayController::GetInstance()
{
    if(autoPlayController==nullptr){
        autoPlayController = new AutoPlayController();
    }
    return autoPlayController;
}

void AutoPlayController::performAction()
{
    qCInfo(autoplayControllerCat) << "Invoking autoplay action";
    // find closest enemy
    auto closestEnemyIndex = findClosestEnemy();

    // find path to the closest enemy
    auto reference = (&(*((*levels)[*(gameController->getActiveLevelIndex())]->enemies[closestEnemyIndex])));
    auto enemyTileIndex = reference->getXPos() + reference->getYPos() *  (*levels)[*(gameController->getActiveLevelIndex())]->cols;
    currentPath = getPathToDest(enemyTileIndex);
    qCInfo(autoplayControllerCat) << "Closest enemy path is: " << currentPath;

    // walk the found path
    walkPath();
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

void AutoPlayController::highlightCurrentPath()
{
    std::for_each((*levels)[*(gameController->getActiveLevelIndex())]->tiles.begin(), (*levels)[*(gameController->getActiveLevelIndex())]->tiles.end(), [this](const auto &tile) {
        tile->resetAutoPlayHighlight();
    });

    int Xindex = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getXPos();
    int Yindex = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getYPos();
    const int cols = (*levels)[*(gameController->getActiveLevelIndex())]->cols;
    foreach (auto & move, currentPath) {
        auto [dx, dy] = move;
        Xindex += dx;
        Yindex += dy;
        const auto tileIndex = Xindex + Yindex * cols;
        (*levels)[*(gameController->getActiveLevelIndex())]->tiles[tileIndex]->setAutoPlayHighlight(true);
    }

}

void AutoPlayController::walkPath()
{
    if(!currentPath.empty()){
        highlightCurrentPath();
        auto move = currentPath[0];
        auto [dx, dy] = move;
        qCInfo(autoplayControllerCat) << "Performing move: " << move;
        gameController->moveProtagonistRelative(dx, dy);
        currentPath.erase(currentPath.begin());
        QTimer::singleShot(1000, this, SLOT(walkPath()));
    }
}
