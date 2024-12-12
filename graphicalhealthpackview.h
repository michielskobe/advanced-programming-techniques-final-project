#ifndef GRAPHICALHEALTHPACKVIEW_H
#define GRAPHICALHEALTHPACKVIEW_H

#include "healthpackview.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVector>

class GraphicalHealthpackView : public HealthpackView
{
public:
    GraphicalHealthpackView(QGraphicsScene* scene);
    ~GraphicalHealthpackView() = default;

    void updateView() override;

private:
    QGraphicsScene* scene;
    QVector<QGraphicsPixmapItem*> healthpackPixmapItems;

    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // GRAPHICALHEALTHPACKVIEW_H
