#ifndef CUSTOMQGRAPHICSVIEW_H
#define CUSTOMQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QPainter>
#include <QRectF>
#include <QPixmap>

class CustomQGraphicsView : public QGraphicsView
{
    //Use everything which is is QGraphicsView
    using QGraphicsView::QGraphicsView;

public: // constructors/destructors
    CustomQGraphicsView();
    ~CustomQGraphicsView() = default;

public: // methods
    void drawBackground(QPainter *painter, const QRectF &rect);

};

#endif // CUSTOMQGRAPHICSVIEW_H
