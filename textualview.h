#ifndef TEXTUALVIEW_H
#define TEXTUALVIEW_H

#include "view.h"
#include <QTextEdit>
#include <QString>

struct TextualRepresentation {
    QString completeWorldRepresentation;
    QString visibleWorldRepresentation;
    int visibleWidth;
    int visibleHeight;
    int firstVisibleRow;
    int firstVisibleCol;
    int offsetLimit;
};

extern TextualRepresentation textualRepresentation;

class TextualView : public View
{

public:
    TextualView(QTextEdit* textView);
    ~TextualView() = default;

    void updateView() = 0;
    void connectSlots();

public slots:
    void moveVisibleViewUp();
    void moveVisibleViewDown();
    void moveVisibleViewLeft();
    void moveVisibleViewRight();

protected:
    QString generateTextRepresentation();
    QString getVisibleTextRepresentation();

    QTextEdit* textView;
    QString characterRepresentation;
};



#endif // TEXTUALVIEW_H
