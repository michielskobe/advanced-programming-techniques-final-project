#ifndef GRAPHICRENDER_H
#define GRAPHICRENDER_H
#include <QtLogging>
#include <QLoggingCategory>
#include "rendermethod.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class GraphicRender : public QGraphicsPixmapItem, public RenderMethod
{
public:
    GraphicRender(QGraphicsPixmapItem* pixmapItem);
    ~GraphicRender() = default;

    void render(int xPos, int yPos) override;

    QGraphicsPixmapItem *pixmapItem() const;

private:
    QGraphicsPixmapItem* m_pixmapItem;
};

#endif // GRAPHICRENDER_H
