#include "textualhealthpackview.h"

TextualHealthpackView::TextualHealthpackView(QTextEdit* textView, TextualWorldView *worldView)
    : textView(textView), worldView(worldView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void TextualHealthpackView::updateView() {
    // Modify the grid to place the healthpack at the specified coordinates
    QString updatedGrid = worldView->getWorldGrid();
    const int gridWidth = (*levels)[*(gameController->getActiveLevelIndex())]->cols;

    for (auto& hp :(*levels)[*(gameController->getActiveLevelIndex())]->healthPacks){
        const int xPos = hp->getXPos();
        const int yPos = hp->getYPos();

        int rowOffset = yPos*(2*gridWidth*4+4) + (gridWidth*4 + 2);
        int colOffset = xPos * 4 + 2;
        int pos = rowOffset + colOffset;

        QString healthView = "❤";
        updatedGrid.replace(pos, 1, healthView);
    }

    worldView->setWorldGrid(updatedGrid);
    textView->setPlainText(updatedGrid);
}
