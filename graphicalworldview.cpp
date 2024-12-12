#include "graphicalworldview.h"

GraphicalWorldView::GraphicalWorldView(QGraphicsScene* scene)
    : scene(scene) {
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
    QString imageFile =  ":/images/world_images/worldmap.png";
    scene->addPixmap(QPixmap(imageFile))->setScale(50);
}
