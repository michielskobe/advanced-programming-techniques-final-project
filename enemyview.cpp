#include "enemyview.h"

EnemyView::EnemyView() {}

void EnemyView::renderModel(QGraphicsScene* scene, int xPos, int yPos){
    renderMethods[activeRenderMethod]->render(scene, xPos, yPos);
}
