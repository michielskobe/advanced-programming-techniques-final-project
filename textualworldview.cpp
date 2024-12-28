#include "textualworldview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

TextualWorldView::TextualWorldView(QTextEdit* textView)
    : TextualView(textView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
}

void TextualWorldView::updateView() {
    if (activeLevel != *(gameController->activeLevelIndex)){
        activeLevel = *(gameController->activeLevelIndex);
        textualRepresentation.completeWorldRepresentation = generateTextRepresentation();
    }
    textView->setPlainText(textualRepresentation.completeWorldRepresentation);
}


