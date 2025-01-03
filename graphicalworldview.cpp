#include "graphicalworldview.h"
#include "levelmanager.h"
#include "gamecontroller.h"
#include <QColor>

GraphicalWorldView::GraphicalWorldView(QGraphicsScene* scene)
    : GraphicalView {scene} {
}

void GraphicalWorldView::updateView() {
    // Clear scene
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        scene->removeItem(item);
    }
    characterPixmapItems.clear();
    characterPixmapItems.reserve(3);

    QString imageFile = (*levels)[*(gameController->activeLevelIndex)]->worldImageLocation;
    auto worldPixmapItem = std::make_unique<QGraphicsPixmapItem>(QPixmap(imageFile));
    worldPixmapItem->setScale(positionScalingFactor);
    worldPixmapItem->setZValue(0);
    scene->addItem(worldPixmapItem.get());
    characterPixmapItems.emplace_back(std::move(worldPixmapItem));

    const auto& tiles = (*levels)[*(gameController->activeLevelIndex)]->tiles;
    std::for_each(tiles.begin(), tiles.end(), [this](const auto &tile) {
        if (tile->damageMultiplier > 0) {
            const int x = tile->getXPos();
            const int y = tile->getYPos();
            auto rect = std::make_unique<QGraphicsRectItem>(x * positionScalingFactor, y * positionScalingFactor, positionScalingFactor, positionScalingFactor);
            QBrush brush(QColor(255*tile->getValue(), 0, 255*tile->getValue()));
            rect->setBrush(brush);
            rect->setZValue(2);
            rect->setPen(Qt::NoPen);
            scene->addItem(rect.release());
        }
        if(tile->getAutoPlayHighlight()){
            const int x = tile->getXPos();
            const int y = tile->getYPos();
            auto rect = std::make_unique<QGraphicsRectItem>(x * positionScalingFactor, y * positionScalingFactor, positionScalingFactor, positionScalingFactor);
            QBrush brush(QColor(0, 255*tile->getValue(), 255*tile->getValue()));
            rect->setBrush(brush);
            rect->setZValue(2);
            rect->setPen(Qt::NoPen);
            scene->addItem(rect.release());
        }
    });

    auto portalIn = std::make_unique<QGraphicsPixmapItem>(QPixmap(":/images/portal_in.png"));
    auto portalOut = std::make_unique<QGraphicsPixmapItem>(QPixmap(":/images/portal_out.png"));

    portalIn->setZValue(4);
    portalIn->setPos(8*positionScalingFactor, 2*positionScalingFactor);
    portalIn->setScale(0.26);

    portalOut->setZValue(4);
    portalOut->setPos(0,0);
    portalOut->setScale(0.26);

    scene->addItem(portalIn.get());
    scene->addItem(portalOut.get());

    characterPixmapItems.emplace_back(std::move(portalIn));
    characterPixmapItems.emplace_back(std::move(portalOut));
}
