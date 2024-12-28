#ifndef TEXTUALWORLDVIEW_H
#define TEXTUALWORLDVIEW_H

#include "textualview.h"

class TextualWorldView : public TextualView
{
public:
    TextualWorldView(QTextEdit* textView);

    void updateView() override;
};

#endif // TEXTUALWORLDVIEW_H
