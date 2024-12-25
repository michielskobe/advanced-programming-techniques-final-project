#include "graphicaloverlayview.h"

GraphicalOverlayView::GraphicalOverlayView(QGraphicsScene* scene)
    : GraphicalView(scene) {
    characterPixmapItem = new QGraphicsPixmapItem(QPixmap(":/images/overlay_images/worldmap.png"));
    characterPixmapItem->setScale(positionScalingFactor);
    characterPixmapItem->setZValue(0.5);
    characterPixmapItem->setVisible(false);
}

void GraphicalOverlayView::updateView(){
    if (overlayStatus){
        characterPixmapItem->setVisible(true);
    } else {
        characterPixmapItem->setVisible(false);
    }
    scene->addItem(characterPixmapItem);
}


void GraphicalOverlayView::switchOverlayStatus()
{
    overlayStatus = overlayStatus ? false : true;
}

bool GraphicalOverlayView::getOverlayStatus() const
{
    return overlayStatus;
}
