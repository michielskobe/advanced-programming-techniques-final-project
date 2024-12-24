#ifndef GRAPHICALWORLDVIEW_H
#define GRAPHICALWORLDVIEW_H

#include "graphicalview.h"

class GraphicalWorldView : public GraphicalView
{
public:
    GraphicalWorldView(QGraphicsScene* scene);
    ~GraphicalWorldView() = default;

    void updateView() override;
};

#endif // GRAPHICALWORLDVIEW_H
