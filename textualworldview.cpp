#include "textualworldview.h"

TextualWorldView::TextualWorldView(QTextEdit* textView)
    : textView(textView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    QString textRepresentation = generateTextRepresentation();
    textView->setPlainText(textRepresentation);

}

void TextualWorldView::updateView() {}


QString TextualWorldView::generateTextRepresentation(){
    const int gridWidth = (*levels)[*(gameController->activeLevelIndex)]->cols;
    const int gridHeight = (*levels)[*(gameController->activeLevelIndex)]->rows;
    QVector<QVector<QString>> grid(gridHeight, QVector<QString>(gridWidth, " "));

    QString gridString;
    for (int y = 0; y < gridHeight; ++y) {
        gridString += QString("+---").repeated(gridWidth) + "+\n"; // Top border
        for (int x = 0; x < gridWidth; ++x) {
            gridString += "| " + grid[y][x] + " ";
        }
        gridString += "|\n"; // End of row
    }
    gridString += QString("+---").repeated(gridWidth) + "+\n"; // Bottom border

    return gridString;
}
