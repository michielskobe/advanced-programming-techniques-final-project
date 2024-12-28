#ifndef TEXTUALHEALTHPACKVIEW_H
#define TEXTUALHEALTHPACKVIEW_H

class TextualWorldView;
#include "textualview.h"

class TextualHealthpackView : public TextualView
{
public:
    TextualHealthpackView(QTextEdit* textView);

    void updateView() override;
};

#endif // TEXTUALHEALTHPACKVIEW_H
