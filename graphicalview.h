#ifndef GRAPHICALVIEW_H
#define GRAPHICALVIEW_H

#include "view.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QTimer>

class GraphicalView : public View
{
public:
    GraphicalView(QGraphicsScene* scene);
    virtual ~GraphicalView() = default;

    virtual void updateView() = 0;

protected:
    QGraphicsScene* scene;
    QPixmap characterPixmap;
    QGraphicsPixmapItem* characterPixmapItem;
    std::vector<QGraphicsPixmapItem*> characterPixmapItems;
    int positionScalingFactor {50};
};

#endif // GRAPHICALVIEW_H
