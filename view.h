#ifndef VIEW_H
#define VIEW_H

#include "rendermethod.h"
#include <memory>
#include <vector>
#include <QGraphicsPixmapItem>
#include <QTextEdit>

class View
{
public:
    View();
    ~View() = default;

    std::vector<std::shared_ptr<RenderMethod>> renderMethods;
    int activeRenderMethod;

    virtual void renderModel(int xPos, int yPos) = 0;
    void addRenderMethod(const std::shared_ptr<RenderMethod> &newRenderMethod);
    int getActiveRenderMethod() const;
    void setActiveRenderMethod(int newActiveRenderMethod);
    void toggleRenderMethod();
};

#endif // VIEW_H
