#ifndef GRAPHICALOVERLAYVIEW_H
#define GRAPHICALOVERLAYVIEW_H

#include "graphicalview.h"

class GraphicalOverlayView : public GraphicalView
{
public:
    GraphicalOverlayView(QGraphicsScene* scene);
    ~GraphicalOverlayView() = default;

    void updateView() override;

    void switchOverlayStatus();

    bool getOverlayStatus() const;

protected:
    bool overlayStatus {false};
};

#endif // GRAPHICALOVERLAYVIEW_H
