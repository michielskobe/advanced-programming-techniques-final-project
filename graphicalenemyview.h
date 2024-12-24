#ifndef GRAPHICALENEMYVIEW_H
#define GRAPHICALENEMYVIEW_H

#include "graphicalview.h"

class GraphicalEnemyView : public GraphicalView
{
    Q_OBJECT
public:
    GraphicalEnemyView(QGraphicsScene* scene);
    ~GraphicalEnemyView() = default;

    void updateView() override;
};

#endif // GRAPHICALENEMYVIEW_H
