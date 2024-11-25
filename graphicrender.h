#ifndef GRAPHICRENDER_H
#define GRAPHICRENDER_H
#include <QtLogging>
#include <QLoggingCategory>
#include "rendermethod.h"

class GraphicRender : public QGraphicsPixmapItem, public RenderMethod
{
public:
    GraphicRender();
    ~GraphicRender() = default;

    void render() override;
};

#endif // GRAPHICRENDER_H
