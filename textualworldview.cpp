#include "textualworldview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

TextualWorldView::TextualWorldView(QTextEdit* textView)
    : TextualView(textView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    connectSlots();
}

void TextualWorldView::updateView() {
    if (activeLevel != *(gameController->activeLevelIndex)){
        textualRepresentation.firstVisibleRow = 0;
        textualRepresentation.firstVisibleCol = 0;
        activeLevel = *(gameController->activeLevelIndex);
        textualRepresentation.completeWorldRepresentation = generateTextRepresentation();
        textualRepresentation.visibleWorldRepresentation = getVisibleTextRepresentation();
    }
    textView->setPlainText(textualRepresentation.completeWorldRepresentation);
}

