#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include "view.h"

class ProtagonistView : public View
{
public:
    ProtagonistView();
    virtual ~ProtagonistView() = default;

    virtual void updateView() = 0;
};

#endif // PROTAGONISTVIEW_H
