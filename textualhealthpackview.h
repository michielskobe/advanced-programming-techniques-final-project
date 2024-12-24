#ifndef TEXTUALHEALTHPACKVIEW_H
#define TEXTUALHEALTHPACKVIEW_H

class TextualWorldView;
#include "textualview.h"

class TextualHealthpackView : public TextualView
{
public:
    TextualHealthpackView(QTextEdit* textView, TextualWorldView* worldView);

    void updateView() override;

private:
    TextualWorldView *worldView;
};

#endif // TEXTUALHEALTHPACKVIEW_H
