#include "graphicalenemyview.h"

GraphicalEnemyView::GraphicalEnemyView(QGraphicsScene* scene)
    : scene(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void GraphicalEnemyView::updateView() {
    for (auto& enemy : (*levels)[*(gameController->getActiveLevelIndex())]->enemies) {
        QGraphicsPixmapItem* enemyPixmapItem = new QGraphicsPixmapItem(QPixmap(":/images/enemy.png"));
        enemyPixmapItem->setPos(enemy->getXPos() * 50, enemy->getYPos() * 50);
        enemyPixmapItem->setZValue(1);
        enemyPixmapItem->setScale(0.09);
        scene->addItem(enemyPixmapItem);
        enemyPixmapItems.append(enemyPixmapItem);
    }
}
