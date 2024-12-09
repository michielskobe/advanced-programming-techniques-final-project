#include "enemyview.h"

EnemyView::EnemyView(QString enemyImage) {
    pixmap = new QGraphicsPixmapItem(QPixmap(enemyImage));
    std::shared_ptr<GraphicRender> enemyGraphicRender = std::make_shared<GraphicRender>(pixmap);
    std::shared_ptr<TextRender> enemyTextRender = std::make_shared<TextRender>(new QTextEdit);
    addRenderMethod(enemyGraphicRender);
    addRenderMethod(enemyTextRender);
    connectSlots();
    activeRenderMethod = 0;
}

void EnemyView::renderModel(int xPos, int yPos){
    renderMethods[activeRenderMethod]->render(xPos, yPos);
}

void EnemyView::connectSlots()
{
}
