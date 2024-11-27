#include "protagonistview.h"

ProtagonistView::ProtagonistView(QGraphicsScene* scene)
    : m_scene(scene){}

void ProtagonistView::renderModel(QGraphicsScene* scene, int xPos, int yPos) {
    renderMethods[1]->render(scene, xPos, yPos);
}
