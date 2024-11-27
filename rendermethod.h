#ifndef RENDERMETHOD_H
#define RENDERMETHOD_H
#include <QGraphicsItem>

class RenderMethod //: public QGraphicsItem
{
public:
    RenderMethod();
    virtual ~RenderMethod() = default;

    virtual void render(int xPos, int yPos) = 0;
};

#endif // RENDERMETHOD_H
