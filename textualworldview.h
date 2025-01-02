#ifndef TEXTUALWORLDVIEW_H
#define TEXTUALWORLDVIEW_H

#include "textualview.h"

class TextualWorldView : public TextualView
{
public:
    TextualWorldView(QTextEdit* textView);
    ~TextualWorldView() = default;

    void updateView() override;

private:
    int activeLevel {0};
};

#endif // TEXTUALWORLDVIEW_H
