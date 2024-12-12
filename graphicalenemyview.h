#ifndef GRAPHICALENEMYVIEW_H
#define GRAPHICALENEMYVIEW_H

#include "enemyview.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVector>

class GraphicalEnemyView : public EnemyView
{
public:
    GraphicalEnemyView(QGraphicsScene* scene);
    ~GraphicalEnemyView() = default;

    void updateView() override;

private:
    QGraphicsScene* scene;
    QVector<QGraphicsPixmapItem*> enemyPixmapItems;

    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // GRAPHICALENEMYVIEW_H
