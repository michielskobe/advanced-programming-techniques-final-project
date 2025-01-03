#include "autoplaycontroller.h"
#include <unistd.h>
#include <QTimer>
#include "xenemy.h"

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

    auto protagonistDead = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getHealth() <= 0.5f || (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getEnergy() <= 0.5;

    if(state == idle && !protagonistDead){
        state = running;
        auto protHealth = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getHealth();

        if (protHealth >= 25.0f){
            // find closest enemy
            auto closestEnemyIndex = findClosestEnemy();

            if(closestEnemyIndex){
                // find path to the closest enemy
                auto reference = (&(*((*levels)[*(gameController->getActiveLevelIndex())]->enemies[*closestEnemyIndex])));
                auto enemyTileIndex = reference->getXPos() + reference->getYPos() *  (*levels)[*(gameController->getActiveLevelIndex())]->cols;
                currentPath = getPathToDest(enemyTileIndex);
                qCInfo(autoplayControllerCat) << "Closest enemy path is: " << currentPath;
            } else {
                state = stalled;
            }
        } else {
            // find closest enemy
            auto closestHealthPackIndex = findClosestHealthPack();

            if(closestHealthPackIndex){
                // find path to the closest enemy
                auto reference = (&(*((*levels)[*(gameController->getActiveLevelIndex())]->healthPacks[*closestHealthPackIndex])));
                auto healthPackTileIndex = reference->getXPos() + reference->getYPos() *  (*levels)[*(gameController->getActiveLevelIndex())]->cols;
                currentPath = getPathToDest(healthPackTileIndex);
                qCInfo(autoplayControllerCat) << "Closest healthPack path is: " << currentPath;
            } else {
                state = stalled;
            }
        }

        // walk the found path
        walkPath();
    }
}

std::optional<int> AutoPlayController::findClosestEnemy()
{
    float minDistance{1'000'000};
    auto closestEnemy{0};
    bool found{false};
    auto protagonist = &((*levels)[*(gameController->getActiveLevelIndex())]->protagonist);

    for (int i = 0; i < (int)((*levels)[*(gameController->getActiveLevelIndex())]->enemies).size(); i++) {
        auto reference = (&(*((*levels)[*(gameController->getActiveLevelIndex())]->enemies[i])));
        if(typeid(*reference) != typeid(XEnemy) && !reference->getDefeated()){ // no dead enemies and no XEnemy
            auto distance = findDistance(**protagonist, *reference);
            if(distance < minDistance){
                closestEnemy = i;
                minDistance = distance;
                found = true;
            }
        }
    }
    if(!found){
        return std::nullopt;
    }
    return {closestEnemy};
}

std::optional<int> AutoPlayController::findClosestHealthPack()
{
    float minDistance{1'000'000};
    auto closestHealth{0};
    auto protagonist = &((*levels)[*(gameController->getActiveLevelIndex())]->protagonist);

    if(((*levels)[*(gameController->getActiveLevelIndex())]->healthPacks).size() == 0){
        return std::nullopt;
    }

    for (int i = 0; i < (int)((*levels)[*(gameController->getActiveLevelIndex())]->healthPacks).size(); i++) {
        auto reference = (&(*((*levels)[*(gameController->getActiveLevelIndex())]->healthPacks[i])));
        auto distance = findDistance(**protagonist, *reference);
        if(distance < minDistance){
            closestHealth = i;
            minDistance = distance;
        }
    }
    return {closestHealth};
}

float AutoPlayController::findDistance(Tile &t1, Tile &t2)
{
    PathFinderHelper pfHelper = PathFinderHelper();
    const int protagonistIndex = t1.getXPos() + t1.getYPos()*(*levels)[*(gameController->getActiveLevelIndex())]->cols;
    const int destIndex = t2.getXPos() + t2.getYPos()*(*levels)[*(gameController->getActiveLevelIndex())]->cols;
    auto path = pfHelper.getPath((*levels)[*(gameController->getActiveLevelIndex())]->tiles, protagonistIndex, destIndex, (*levels)[*(gameController->getActiveLevelIndex())]->cols);
    return path.size();
    //return std::abs(t1.getXPos() - t2.getXPos()) + std::abs(t1.getYPos() - t2.getYPos());
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
    const int rows = (*levels)[*(gameController->getActiveLevelIndex())]->rows;
    foreach (auto & move, currentPath) {
        auto [dx, dy] = move;
        Xindex += dx;
        Yindex += dy;
        const auto tileIndex = Xindex + Yindex * cols;
        if(tileIndex >= 0 && tileIndex <= rows*cols){
            (*levels)[*(gameController->getActiveLevelIndex())]->tiles[tileIndex]->setAutoPlayHighlight(true);
        }
    }

}

bool AutoPlayController::getActivated() const
{
    return activated;
}

void AutoPlayController::setActivated(bool newActivated)
{
    activated = newActivated;
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
        QTimer::singleShot(100, this, SLOT(walkPath()));
    } else {
        if (state != stalled){
            state = idle;
            if(activated){
                performAction();
            }
        }
    }
}
