#include "customqgraphicsview.h"

CustomQGraphicsView::CustomQGraphicsView() {}

void CustomQGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    auto pic = QPixmap(":/images/test2.jpg");
    auto rectf = QRectF(pic.rect());
    painter->drawPixmap(rect, pic, rect);
}
