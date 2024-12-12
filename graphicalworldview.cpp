#include "graphicalworldview.h"

GraphicalWorldView::GraphicalWorldView(QGraphicsScene* scene, const QString& imageFile)
    : scene(scene) {
    scene->clear();
    scene->addPixmap(QPixmap(imageFile))->setScale(50);
}

void GraphicalWorldView::updateView() {}
