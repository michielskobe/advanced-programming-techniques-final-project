#include "textualhealthpackview.h"
#include "textualworldview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

TextualHealthpackView::TextualHealthpackView(QTextEdit* textView)
    : TextualView(textView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    characterRepresentation = "❤";
}

void TextualHealthpackView::updateView() {
    // Modify the grid to place the healthpack at the specified coordinates
    for (auto& hp :(*levels)[*(gameController->getActiveLevelIndex())]->healthPacks){
        const int xPos = hp->getXPos();
        const int yPos = hp->getYPos();

        if (yPos < textualRepresentation.firstVisibleRow/2 ||
            yPos >= textualRepresentation.firstVisibleRow/2 + textualRepresentation.visibleHeight ||
            xPos < textualRepresentation.firstVisibleCol/4 ||
            xPos >= textualRepresentation.firstVisibleCol/4 + textualRepresentation.visibleWidth) {
            continue;
        }

        const int rowOffset = (1 + 2*yPos - textualRepresentation.firstVisibleRow)*(textualRepresentation.visibleWidth * 4 + 2);
        const int colOffset = 2 + xPos * 4;
        const int pos = rowOffset + colOffset;
        textualRepresentation.visibleWorldRepresentation.replace(pos, 1, characterRepresentation);

    }
    //textView->setPlainText(textualRepresentation.visibleWorldRepresentation);
}
