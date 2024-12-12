#include "textualenemyview.h"

TextualEnemyView::TextualEnemyView(QTextEdit* textView, TextualWorldView *worldView)
    : textView(textView), worldView(worldView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void TextualEnemyView::updateView() {
    // Modify the grid to place the enemy at the specified coordinates
    QString updatedGrid = worldView->getWorldGrid();
    const int gridWidth = (*levels)[*(gameController->getActiveLevelIndex())]->cols;

    for (auto& enemy :(*levels)[*(gameController->getActiveLevelIndex())]->enemies){
        const int xPos = enemy->getXPos();
        const int yPos = enemy->getYPos();

        int rowOffset = yPos*(2*gridWidth*4+4) + (gridWidth*4 + 2);
        int colOffset = xPos * 4 + 2;
        int pos = rowOffset + colOffset;

        if (pos < updatedGrid.size()) {
            updatedGrid[pos] = 'E';
        }
    }

    worldView->setWorldGrid(updatedGrid);
    textView->setPlainText(updatedGrid);
}
