#include "tileview.h"

TileView::TileView() {}

void TileView::renderModel(QGraphicsScene* scene, int xPos, int yPos){
    renderMethods[activeRenderMethod]->render(scene, xPos, yPos);
}
