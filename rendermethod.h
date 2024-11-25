#ifndef RENDERMETHOD_H
#define RENDERMETHOD_H
#include <QGraphicsItem>

class RenderMethod //: public QGraphicsItem
{
public:
    RenderMethod();
    virtual ~RenderMethod() = default;

    virtual void render() = 0;
};

#endif // RENDERMETHOD_H
