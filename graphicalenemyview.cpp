#include "graphicalenemyview.h"
#include "levelmanager.h"
#include "gamecontroller.h"
#include "xenemy.h"
#include "ownenemy.h"
#include "ownpenemy.h"

GraphicalEnemyView::GraphicalEnemyView(QGraphicsScene* scene)
    : GraphicalView {scene} {
}

void GraphicalEnemyView::updateView() {
    characterPixmapItems.clear();

    auto activeLevelIndex = *(gameController->getActiveLevelIndex());
    auto& enemies = (*levels)[activeLevelIndex]->enemies;
    characterPixmapItems.reserve(enemies.size());

    for (auto& enemy : enemies) {
        characterPixmap = enemy->getPixmap();
        auto characterPixmapItem = std::make_unique<QGraphicsPixmapItem>(characterPixmap);
        characterPixmapItem->setPos(enemy->getXPos() * positionScalingFactor, enemy->getYPos() * positionScalingFactor);
        characterPixmapItem->setZValue(4);
        characterPixmapItem->setScale(0.085);
        scene->addItem(characterPixmapItem.get());
        characterPixmapItems.emplace_back(std::move(characterPixmapItem));
    }
}
