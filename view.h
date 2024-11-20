#ifndef VIEW_H
#define VIEW_H

#include "rendermethod.h"
#include <memory>
#include <vector>

class View
{
public:
    View();
    ~View() = default;

    std::vector<std::shared_ptr<RenderMethod>> renderMethods;
    int activeRenderMethod;

    void setRenderMethods(const std::vector<std::shared_ptr<RenderMethod>> &newRenderMethods);
    int getActiveRenderMethod() const;
    void setActiveRenderMethod(int newActiveRenderMethod);

};

#endif // VIEW_H
