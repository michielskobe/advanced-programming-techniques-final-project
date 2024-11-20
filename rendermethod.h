#ifndef RENDERMETHOD_H
#define RENDERMETHOD_H

class RenderMethod
{
public:
    RenderMethod();
    ~RenderMethod() = default;

    virtual void render() = 0;
};

#endif // RENDERMETHOD_H
