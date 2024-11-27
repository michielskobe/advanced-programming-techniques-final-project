#ifndef TEXTRENDER_H
#define TEXTRENDER_H

#include "rendermethod.h"
#include <QTextEdit>

class TextRender : public RenderMethod
{
public:
    TextRender(QTextEdit* textEdit);
    ~TextRender() = default;

    void render(QGraphicsScene* scene, int xPos, int yPos) override;

private:
    QTextEdit* m_textEdit;
};

#endif // TEXTRENDER_H
