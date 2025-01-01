#include "textualworldview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

TextualWorldView::TextualWorldView(QTextEdit* textView)
    : TextualView(textView) {
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
    textualRepresentation.visibleWorldRepresentation = getVisibleTextRepresentation();
    textView->setPlainText(textualRepresentation.visibleWorldRepresentation);
}

