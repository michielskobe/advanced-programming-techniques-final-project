#include "graphicalprotagonistview.h"

#include "graphicalprotagonistview.h"

GraphicalProtagonistView::GraphicalProtagonistView(QGraphicsScene* scene)
    : scene(scene), currentFrame(0) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    connectSlots();

    protagonistPixmap = QPixmap(":/images/Protagonist.png");
    protagonistPixmapItem = new QGraphicsPixmapItem(protagonistPixmap.copy(6, 3, 25, 25));
    protagonistPixmapItem->setZValue(1);
    protagonistPixmapItem->setScale(2.4);
    scene->addItem(protagonistPixmapItem);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, [this]() {updateAnimationFrame(animationFrames);});
}

void GraphicalProtagonistView::updateView() {
    auto& levelProtagonist = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist;
    protagonistPixmapItem->setPos(levelProtagonist->getXPos() * 50, levelProtagonist->getYPos() * 50);
    scene->addItem(protagonistPixmapItem);
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
        {"Idle", {protagonistPixmap.copy(6, 3, 25, 25)}},
        {"MovingUp", {protagonistPixmap.copy(70, 132, 25, 25), protagonistPixmap.copy(134, 132, 25, 25), protagonistPixmap.copy(70, 132, 25, 25), protagonistPixmap.copy(6, 3, 25, 25)}},
        {"MovingDown", {protagonistPixmap.copy(70, 4, 25, 25), protagonistPixmap.copy(134, 4, 25, 25), protagonistPixmap.copy(70, 4, 25, 25), protagonistPixmap.copy(6, 3, 25, 25)}},
        {"MovingLeft", {protagonistPixmap.copy(70, 196, 25, 25), protagonistPixmap.copy(134, 196, 25, 25), protagonistPixmap.copy(70, 196, 25, 25), protagonistPixmap.copy(6, 3, 25, 25)}},
        {"MovingRight", {protagonistPixmap.copy(70, 68, 25, 25), protagonistPixmap.copy(134, 68, 25, 25), protagonistPixmap.copy(70, 68, 25, 25), protagonistPixmap.copy(6, 3, 25, 25)}},
        {"Attacking", {protagonistPixmap.copy(166, 35, 25, 25), protagonistPixmap.copy(232, 36, 25, 25), protagonistPixmap.copy(264, 36, 25, 25), protagonistPixmap.copy(6, 3, 25, 25)}},
        {"HealthPack", {protagonistPixmap.copy(646, 2, 25, 25), protagonistPixmap.copy(6, 3, 25, 25)}},
        {"Poisoned", {protagonistPixmap.copy(712, 2, 25, 25), protagonistPixmap.copy(6, 3, 25, 25)}},
        {"Dying", {protagonistPixmap.copy(742, 229, 25, 25)}}
    };

    if (stateToFrames.contains(state)) {
        animationFrames = stateToFrames[state];
        animationTimer->stop();
        if (animationFrames.size() > 1) {
            currentFrame = 0;
            animationTimer->start(150);

        } else {
            animationTimer->stop();
            protagonistPixmapItem->setPixmap(animationFrames[0]);
        }
    }
}

void GraphicalProtagonistView::updateAnimationFrame(const std::vector<QPixmap>& animationFrames) {
    protagonistPixmapItem->setPixmap(animationFrames[currentFrame % animationFrames.size()]);
    currentFrame++;
    if (currentFrame >= (int)animationFrames.size()) {
        animationTimer->stop();
    }
}

