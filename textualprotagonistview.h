#ifndef TEXTUALPROTAGONISTVIEW_H
#define TEXTUALPROTAGONISTVIEW_H

#include "protagonistview.h"
#include <QTextEdit>
#include <QString>
#include "textualworldview.h"
#include <QTimer>

class TextualProtagonistView : public QObject, public ProtagonistView
{
    Q_OBJECT
public:
    TextualProtagonistView(QTextEdit* textView, TextualWorldView* worldView);

    void updateView() override;
    void connectSlots();
    void changeProtagonistColor(const QColor& color);

public slots:
    void updateForIdle();
    void updateForMoving();
    void updateForAttacking();
    void updateForHealthPack();
    void updateForPoisoned();
    void updateForDying();

private:
    QTextEdit* textView;
    TextualWorldView* worldView;
    QString protagonistView;
    QColor currentColor;
    bool isDead = false;

    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // TEXTUALPROTAGONISTVIEW_H
