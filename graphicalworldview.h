#ifndef GRAPHICALWORLDVIEW_H
#define GRAPHICALWORLDVIEW_H

#include "worldview.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QString>

class GraphicalWorldView : public WorldView
{
public:
    GraphicalWorldView(QGraphicsScene* scene, const QString& imageFile);

    void updateView() override;

private:
    QGraphicsScene* scene;
};

#endif // GRAPHICALWORLDVIEW_H
