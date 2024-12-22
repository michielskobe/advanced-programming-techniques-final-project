#include "graphicalprotagonistview.h"

GraphicalProtagonistView::GraphicalProtagonistView(QGraphicsScene* scene)
    : scene(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    initializeProtagonistView();
    connectSlots();

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, [this]() {updateAnimationFrame(firstAnimationFrame, secondAnimationFrame, thirdAnimationFrame);});
}

void GraphicalProtagonistView::initializeProtagonistView(){
    protagonistPixmap = QPixmap(":/images/Protagonist.png");
    protagonistPixmapItem = new QGraphicsPixmapItem(protagonistPixmap.copy(6, 3, 25, 25));
    protagonistPixmapItem->setPos(0,0);
    protagonistPixmapItem->setZValue(1);
    protagonistPixmapItem->setScale(2.4);
    scene->addItem(protagonistPixmapItem);
}

void GraphicalProtagonistView::connectSlots(){
    QObject::connect(gameController, &GameController::protagonistIdleVisualisation, this, &GraphicalProtagonistView::updateForIdle);
    QObject::connect(gameController, &GameController::protagonistMoveUpVisualisation, this, &GraphicalProtagonistView::updateForMovingUp);
    QObject::connect(gameController, &GameController::protagonistMoveDownVisualisation, this, &GraphicalProtagonistView::updateForMovingDown);
    QObject::connect(gameController, &GameController::protagonistMoveLeftVisualisation, this, &GraphicalProtagonistView::updateForMovingLeft);
    QObject::connect(gameController, &GameController::protagonistMoveRightVisualisation, this, &GraphicalProtagonistView::updateForMovingRight);
    QObject::connect(gameController, &GameController::protagonistAttackVisualisation, this, &GraphicalProtagonistView::updateForAttacking);
    QObject::connect(gameController, &GameController::protagonistHealthVisualisation, this, &GraphicalProtagonistView::updateForHealthPack);
    QObject::connect(gameController, &GameController::protagonistPoisonVisualisation, this, &GraphicalProtagonistView::updateForPoisoned);
    QObject::connect(gameController, &GameController::protagonistDeathVisualisation, this, &GraphicalProtagonistView::updateForDying);

}

void GraphicalProtagonistView::updateView() {
    auto& levelProtagonist = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist;
    protagonistPixmapItem->setPos(levelProtagonist->getXPos()*50, levelProtagonist->getYPos()*50);
    scene->addItem(protagonistPixmapItem);
}

void GraphicalProtagonistView::updateForIdle() {
    animationTimer->stop();
    protagonistPixmapItem->setPixmap(protagonistPixmap.copy(6, 4, 25, 25));
}

void GraphicalProtagonistView::updateForMovingUp() {
    animationTimer->stop();
    animationTimer->start(150);
    firstAnimationFrame = protagonistPixmap.copy(70, 132, 25, 25);
    secondAnimationFrame = protagonistPixmap.copy(134, 132, 25, 25);
    thirdAnimationFrame = firstAnimationFrame;
    currentFrame = 0;
}

void GraphicalProtagonistView::updateForMovingDown() {
    animationTimer->stop();
    animationTimer->start(150);
    firstAnimationFrame = protagonistPixmap.copy(70, 4, 25, 25);
    secondAnimationFrame = protagonistPixmap.copy(134, 4, 25, 25);
    thirdAnimationFrame = firstAnimationFrame;
    currentFrame = 0;
}

void GraphicalProtagonistView::updateForMovingLeft() {
    animationTimer->stop();
    animationTimer->start(150);
    firstAnimationFrame = protagonistPixmap.copy(70, 196, 25, 25);
    secondAnimationFrame = protagonistPixmap.copy(134, 196, 25, 25);
    thirdAnimationFrame = firstAnimationFrame;
    currentFrame = 0;
}

void GraphicalProtagonistView::updateForMovingRight() {
    animationTimer->stop();
    animationTimer->start(150);
    firstAnimationFrame = protagonistPixmap.copy(70, 68, 25, 25);
    secondAnimationFrame = protagonistPixmap.copy(134, 68, 25, 25);
    thirdAnimationFrame = firstAnimationFrame;
    currentFrame = 0;
}

void GraphicalProtagonistView::updateForAttacking() {
    animationTimer->stop();
    animationTimer->start(150);
    firstAnimationFrame = protagonistPixmap.copy(166, 35, 25, 25);
    secondAnimationFrame = protagonistPixmap.copy(232, 36, 25, 25);
    thirdAnimationFrame = protagonistPixmap.copy(264, 36, 25, 25);
    currentFrame = 0;
}

void GraphicalProtagonistView::updateForHealthPack() {
    animationTimer->stop();
    protagonistPixmapItem->setPixmap(protagonistPixmap.copy(646, 2, 25, 25));
}

void GraphicalProtagonistView::updateForPoisoned() {
    animationTimer->stop();
    protagonistPixmapItem->setPixmap(protagonistPixmap.copy(712, 2, 25, 25));
}

void GraphicalProtagonistView::updateForDying() {
    animationTimer->stop();
    protagonistPixmapItem->setPixmap(protagonistPixmap.copy(742, 229, 25, 25));
}

void GraphicalProtagonistView::updateAnimationFrame(QPixmap firstAnimationFrame, QPixmap secondAnimationFrame, QPixmap thirdAnimationFrame) {
    if (currentFrame == 0) {
        protagonistPixmapItem->setPixmap(firstAnimationFrame);
        currentFrame++;
    } else if (currentFrame == 1){
        protagonistPixmapItem->setPixmap(secondAnimationFrame);
        currentFrame++;
    } else {
        protagonistPixmapItem->setPixmap(thirdAnimationFrame);
    }
}
