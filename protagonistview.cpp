#include "protagonistview.h"

ProtagonistView::ProtagonistView(){}

void ProtagonistView::renderModel(int xPos, int yPos) {
    renderMethods[1]->render(xPos, yPos);
}
