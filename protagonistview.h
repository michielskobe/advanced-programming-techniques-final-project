#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include "view.h"

class ProtagonistView : public View
{
public:
    ProtagonistView();
    ~ProtagonistView() = default;

    void renderModel() override;
};

#endif // PROTAGONISTVIEW_H
