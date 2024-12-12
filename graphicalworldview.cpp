#include "graphicalworldview.h"

GraphicalWorldView::GraphicalWorldView(QGraphicsScene* scene)
    : scene(scene) {
    QString imageFile =  ":/images/world_images/worldmap.png";
    scene->addPixmap(QPixmap(imageFile))->setScale(50);
}

void GraphicalWorldView::updateView() {
}
