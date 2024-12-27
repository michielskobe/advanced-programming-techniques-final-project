#include "graphicalenemyview.h"
#include "levelmanager.h"
#include "gamecontroller.h"
#include "xenemy.h"
#include "ownenemy.h"
#include "ownpenemy.h"


GraphicalEnemyView::GraphicalEnemyView(QGraphicsScene* scene)
    : GraphicalView(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void GraphicalEnemyView::updateView() {
    characterPixmapItems.clear();

    for (auto& enemy : (*levels)[*(gameController->getActiveLevelIndex())]->enemies) {

        if (typeid(*enemy) == typeid(OwnPEnemy)) {
            if (enemy->getDefeated()) { characterPixmap = QPixmap(":/images/PEnemy_Dead.png"); }
            else { characterPixmap = QPixmap(":/images/PEnemy_Idle.png"); }
        } else if (typeid(*enemy) == typeid(XEnemy)) {
            if (enemy->getDefeated()) { characterPixmap = QPixmap(":/images/XEnemy_Dead.png"); }
            else { characterPixmap = QPixmap(":/images/XEnemy_Idle.png"); }
        } else {
            if (enemy->getDefeated()) { characterPixmap = QPixmap(":/images/Enemy_Dead.png"); }
            else { characterPixmap = QPixmap(":/images/Enemy_Idle.png"); }
        }

        auto characterPixmapItem = std::make_unique<QGraphicsPixmapItem>(characterPixmap);
        characterPixmapItem->setPos(enemy->getXPos() * positionScalingFactor, enemy->getYPos() * positionScalingFactor);
        characterPixmapItem->setZValue(4);
        characterPixmapItem->setScale(0.085);

        scene->addItem(characterPixmapItem.get());
        characterPixmapItems.emplace_back(std::move(characterPixmapItem));
    }
}
