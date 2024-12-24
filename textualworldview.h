#ifndef TEXTUALWORLDVIEW_H
#define TEXTUALWORLDVIEW_H

#include "textualview.h"

class TextualWorldView : public TextualView
{
public:
    TextualWorldView(QTextEdit* textView);

    void updateView() override;
    QString& getWorldGrid();

    void setWorldGrid(const QString &newWorldGrid);

private:
    QString generateTextRepresentation();

    QString worldGrid;
};

#endif // TEXTUALWORLDVIEW_H
