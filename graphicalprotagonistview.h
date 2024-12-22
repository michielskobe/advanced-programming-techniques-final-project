#ifndef GRAPHICALPROTAGONISTVIEW_H
#define GRAPHICALPROTAGONISTVIEW_H

#include "protagonistview.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTimer>

class GraphicalProtagonistView : public QObject, public ProtagonistView
{
    Q_OBJECT
public:
    GraphicalProtagonistView(QGraphicsScene* scene);

    void initializeProtagonistView();
    void connectSlots();
    void updateView() override;
    void updateAnimationFrame(QPixmap firstAnimationFrame, QPixmap secondAnimationFrame, QPixmap thirdAnimationFrame);

public slots:
    void updateForIdle();
    void updateForMovingUp();
    void updateForMovingDown();
    void updateForMovingLeft();
    void updateForMovingRight();
    void updateForAttacking();
    void updateForHealthPack();
    void updateForPoisoned();
    void updateForDying();

private:
    QGraphicsScene* scene;
    QPixmap protagonistPixmap;
    QGraphicsPixmapItem* protagonistPixmapItem;
    QTimer* animationTimer;
    int currentFrame;
    QPixmap firstAnimationFrame;
    QPixmap secondAnimationFrame;
    QPixmap thirdAnimationFrame;

    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // GRAPHICALPROTAGONISTVIEW_H
