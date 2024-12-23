#include "textualprotagonistview.h"

TextualProtagonistView::TextualProtagonistView(QTextEdit* textView, TextualWorldView *worldView)
    : textView(textView), worldView(worldView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();

    protagonistView = " ☺ ";
    currentColor = QColor("black");
    connectSlots();

}

void TextualProtagonistView::updateView() {
    // Modify the grid to place the protagonist at the specified coordinates
    QString updatedGrid = worldView->getWorldGrid();

    const int gridWidth = (*levels)[*(gameController->getActiveLevelIndex())]->cols;
    const int xPos = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getXPos();
    const int yPos = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getYPos();

    int rowOffset = yPos*(2*gridWidth*4+4) + (gridWidth*4 + 2);
    int colOffset = xPos * 4 + 2;
    int pos = rowOffset + colOffset;

    updatedGrid.replace(pos-1, 3, protagonistView);

    worldView->setWorldGrid(updatedGrid);
    textView->setPlainText(updatedGrid);

    QTextCursor cursor(textView->document());
    cursor.setPosition(pos-1);
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, 3);

    QTextCharFormat format;
    format.setForeground(currentColor);

    cursor.mergeCharFormat(format);
}

void TextualProtagonistView::connectSlots(){
    QObject::connect(gameController, &GameController::protagonistIdleVisualisation, this, &TextualProtagonistView::updateForIdle);
    QObject::connect(gameController, &GameController::protagonistMoveUpVisualisation, this, &TextualProtagonistView::updateForMoving);
    QObject::connect(gameController, &GameController::protagonistMoveDownVisualisation, this, &TextualProtagonistView::updateForMoving);
    QObject::connect(gameController, &GameController::protagonistMoveLeftVisualisation, this, &TextualProtagonistView::updateForMoving);
    QObject::connect(gameController, &GameController::protagonistMoveRightVisualisation, this, &TextualProtagonistView::updateForMoving);
    QObject::connect(gameController, &GameController::protagonistAttackVisualisation, this, &TextualProtagonistView::updateForAttacking);
    QObject::connect(gameController, &GameController::protagonistHealthVisualisation, this, &TextualProtagonistView::updateForHealthPack);
    QObject::connect(gameController, &GameController::protagonistPoisonVisualisation, this, &TextualProtagonistView::updateForPoisoned);
    QObject::connect(gameController, &GameController::protagonistDeathVisualisation, this, &TextualProtagonistView::updateForDying);

}


void TextualProtagonistView::updateForIdle() {
    if (isDead) return;
    protagonistView = " ☺ ";
    currentColor = QColor("black");
    updateView();
}

void TextualProtagonistView::updateForMoving() {
    if (isDead) return;
    protagonistView = " ☺ ";
    currentColor = QColor("grey");
    updateView();
    QTimer::singleShot(1000, [this]() {
        updateForIdle();
    });
}

void TextualProtagonistView::updateForAttacking() {
    if (isDead) return;
    protagonistView = " ☺/";
    currentColor = QColor("brown");
    updateView();
    QTimer::singleShot(1000, [this]() {
        updateForIdle();
    });
}

void TextualProtagonistView::updateForHealthPack() {
    if (isDead) return;
    protagonistView = " ☺❤";
    currentColor = QColor("red");
    updateView();
    QTimer::singleShot(1000, [this]() {
        updateForIdle();
    });
}

void TextualProtagonistView::updateForPoisoned() {
    if (isDead) return;
    protagonistView = " ☺ ";
    currentColor = QColor("purple");
    updateView();
    QTimer::singleShot(1000, [this]() {
        updateForIdle();
    });
}

void TextualProtagonistView::updateForDying() {
    isDead = true;
    currentColor = QColor("grey");
    protagonistView = " † ";
    updateView();
}
