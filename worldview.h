#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include "view.h"

class WorldView : public View
{
public:
    WorldView();
    virtual ~WorldView() = default;

    virtual void updateView() = 0;
};

#endif // WORLDVIEW_H
