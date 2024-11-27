#include "graphicrender.h"

QLoggingCategory graphicRenderCat("Graphical Renderer");

GraphicRender::GraphicRender(QGraphicsPixmapItem* pixmapItem)
    : m_pixmapItem(pixmapItem) {
    qCInfo(graphicRenderCat) << "Init of graphic renderer";
}

void GraphicRender::render(QGraphicsScene* scene, int xPos, int yPos){
    m_pixmapItem->setPixmap(QPixmap(":/images/protagonist.png"));
    m_pixmapItem->setScale(0.1);
    m_pixmapItem->setPos(xPos, yPos);
    m_pixmapItem->setZValue(1);
    scene->addItem(m_pixmapItem);
}
