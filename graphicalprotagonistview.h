#ifndef GRAPHICALPROTAGONISTVIEW_H
#define GRAPHICALPROTAGONISTVIEW_H

#include "protagonistview.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class GraphicalProtagonistView : public ProtagonistView
{
public:
    GraphicalProtagonistView(QGraphicsScene* scene);

    void updateView() override;

private:
    QGraphicsScene* scene;
    QGraphicsPixmapItem* protagonistPixmapItem;

    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // GRAPHICALPROTAGONISTVIEW_H
