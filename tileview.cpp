#include "tileview.h"

TileView::TileView() {}

void TileView::renderModel(int xPos, int yPos){
    renderMethods[activeRenderMethod]->render(xPos, yPos);
}
