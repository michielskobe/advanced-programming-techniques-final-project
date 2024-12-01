#include "graphicrender.h"

QLoggingCategory graphicRenderCat("Graphical Renderer");

GraphicRender::GraphicRender(QGraphicsPixmapItem* pixmapItem)
    : m_pixmapItem(pixmapItem) {
    m_pixmapItem->setScale(0.1);
    m_pixmapItem->setPos(0, 0);
    m_pixmapItem->setZValue(1);
    qCInfo(graphicRenderCat) << "Init of graphic renderer";
}

void GraphicRender::render(int xPos, int yPos){
    m_pixmapItem->setPos(xPos, yPos);
}

QGraphicsPixmapItem *GraphicRender::pixmapItem() const
{
    return m_pixmapItem;
}
