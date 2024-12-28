#ifndef TEXTUALVIEW_H
#define TEXTUALVIEW_H

#include "view.h"
#include <QTextEdit>
#include <QString>

extern QString completeWorldRepresentation;

class TextualView : public View
{

public:
    TextualView(QTextEdit* textView);
    virtual ~TextualView() = default;

    virtual void updateView() = 0;

protected:
    QString generateTextRepresentation();

    QTextEdit* textView;
    QString characterRepresentation;
};



#endif // TEXTUALVIEW_H
