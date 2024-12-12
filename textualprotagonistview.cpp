#include "textualprotagonistview.h"

TextualProtagonistView::TextualProtagonistView(QTextEdit* textView, QString& grid)
    : textView(textView), grid(grid) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void TextualProtagonistView::updateView() {
    // Modify the grid to place the protagonist at the specified coordinates
    QString updatedGrid = grid;
    const int gridWidth = (*levels)[*(gameController->getActiveLevelIndex())]->cols;
    const int xPos = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getXPos();
    const int yPos = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getYPos();

    int rowOffset = yPos*(2*gridWidth*4+4) + (gridWidth*4 + 2);
    int colOffset = xPos * 4 + 2;
    int pos = rowOffset + colOffset;

    if (pos < updatedGrid.size()) {
        updatedGrid[pos] = 'P';
    }

    textView->setPlainText(updatedGrid);
}
