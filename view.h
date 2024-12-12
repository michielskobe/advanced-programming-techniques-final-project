#ifndef VIEW_H
#define VIEW_H

#include "levelmanager.h"
#include "gamecontroller.h"

class View
{
public:
    View();
    ~View() = default;

    virtual void updateView() = 0;
};

#endif // VIEW_H
