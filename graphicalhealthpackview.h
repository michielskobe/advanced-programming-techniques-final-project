#ifndef GRAPHICALHEALTHPACKVIEW_H
#define GRAPHICALHEALTHPACKVIEW_H

#include "graphicalview.h"

class GraphicalHealthpackView : public GraphicalView
{
public:
    GraphicalHealthpackView(QGraphicsScene* scene);
    ~GraphicalHealthpackView() = default;

    void updateView() override;
};

#endif // GRAPHICALHEALTHPACKVIEW_H
