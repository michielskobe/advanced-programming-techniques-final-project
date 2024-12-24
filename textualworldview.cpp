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

    return gridString;
}
