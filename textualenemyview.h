#ifndef TEXTUALENEMYVIEW_H
#define TEXTUALENEMYVIEW_H

class TextualWorldView;
#include "textualview.h"

class TextualEnemyView : public TextualView
{
public:
    TextualEnemyView(QTextEdit* textView, TextualWorldView* worldView);

    void updateView() override;

private:
    TextualWorldView* worldView;
};

#endif // TEXTUALENEMYVIEW_H

