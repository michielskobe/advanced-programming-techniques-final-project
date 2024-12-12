#include "textualworldview.h"

TextualWorldView::TextualWorldView(QTextEdit* textView)
    : textView(textView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void TextualWorldView::updateView() {
    grid = generateTextRepresentation();
    textView->setPlainText(grid);
}

QString& TextualWorldView::getGrid()
{
    return grid;
}

QString TextualWorldView::generateTextRepresentation(){
    const int gridWidth = (*levels)[*(gameController->getActiveLevelIndex())]->cols;
    const int gridHeight = (*levels)[*(gameController->getActiveLevelIndex())]->rows;

    QString gridString;
    for (int y = 0; y < gridHeight; ++y) {
        gridString += QString("+---").repeated(gridWidth) + "+\n"; // Top border
        for (int x = 0; x < gridWidth; ++x) {
            gridString += "|   ";
        }
        gridString += "|\n"; // End of row
    }
    gridString += QString("+---").repeated(gridWidth) + "+\n"; // Bottom border

    return gridString;
}
