#ifndef HEALTHPACKVIEW_H
#define HEALTHPACKVIEW_H

#include "view.h"

class HealthpackView : public View
{
public:
    HealthpackView();

    virtual void updateView() = 0;
};

#endif // HEALTHPACKVIEW_H
