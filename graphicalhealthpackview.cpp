#include "graphicalhealthpackview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

GraphicalHealthpackView::GraphicalHealthpackView(QGraphicsScene* scene)
    : GraphicalView(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void GraphicalHealthpackView::updateView() {
    characterPixmapItems.clear();

    for (auto& hp : (*levels)[*(gameController->getActiveLevelIndex())]->healthPacks) {
        characterPixmap = QPixmap(":/images/healthpack.png");
        auto characterPixmapItem = std::make_unique<QGraphicsPixmapItem>(characterPixmap);
        characterPixmapItem->setPos(hp->getXPos() * positionScalingFactor, hp->getYPos() * positionScalingFactor);
        characterPixmapItem->setZValue(3);
        characterPixmapItem->setScale(0.13);
        scene->addItem(characterPixmapItem.get());
        characterPixmapItems.emplace_back(std::move(characterPixmapItem));
    }
}
