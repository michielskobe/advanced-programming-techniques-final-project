#ifndef CUSTOMQGRAPHICSVIEW_H
#define CUSTOMQGRAPHICSVIEW_H

#include <QGraphicsView>

class CustomQGraphicsView : public QGraphicsView
{
    //Use everything which is is QGraphicsView
    using QGraphicsView::QGraphicsView;
public:
    CustomQGraphicsView();
    ~CustomQGraphicsView() = default;
};

#endif // CUSTOMQGRAPHICSVIEW_H
