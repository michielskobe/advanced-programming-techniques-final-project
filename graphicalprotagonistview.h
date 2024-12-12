#ifndef GRAPHICALPROTAGONISTVIEW_H
#define GRAPHICALPROTAGONISTVIEW_H

#include "protagonistview.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class GraphicalProtagonistView : public ProtagonistView
{
public:
    GraphicalProtagonistView(QGraphicsScene* scene);

    void updateView() override;

private:
    QGraphicsScene* scene;
    QGraphicsPixmapItem* protagonistPixmapItem;
};

#endif // GRAPHICALPROTAGONISTVIEW_H
