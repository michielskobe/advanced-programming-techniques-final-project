#include "enemyview.h"

EnemyView::EnemyView() {}

void EnemyView::renderModel(int xPos, int yPos){
    renderMethods[activeRenderMethod]->render(xPos, yPos);
}

void EnemyView::connectSlots()
{}
