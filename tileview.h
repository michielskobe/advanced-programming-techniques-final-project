#ifndef TILEVIEW_H
#define TILEVIEW_H

#include "view.h"

class TileView : public View
{
public:
    TileView();
    ~TileView() = default;

    void renderModel() override;
};

#endif // TILEVIEW_H
