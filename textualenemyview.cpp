#include "textualenemyview.h"
#include "textualworldview.h"
#include "levelmanager.h"
#include "gamecontroller.h"
#include "ownpenemy.h"
#include "xenemy.h"

TextualEnemyView::TextualEnemyView(QTextEdit* textView, TextualWorldView *worldView)
    : TextualView(textView), worldView(worldView) {
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

        if (typeid(*enemy) == typeid(OwnPEnemy)) {
            characterRepresentation = "P";
        } else if (typeid(*enemy) == typeid(XEnemy)) {
            characterRepresentation = "X";
        } else {
            characterRepresentation = "E";
        }

        if (enemy->getDefeated()){
            characterRepresentation = characterRepresentation.toLower();
        }

        updatedGrid.replace(pos, 1, characterRepresentation);
    }

    worldView->setWorldGrid(updatedGrid);
    textView->setPlainText(updatedGrid);
}
