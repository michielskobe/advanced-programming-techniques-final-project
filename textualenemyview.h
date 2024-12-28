#ifndef TEXTUALENEMYVIEW_H
#define TEXTUALENEMYVIEW_H

class TextualWorldView;
#include "textualview.h"

class TextualEnemyView : public TextualView
{
public:
    TextualEnemyView(QTextEdit* textView);

    void updateView() override;
};

#endif // TEXTUALENEMYVIEW_H

