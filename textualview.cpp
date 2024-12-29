#include "textualview.h"
#include "levelmanager.h"
#include "gamecontroller.h"
#include <QDebug>
#include <QtLogging>
#include <QLoggingCategory>
TextualRepresentation textualRepresentation;

TextualView::TextualView(QTextEdit* textView)
    :textView(textView)
{
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    textualRepresentation.completeWorldRepresentation = generateTextRepresentation();
    textualRepresentation.visibleWorldRepresentation = "";
    textualRepresentation.visibleWidth = 15;
    textualRepresentation.visibleHeight = 15;
    textualRepresentation.firstVisibleRow = 0;
    textualRepresentation.firstVisibleCol = 0;
}

void TextualView::connectSlots() {
    qInfo() << "Connecting slots for TextualView";
    QObject::connect(gameController, &GameController::textualWorldMoveUp, this, &TextualView::moveVisibleViewUp, Qt::UniqueConnection);
    QObject::connect(gameController, &GameController::textualWorldMoveDown, this, &TextualView::moveVisibleViewDown, Qt::UniqueConnection);
    QObject::connect(gameController, &GameController::textualWorldMoveLeft, this, &TextualView::moveVisibleViewLeft, Qt::UniqueConnection);
    QObject::connect(gameController, &GameController::textualWorldMoveRight, this, &TextualView::moveVisibleViewRight, Qt::UniqueConnection);
}

QString TextualView::generateTextRepresentation(){
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

QString TextualView::getVisibleTextRepresentation(){
    QString worldString = textualRepresentation.completeWorldRepresentation;
    QString displayedWorld;
    QStringList rowList = worldString.split('\n');
    const int nrOfRowCharacters = 4 * textualRepresentation.visibleWidth;
    const int nrOfColCharacters = 2 * textualRepresentation.visibleHeight;
    for (int i = textualRepresentation.firstVisibleRow; i <= textualRepresentation.firstVisibleRow + nrOfColCharacters && i < rowList.size(); ++i) {
        QString row = rowList[i];
        displayedWorld += row.mid(textualRepresentation.firstVisibleCol, nrOfRowCharacters + 1) + "\n";
    }

    return displayedWorld;
}


void TextualView::moveVisibleViewUp()
{
    textualRepresentation.firstVisibleRow -= 2;
    textualRepresentation.visibleWorldRepresentation = getVisibleTextRepresentation();
}

void TextualView::moveVisibleViewDown()
{
    textualRepresentation.firstVisibleRow += 2;
    textualRepresentation.visibleWorldRepresentation = getVisibleTextRepresentation();

}

void TextualView::moveVisibleViewLeft()
{

    textualRepresentation.firstVisibleCol -= 4;
    textualRepresentation.visibleWorldRepresentation = getVisibleTextRepresentation();
}

void TextualView::moveVisibleViewRight()
{
    textualRepresentation.firstVisibleCol += 4;
    textualRepresentation.visibleWorldRepresentation = getVisibleTextRepresentation();
}

