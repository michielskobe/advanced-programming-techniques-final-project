#include "graphicalworldview.h"
#include <QImage>
#include <QColor>
#include "levelmanager.h"
#include "gamecontroller.h"

GraphicalWorldView::GraphicalWorldView(QGraphicsScene* scene)
    : GraphicalView(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void GraphicalWorldView::updateView() {
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        // Check if the item is a QGraphicsPixmapItem
        QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(item);
        if (pixmapItem) {
            scene->removeItem(pixmapItem);
        }
    }

    QString imageFile = (*levels)[*(gameController->activeLevelIndex)]->worldImageLocation;
    QImage image(imageFile);

    QPixmap modifiedPixmap = QPixmap::fromImage(image);
    scene->addPixmap(modifiedPixmap)->setScale(positionScalingFactor);
}

