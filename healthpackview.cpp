#include "healthpackview.h"

HealthPackView::HealthPackView(QString healthPackImage) {
    pixmap = new QGraphicsPixmapItem(QPixmap(healthPackImage));
    std::shared_ptr<GraphicRender> healthPackGraphicRender = std::make_shared<GraphicRender>(pixmap);
    std::shared_ptr<TextRender> healthPackTextRender = std::make_shared<TextRender>(new QTextEdit);
    addRenderMethod(healthPackGraphicRender);
    addRenderMethod(healthPackTextRender);
    connectSlots();
    activeRenderMethod = 0;
}

void HealthPackView::renderModel(int xPos, int yPos){
    renderMethods[activeRenderMethod]->render(xPos, yPos);
}

void HealthPackView::connectSlots()
{
}
