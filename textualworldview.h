#ifndef TEXTUALWORLDVIEW_H
#define TEXTUALWORLDVIEW_H

#include "worldview.h"
#include <QTextEdit>
#include <QString>

class TextualWorldView : public WorldView
{
public:
    TextualWorldView(QTextEdit* textView);

    void updateView() override;
    QString& getWorldGrid();

    void setWorldGrid(const QString &newWorldGrid);

private:
    QTextEdit* textView;
    QString worldGrid;
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;

    QString generateTextRepresentation();
};

#endif // TEXTUALWORLDVIEW_H
