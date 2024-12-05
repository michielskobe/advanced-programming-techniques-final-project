#include "protagonistview.h"

ProtagonistView::ProtagonistView(QString protagonistImage){
    pixmap = new QGraphicsPixmapItem(QPixmap(protagonistImage));
    std::shared_ptr<GraphicRender> protagonistGraphicRender = std::make_shared<GraphicRender>(pixmap);
    std::shared_ptr<TextRender> protagonistTextRender = std::make_shared<TextRender>(new QTextEdit);
    addRenderMethod(protagonistGraphicRender);
    addRenderMethod(protagonistTextRender);
    connectSlots();
    activeRenderMethod = 0;
}

void ProtagonistView::renderModel(int xPos, int yPos) {
    renderMethods[activeRenderMethod]->render(xPos, yPos);
}

void ProtagonistView::connectSlots()
{
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels = LevelManager::GetInstance()->getLevels();
    for (int i = 0; i < (int)(*levels).size(); i++) {
        QObject::connect(&(*((*levels)[i]->protagonist)), &Protagonist::posChanged, this, &ProtagonistView::renderModel);
    }
}
