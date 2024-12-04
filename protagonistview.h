#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include "view.h"
#include "levelmanager.h"

class ProtagonistView : public View, public QObject
{
public:
    ProtagonistView();
    ~ProtagonistView() = default;

    void connectSlots();

public slots:
    void renderModel(int xPos, int yPos) override;
};
#endif // PROTAGONISTVIEW_H
