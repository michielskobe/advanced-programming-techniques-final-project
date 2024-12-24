#ifndef TEXTUALVIEW_H
#define TEXTUALVIEW_H

#include "view.h"
#include <QTextEdit>
#include <QString>

class TextualView : public View
{
public:
    TextualView(QTextEdit* textView);
    virtual ~TextualView() = default;

    virtual void updateView() = 0;

protected:
    QTextEdit* textView;
    QString characterRepresentation;

};

#endif // TEXTUALVIEW_H
