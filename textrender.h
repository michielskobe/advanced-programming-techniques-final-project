#ifndef TEXTRENDER_H
#define TEXTRENDER_H

#include "rendermethod.h"

class TextRender : public RenderMethod
{
public:
    TextRender();
    ~TextRender() = default;

    void render() override;
};

#endif // TEXTRENDER_H
