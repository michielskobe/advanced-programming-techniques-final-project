#ifndef TEXTUALWORLDVIEW_H
#define TEXTUALWORLDVIEW_H

#include "worldview.h"
#include <QString>
#include <QTextEdit>

class TextualWorldView : public WorldView
{
public:
    TextualWorldView(QTextEdit* textView);

    void updateView() override;

private:
    QString generateTextRepresentation();

    QTextEdit* textView;
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // TEXTUALWORLDVIEW_H
