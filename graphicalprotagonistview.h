#ifndef GRAPHICALPROTAGONISTVIEW_H
#define GRAPHICALPROTAGONISTVIEW_H

#include "protagonistview.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class GraphicalProtagonistView : public QObject, public ProtagonistView
{
    Q_OBJECT
public:
    GraphicalProtagonistView(QGraphicsScene* scene);

    void initializeProtagonistView();
    void connectSlots();
    void updateView() override;

public slots:
    void updateForIdle();
    void updateForMoving();
    void updateForAttacking();
    void updateForHealthPack();
    void updateForPoisoned();
    void updateForDying();

private:
    QGraphicsScene* scene;
    QPixmap protagonistPixmap;
    QGraphicsPixmapItem* protagonistPixmapItem;

    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // GRAPHICALPROTAGONISTVIEW_H
