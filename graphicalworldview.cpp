#include "graphicalworldview.h"

GraphicalWorldView::GraphicalWorldView(QGraphicsScene* scene)
    : scene(scene) {
}

void GraphicalWorldView::updateView() {
    QString imageFile =  ":/images/world_images/worldmap.png";
    scene->clear();
    scene->addPixmap(QPixmap(imageFile))->setScale(50);
}
