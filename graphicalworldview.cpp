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
    // Clear scene
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(item);
        if (pixmapItem) {
            scene->removeItem(pixmapItem);
        }
    }

    QString imageFile = (*levels)[*(gameController->activeLevelIndex)]->worldImageLocation;
    QImage image(imageFile);
    QPixmap modifiedPixmap = QPixmap::fromImage(image);
    scene->addPixmap(modifiedPixmap)->setScale(positionScalingFactor);

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            const int index = x + y * ((*levels)[*(gameController->activeLevelIndex)]->cols);
            auto tile = ((*levels)[*(gameController->activeLevelIndex)]->tiles)[index].get();
            const int poisonDmg = tile->damageMultiplier;
            if (poisonDmg) {
                QGraphicsRectItem *rect = new QGraphicsRectItem(x*positionScalingFactor, y*positionScalingFactor, positionScalingFactor, positionScalingFactor);
                QColor color = image.pixelColor(x, y);
                int intensity = (color.red() + color.green() + color.blue()) / 3;
                QBrush brush(QColor(intensity, 0, intensity));
                rect->setBrush(brush);
                rect->setZValue(2);
                rect->setPen(Qt::NoPen);
                scene->addItem(rect);
            }
        }
    }
}
