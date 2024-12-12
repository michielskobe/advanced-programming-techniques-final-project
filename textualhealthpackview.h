#ifndef TEXTUALHEALTHPACKVIEW_H
#define TEXTUALHEALTHPACKVIEW_H

#include "healthpackview.h"
#include <QTextEdit>
#include <QString>
#include "textualworldview.h"

class TextualHealthpackView : public HealthpackView
{
public:
    TextualHealthpackView(QTextEdit* textView, TextualWorldView* worldView);

    void updateView() override;

private:
    QTextEdit* textView;
    TextualWorldView* worldView;
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // TEXTUALHEALTHPACKVIEW_H
