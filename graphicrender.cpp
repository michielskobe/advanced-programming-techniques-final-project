#include "graphicrender.h"

QLoggingCategory graphicRenderCat("Graphical Renderer");

GraphicRender::GraphicRender() {
    qCInfo(graphicRenderCat) << "Init of graphic renderer";
}

void GraphicRender::render(){
    qCInfo(graphicRenderCat) << "graphic renderer";
}
