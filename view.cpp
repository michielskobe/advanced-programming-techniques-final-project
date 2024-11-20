#include "view.h"

View::View() {}

void View::setActiveRenderMethod(int newActiveRenderMethod)
{
    activeRenderMethod = newActiveRenderMethod;
}

int View::getActiveRenderMethod() const
{
    return activeRenderMethod;
}

void View::setRenderMethods(const std::vector<std::shared_ptr<RenderMethod> > &newRenderMethods)
{
    renderMethods = newRenderMethods;
}

