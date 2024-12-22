#include "graphicalprotagonistview.h"

GraphicalProtagonistView::GraphicalProtagonistView(QGraphicsScene* scene)
    : scene(scene) {
    levels = LevelManager::GetInstance()->getLevels();
    gameController = GameController::GetInstance();
    initializeProtagonistView();
    connectSlots();
}

void GraphicalProtagonistView::initializeProtagonistView(){
    protagonistPixmap = QPixmap(":/images/Protagonist.png");
    protagonistPixmapItem = new QGraphicsPixmapItem(protagonistPixmap.copy(6, 3, 25, 25));
    protagonistPixmapItem->setPos(0,0);
    protagonistPixmapItem->setZValue(1);
    protagonistPixmapItem->setScale(2.5);
    scene->addItem(protagonistPixmapItem);
}

void GraphicalProtagonistView::connectSlots(){
    QObject::connect(gameController, &GameController::protagonistIdle, this, &GraphicalProtagonistView::updateForIdle);
    QObject::connect(gameController, &GameController::protagonistMove, this, &GraphicalProtagonistView::updateForMoving);
    QObject::connect(gameController, &GameController::protagonistAttack, this, &GraphicalProtagonistView::updateForAttacking);
    QObject::connect(gameController, &GameController::protagonistHealth, this, &GraphicalProtagonistView::updateForHealthPack);
    QObject::connect(gameController, &GameController::protagonistPoison, this, &GraphicalProtagonistView::updateForPoisoned);
    QObject::connect(gameController, &GameController::protagonistDeath, this, &GraphicalProtagonistView::updateForDying);

}

void GraphicalProtagonistView::updateView() {
    auto& levelProtagonist = (*levels)[*(gameController->getActiveLevelIndex())]->protagonist;
    protagonistPixmapItem->setPos(levelProtagonist->getXPos()*50, levelProtagonist->getYPos()*50);
    scene->addItem(protagonistPixmapItem);
}

void GraphicalProtagonistView::updateForIdle() {
    protagonistPixmapItem = new QGraphicsPixmapItem(protagonistPixmap.copy(6, 3, 25, 25));
    protagonistPixmapItem->setScale(2.5);
}

void GraphicalProtagonistView::updateForMoving() {
    protagonistPixmapItem = new QGraphicsPixmapItem(protagonistPixmap.copy(73, 3, 25, 25));
    protagonistPixmapItem->setScale(2.5);
}

void GraphicalProtagonistView::updateForAttacking() {
    protagonistPixmapItem = new QGraphicsPixmapItem(protagonistPixmap.copy(167, 34, 25, 25));
    protagonistPixmapItem->setScale(2.5);
}

void GraphicalProtagonistView::updateForHealthPack() {
    protagonistPixmapItem = new QGraphicsPixmapItem(protagonistPixmap.copy(647, 1, 25, 25));
    protagonistPixmapItem->setScale(2.5);
}

void GraphicalProtagonistView::updateForPoisoned() {
    protagonistPixmapItem = new QGraphicsPixmapItem(protagonistPixmap.copy(712, 2, 25, 25));
    protagonistPixmapItem->setScale(2.5);
}

void GraphicalProtagonistView::updateForDying() {
    protagonistPixmapItem = new QGraphicsPixmapItem(protagonistPixmap.copy(744, 230, 25, 25));
    protagonistPixmapItem->setScale(2.5);
}
