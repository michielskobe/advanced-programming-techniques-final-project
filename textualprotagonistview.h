#ifndef TEXTUALPROTAGONISTVIEW_H
#define TEXTUALPROTAGONISTVIEW_H

class TextualWorldView;
#include "protagonistview.h"
#include <QTextEdit>
#include <QString>
#include <QColor>

class TextualProtagonistView : public ProtagonistView
{
    Q_OBJECT
public:
    TextualProtagonistView(QTextEdit* textView, TextualWorldView* worldView);

    void updateView() override;
    void connectSlots() override;
    void changeProtagonistColor(const QColor& color);

public slots:
    void updateForState(const QString& state);

private:
    QTextEdit* textView;
    TextualWorldView* worldView;
    QString protagonistView {" ☺ "};
    QColor currentColor {QColor("black")};
    bool isDead {false};
};

#endif // TEXTUALPROTAGONISTVIEW_H
