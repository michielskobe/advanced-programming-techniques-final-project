#include "textualworldview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

TextualWorldView::TextualWorldView(QTextEdit* textView)
    : TextualView(textView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void TextualWorldView::updateView() {
    worldGrid = generateTextRepresentation();
    textView->setPlainText(worldGrid);
}

QString& TextualWorldView::getWorldGrid()
{
    return worldGrid;
}

void TextualWorldView::setWorldGrid(const QString &newWorldGrid)
{
    worldGrid = newWorldGrid;
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

    // Visualise level switching portal
    const int pos = 2 * (8 * gridWidth + 4) + (gridWidth * 4 + 2) + 33; // Calculated based on character position formula, indicates start of 3-character portal tile
    gridString.replace(pos, 3, "[║]");

    return gridString;
}
