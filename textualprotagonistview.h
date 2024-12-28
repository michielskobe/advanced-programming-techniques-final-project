#ifndef TEXTUALPROTAGONISTVIEW_H
#define TEXTUALPROTAGONISTVIEW_H

class TextualWorldView;
#include "textualview.h"
#include <QColor>

class TextualProtagonistView : public TextualView
{
    Q_OBJECT
public:
    TextualProtagonistView(QTextEdit* textView);

    void updateView() override;
    void connectSlots();
    void changeProtagonistColor(const QColor& color);

public slots:
    void updateForState(const QString& state);

private:
    QColor currentColor {QColor("black")};
    bool isDead {false};
};

#endif // TEXTUALPROTAGONISTVIEW_H
