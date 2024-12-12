#ifndef TEXTUALENEMYVIEW_H
#define TEXTUALENEMYVIEW_H

#include "enemyview.h"
#include <QTextEdit>
#include <QString>
#include "textualworldview.h"

class TextualEnemyView : public EnemyView
{
public:
    TextualEnemyView(QTextEdit* textView, TextualWorldView* worldView);

    void updateView() override;

private:
    QTextEdit* textView;
    TextualWorldView* worldView;
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // TEXTUALENEMYVIEW_H
