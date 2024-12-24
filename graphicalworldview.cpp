#include "graphicalworldview.h"
#include <QImage>
#include <QColor>

GraphicalWorldView::GraphicalWorldView(QGraphicsScene* scene)
    : GraphicalView(scene) {
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

    QString imageFile = ":/images/world_images/worldmap.png";
    QImage image(imageFile);

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QColor color = image.pixelColor(x, y);
            int intensity = (color.red() + color.green() + color.blue()) / 3;
            QColor greenShade(0, intensity, 0);
            image.setPixelColor(x, y, greenShade);
        }
    }

    QPixmap modifiedPixmap = QPixmap::fromImage(image);
    scene->addPixmap(modifiedPixmap)->setScale(positionScalingFactor);
}
