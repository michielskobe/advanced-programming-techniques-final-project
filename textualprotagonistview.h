#ifndef TEXTUALPROTAGONISTVIEW_H
#define TEXTUALPROTAGONISTVIEW_H

#include "protagonistview.h"
#include <QTextEdit>
#include <QString>

class TextualProtagonistView : public ProtagonistView
{
public:
    TextualProtagonistView(QTextEdit* textView, QString& grid);

    void updateView() override;

private:
    QTextEdit* textView;
    QString& grid;
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // TEXTUALPROTAGONISTVIEW_H
