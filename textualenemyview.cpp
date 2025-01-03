#include "textualenemyview.h"
#include "levelmanager.h"
#include "gamecontroller.h"
#include "ownpenemy.h"
#include "xenemy.h"

TextualEnemyView::TextualEnemyView(QTextEdit* textView)
    : TextualView {textView} {
}

void TextualEnemyView::updateView() {
    // Modify the grid to place the enemy at the specified coordinates
    textualRepresentation.visibleWorldRepresentation.replace("X", " "); // Only X enemy needs to be removed, other enemies keep position and are overwritten

    for (auto& enemy :(*levels)[*(gameController->getActiveLevelIndex())]->enemies){
        const int xPos = enemy->getXPos();
        const int yPos = enemy->getYPos();

        if (yPos < textualRepresentation.firstVisibleRow/2 ||
            yPos >= textualRepresentation.firstVisibleRow/2 + textualRepresentation.visibleHeight ||
            xPos < textualRepresentation.firstVisibleCol/4 ||
            xPos >= textualRepresentation.firstVisibleCol/4 + textualRepresentation.visibleWidth) {
            continue;
        }

        const int rowOffset = (1 + 2*yPos - textualRepresentation.firstVisibleRow)*(textualRepresentation.visibleWidth * 4 + 2);
        const int colOffset = 2 + xPos * 4 - textualRepresentation.firstVisibleCol;
        const int pos = rowOffset + colOffset;

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


        textualRepresentation.visibleWorldRepresentation.replace(pos, 1, characterRepresentation);
    }
    textView->setPlainText(textualRepresentation.visibleWorldRepresentation);
}
