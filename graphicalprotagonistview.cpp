#include "graphicalprotagonistview.h"

GraphicalProtagonistView::GraphicalProtagonistView(QGraphicsScene* scene)
    : scene(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    protagonistPixmapItem = new QGraphicsPixmapItem(QPixmap(":/images/protagonist.png"));
    protagonistPixmapItem->setPos(0,0);
    protagonistPixmapItem->setZValue(1);
    protagonistPixmapItem->setScale(0.2);
    scene->addItem(protagonistPixmapItem);
    scene->update();
}

void GraphicalProtagonistView::updateView() {
    auto& levelProtagonist = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist;
    protagonistPixmapItem->setPos(levelProtagonist->getXPos()*50, levelProtagonist->getYPos()*50);
    scene->addItem(protagonistPixmapItem);
}
