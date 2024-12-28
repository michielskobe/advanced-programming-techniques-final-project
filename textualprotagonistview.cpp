#include "textualprotagonistview.h"
#include "textualworldview.h"
#include "levelmanager.h"
#include "gamecontroller.h"
#include <QTimer>

TextualProtagonistView::TextualProtagonistView(QTextEdit* textView)
    : TextualView(textView) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    characterRepresentation = " ☺ ";
    connectSlots();
}


void TextualProtagonistView::updateView() {
    worldGrid.replace(characterRepresentation, "   ");
    const int gridWidth = (*levels)[*(gameController->getActiveLevelIndex())]->cols;
    const int xPos = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getXPos();
    const int yPos = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getYPos();

    const int rowOffset = yPos * (2 * gridWidth * 4 + 4) + (gridWidth * 4 + 2);
    const int colOffset = xPos * 4 + 2;
    const int pos = rowOffset + colOffset;

    worldGrid.replace(pos - 1, 3, characterRepresentation);

    textView->setPlainText(worldGrid);

    QTextCursor cursor(textView->document());
    cursor.setPosition(pos - 1);
    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, 3);

    QTextCharFormat format;
    format.setForeground(currentColor);

    cursor.mergeCharFormat(format);
}

void TextualProtagonistView::connectSlots() {
    QObject::connect(gameController, &GameController::protagonistIdleVisualisation, this, [this]() { updateForState("Idle"); });
    QObject::connect(gameController, &GameController::protagonistMoveUpVisualisation, this, [this]() { updateForState("Moving"); });
    QObject::connect(gameController, &GameController::protagonistMoveDownVisualisation, this, [this]() { updateForState("Moving"); });
    QObject::connect(gameController, &GameController::protagonistMoveLeftVisualisation, this, [this]() { updateForState("Moving"); });
    QObject::connect(gameController, &GameController::protagonistMoveRightVisualisation, this, [this]() { updateForState("Moving"); });
    QObject::connect(gameController, &GameController::protagonistAttackVisualisation, this, [this]() { updateForState("Attacking"); });
    QObject::connect(gameController, &GameController::protagonistHealthVisualisation, this, [this]() { updateForState("HealthPack"); });
    QObject::connect(gameController, &GameController::protagonistPoisonVisualisation, this, [this]() { updateForState("Poisoned"); });
    QObject::connect(gameController, &GameController::protagonistDeathVisualisation, this, [this]() { updateForState("Dying"); });
}

void TextualProtagonistView::updateForState(const QString& state) {
    if (isDead && state != "Dying") return;

    if (state == "Idle") {
        currentColor = QColor("black");
        characterRepresentation = " ☺ ";
    } else if (state == "Moving") {
        currentColor = QColor("grey");
        characterRepresentation = " ☺ ";
    } else if (state == "Attacking") {
        currentColor = QColor("brown");
        characterRepresentation = " ☺/";
    } else if (state == "HealthPack") {
        currentColor = QColor("red");
        characterRepresentation = " ☺❤";
    } else if (state == "Poisoned") {
        currentColor = QColor("green");
        characterRepresentation = " @ ";
    } else if (state == "Dying") {
        isDead = true;
        currentColor = QColor("grey");
        characterRepresentation = " † ";
    }
    updateView();
    QTimer::singleShot(2000, [this]() {
        updateForState("Idle");
    });

}
