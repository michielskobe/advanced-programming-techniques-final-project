#include "graphicalprotagonistview.h"
#include "levelmanager.h"
#include "gamecontroller.h"

GraphicalProtagonistView::GraphicalProtagonistView(QGraphicsScene* scene)
    : GraphicalView(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    connectSlots();

    characterPixmap = QPixmap(":/images/Protagonist.png");
    characterPixmapItem = new QGraphicsPixmapItem(characterPixmap.copy(6, 3, 25, 25));
    characterPixmapItem->setZValue(5);
    characterPixmapItem->setScale(2.4);
    scene->addItem(characterPixmapItem);

    animationTimer = std::make_unique<QTimer>(this);
    connect(animationTimer.get(), &QTimer::timeout, this, [this]() {updateAnimationFrame(animationFrames);});
}

void GraphicalProtagonistView::updateView() {
    auto& levelProtagonist = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist;
    characterPixmapItem->setPos(levelProtagonist->getXPos() * positionScalingFactor, levelProtagonist->getYPos() * positionScalingFactor);
    scene->addItem(characterPixmapItem);
}


void GraphicalProtagonistView::connectSlots() {
    QObject::connect(gameController, &GameController::protagonistIdleVisualisation, this, [this]() { updateForState("Idle"); });
    QObject::connect(gameController, &GameController::protagonistMoveUpVisualisation, this, [this]() { updateForState("MovingUp"); });
    QObject::connect(gameController, &GameController::protagonistMoveDownVisualisation, this, [this]() { updateForState("MovingDown"); });
    QObject::connect(gameController, &GameController::protagonistMoveLeftVisualisation, this, [this]() { updateForState("MovingLeft"); });
    QObject::connect(gameController, &GameController::protagonistMoveRightVisualisation, this, [this]() { updateForState("MovingRight"); });
    QObject::connect(gameController, &GameController::protagonistAttackVisualisation, this, [this]() { updateForState("Attacking"); });
    QObject::connect(gameController, &GameController::protagonistHealthVisualisation, this, [this]() { updateForState("HealthPack"); });
    QObject::connect(gameController, &GameController::protagonistPoisonVisualisation, this, [this]() { updateForState("Poisoned"); });
    QObject::connect(gameController, &GameController::protagonistDeathVisualisation, this, [this]() { updateForState("Dying"); });
}

void GraphicalProtagonistView::updateForState(const QString& state) {
    animationTimer->stop();
    animationFrames.clear();

    const QMap<QString, std::vector<QPixmap>> stateToFrames = {
        {"Idle", {characterPixmap.copy(6, 3, 25, 25)}},
        {"MovingUp", {characterPixmap.copy(70, 132, 25, 25), characterPixmap.copy(134, 132, 25, 25), characterPixmap.copy(70, 132, 25, 25), characterPixmap.copy(6, 3, 25, 25)}},
        {"MovingDown", {characterPixmap.copy(70, 4, 25, 25), characterPixmap.copy(134, 4, 25, 25), characterPixmap.copy(70, 4, 25, 25), characterPixmap.copy(6, 3, 25, 25)}},
        {"MovingLeft", {characterPixmap.copy(70, 196, 25, 25), characterPixmap.copy(134, 196, 25, 25), characterPixmap.copy(70, 196, 25, 25), characterPixmap.copy(6, 3, 25, 25)}},
        {"MovingRight", {characterPixmap.copy(70, 68, 25, 25), characterPixmap.copy(134, 68, 25, 25), characterPixmap.copy(70, 68, 25, 25), characterPixmap.copy(6, 3, 25, 25)}},
        {"Attacking", {characterPixmap.copy(166, 35, 25, 25), characterPixmap.copy(232, 36, 25, 25), characterPixmap.copy(264, 36, 25, 25), characterPixmap.copy(6, 3, 25, 25)}},
        {"HealthPack", {characterPixmap.copy(646, 2, 25, 25), characterPixmap.copy(6, 3, 25, 25)}},
        {"Poisoned", {characterPixmap.copy(712, 2, 25, 25), characterPixmap.copy(6, 3, 25, 25), characterPixmap.copy(712, 2, 25, 25), characterPixmap.copy(6, 3, 25, 25)}},
        {"Dying", {characterPixmap.copy(742, 229, 25, 25)}}
    };

    if (stateToFrames.contains(state)) {
        animationFrames = stateToFrames[state];
        animationTimer->stop();
        if (animationFrames.size() > 1) {
            currentFrame = 0;
            animationTimer->start(150);

        } else {
            animationTimer->stop();
            characterPixmapItem->setPixmap(animationFrames[0]);
        }
    }
}

void GraphicalProtagonistView::updateAnimationFrame(const std::vector<QPixmap>& animationFrames) {
    characterPixmapItem->setPixmap(animationFrames[currentFrame % animationFrames.size()]);
    currentFrame++;
    if (currentFrame >= (int)animationFrames.size()) {
        animationTimer->stop();
    }
}

