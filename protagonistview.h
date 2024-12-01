#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include "view.h"

class ProtagonistView : public View
{
public:
    ProtagonistView();
    ~ProtagonistView() = default;

public slots:
    void renderModel(int xPos, int yPos) override;
};
#endif // PROTAGONISTVIEW_H
