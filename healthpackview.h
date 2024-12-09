#ifndef HEALTHPACKVIEW_H
#define HEALTHPACKVIEW_H

#include "view.h"
#include "levelmanager.h"
#include "textrender.h"
#include "graphicrender.h"

class HealthPackView : public View, public QObject
{
public:
    HealthPackView(QString healthPackImage);
    ~HealthPackView() = default;

    void connectSlots();

    QGraphicsPixmapItem* pixmap;

public slots:
    void renderModel(int xPos, int yPos) override;
};

#endif // HEALTHPACKVIEW_H
