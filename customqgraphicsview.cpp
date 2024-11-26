#include "customqgraphicsview.h"

CustomQGraphicsView::CustomQGraphicsView() {}

void CustomQGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    auto pic = QPixmap(":/images/world_images/maze2.png");
    auto rectf = QRectF(pic.rect());
    painter->drawPixmap(rect, pic, rectf);
}
