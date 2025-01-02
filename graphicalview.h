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
    ~GraphicalView() = default;

    void updateView() = 0;

protected:
    QGraphicsScene* scene;
    QPixmap characterPixmap;
    std::unique_ptr<QGraphicsPixmapItem> characterPixmapItem;
    std::vector<std::unique_ptr<QGraphicsPixmapItem>> characterPixmapItems;
    int positionScalingFactor {50};
};

#endif // GRAPHICALVIEW_H
