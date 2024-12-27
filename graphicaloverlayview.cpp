#include "graphicaloverlayview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

GraphicalOverlayView::GraphicalOverlayView(QGraphicsScene* scene)
    : GraphicalView(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    QString imageFile = (*levels)[*(gameController->activeLevelIndex)]->worldOverlayLocation;
    characterPixmapItem = std::make_unique<QGraphicsPixmapItem>(QPixmap(imageFile));
}

void GraphicalOverlayView::updateView(){
    QString imageFile = (*levels)[*(gameController->activeLevelIndex)]->worldOverlayLocation;
    characterPixmapItem = std::make_unique<QGraphicsPixmapItem>(QPixmap(imageFile));
    characterPixmapItem->setScale(positionScalingFactor);
    characterPixmapItem->setZValue(1);
    if (overlayStatus){
        characterPixmapItem->setVisible(true);
    } else {
        characterPixmapItem->setVisible(false);
    }
    scene->addItem(characterPixmapItem.get());
}


void GraphicalOverlayView::switchOverlayStatus()
{
    overlayStatus = overlayStatus ? false : true;
}

bool GraphicalOverlayView::getOverlayStatus() const
{
    return overlayStatus;
}
