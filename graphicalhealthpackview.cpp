#include "graphicalhealthpackview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

GraphicalHealthpackView::GraphicalHealthpackView(QGraphicsScene* scene)
    : GraphicalView {scene} {
    characterPixmap = QPixmap(":/images/healthpack.png");
}

void GraphicalHealthpackView::updateView() {
    characterPixmapItems.clear();

    auto activeLevelIndex = *(gameController->getActiveLevelIndex());
    auto& healthPacks = (*levels)[activeLevelIndex]->healthPacks;
    characterPixmapItems.reserve(healthPacks.size());

    for (auto& hp : healthPacks) {
        auto characterPixmapItem = std::make_unique<QGraphicsPixmapItem>(characterPixmap);
        characterPixmapItem->setPos(hp->getXPos() * positionScalingFactor, hp->getYPos() * positionScalingFactor);
        characterPixmapItem->setZValue(3);
        characterPixmapItem->setScale(0.13);
        scene->addItem(characterPixmapItem.get());
        characterPixmapItems.emplace_back(std::move(characterPixmapItem));
    }
}
