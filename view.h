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

    virtual void renderModel(QGraphicsScene* scene, int xPos, int yPos) = 0;
    void setRenderMethods(const std::vector<std::shared_ptr<RenderMethod>> &newRenderMethods);
    int getActiveRenderMethod() const;
    void setActiveRenderMethod(int newActiveRenderMethod);
};

#endif // VIEW_H
