#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include "view.h"
#include "levelmanager.h"
#include "textrender.h"
#include "graphicrender.h"
#include <QGraphicsPixmapItem>

class ProtagonistView : public View, public QObject
{
public:
    ProtagonistView(QString protagonistImage);
    ~ProtagonistView() = default;

    void connectSlots();

    QGraphicsPixmapItem* pixmap;

public slots:
    void renderModel(int xPos, int yPos) override;
};
#endif // PROTAGONISTVIEW_H
