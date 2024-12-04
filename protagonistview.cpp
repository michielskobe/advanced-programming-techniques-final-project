#include "protagonistview.h"

ProtagonistView::ProtagonistView(){}

void ProtagonistView::renderModel(int xPos, int yPos) {
    renderMethods[1]->render(xPos, yPos);
}

void ProtagonistView::connectSlots()
{
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels = LevelManager::GetInstance()->getLevels();
    for (int i = 0; i < (int)(*levels).size(); i++) {
        QObject::connect(&(*((*levels)[i]->protagonist)), &Protagonist::posChanged, this, &ProtagonistView::renderModel);
    }
}
