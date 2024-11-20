#ifndef GRAPHICRENDER_H
#define GRAPHICRENDER_H

#include "rendermethod.h"

class GraphicRender : public RenderMethod
{
public:
    GraphicRender();
    ~GraphicRender() = default;

    void render() override;
};

#endif // GRAPHICRENDER_H
