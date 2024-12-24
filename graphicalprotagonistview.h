#ifndef GRAPHICALPROTAGONISTVIEW_H
#define GRAPHICALPROTAGONISTVIEW_H

#include "protagonistview.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTimer>

class GraphicalProtagonistView : public ProtagonistView
{
    Q_OBJECT
public:
    GraphicalProtagonistView(QGraphicsScene* scene);

    void updateView() override;
    void connectSlots() override;
    void updateAnimationFrame(const std::vector<QPixmap>& animationFrames);

public slots:
    void updateForState(const QString& state);

private:
    QGraphicsScene* scene;
    QPixmap protagonistPixmap;
    QGraphicsPixmapItem* protagonistPixmapItem;
    QTimer* animationTimer;
    int currentFrame;
    std::vector<QPixmap> animationFrames;
};

#endif // GRAPHICALPROTAGONISTVIEW_H
