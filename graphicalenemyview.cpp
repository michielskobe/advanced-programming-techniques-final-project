#include "graphicalenemyview.h"
#include "xenemy.h"

GraphicalEnemyView::GraphicalEnemyView(QGraphicsScene* scene)
    : scene(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void GraphicalEnemyView::updateView() {
    for (auto& enemy : (*levels)[*(gameController->getActiveLevelIndex())]->enemies) {
        QString image = ":/images/test2.jpg";
        auto temp = dynamic_cast<PEnemy*>(&(*enemy));
        if (temp != nullptr){
            image = ":/images/enemy.png";
        }
        auto temp2 = dynamic_cast<XEnemy*>(&(*enemy));
        if (temp2 != nullptr){
            image = ":/images/XEnemy.png";
        }

        QGraphicsPixmapItem* enemyPixmapItem = new QGraphicsPixmapItem(QPixmap(image));
        enemyPixmapItem->setPos(enemy->getXPos() * 50, enemy->getYPos() * 50);
        enemyPixmapItem->setZValue(1);
        enemyPixmapItem->setScale(0.09);
        scene->addItem(enemyPixmapItem);
        enemyPixmapItems.append(enemyPixmapItem);
    }
}
