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

void View::addRenderMethod(const std::shared_ptr<RenderMethod> &newRenderMethods)
{
    renderMethods.emplace_back(newRenderMethods);
}

void View::toggleRenderMethod() {
    activeRenderMethod = (activeRenderMethod == 0) ? 1 : 0;
    //renderMethods[activeRenderMethod]->render(currentXPos, currentYPos);
}
