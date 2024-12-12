#include "graphicalhealthpackview.h"

GraphicalHealthpackView::GraphicalHealthpackView(QGraphicsScene* scene)
    : scene(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void GraphicalHealthpackView::updateView() {
    for (auto& hp : (*levels)[*(gameController->getActiveLevelIndex())]->healthPacks) {
        QGraphicsPixmapItem* healthpackPixmapItem = new QGraphicsPixmapItem(QPixmap(":/images/healthpack.png"));
        healthpackPixmapItem->setPos(hp->getXPos() * 50, hp->getYPos() * 50);
        healthpackPixmapItem->setZValue(1);
        healthpackPixmapItem->setScale(0.13);
        scene->addItem(healthpackPixmapItem);
        healthpackPixmapItems.append(healthpackPixmapItem);
    }
}
