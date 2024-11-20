#ifndef VIEW_H
#define VIEW_H

#include "rendermethod.h"

class View
{
public:
    View();
    ~View() = default;

    RenderMethod renderMethod;

    void setRenderMethod(const RenderMethod &newRenderMethod);
};

#endif // VIEW_H
