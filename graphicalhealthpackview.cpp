#include "graphicalhealthpackview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

GraphicalHealthpackView::GraphicalHealthpackView(QGraphicsScene* scene)
    : GraphicalView(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void GraphicalHealthpackView::updateView() {
    for (auto& hp : (*levels)[*(gameController->getActiveLevelIndex())]->healthPacks) {
        characterPixmap = QPixmap(":/images/healthpack.png");
        QGraphicsPixmapItem* characterPixmapItem = new QGraphicsPixmapItem(characterPixmap);
        characterPixmapItem->setPos(hp->getXPos() * positionScalingFactor, hp->getYPos() * positionScalingFactor);
        characterPixmapItem->setZValue(1);
        characterPixmapItem->setScale(0.13);
        scene->addItem(characterPixmapItem);
        characterPixmapItems.emplace_back(characterPixmapItem);
    }
}
