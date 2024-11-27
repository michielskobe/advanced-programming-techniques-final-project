#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "view.h"

class EnemyView : public View
{
public:
    EnemyView();
    ~EnemyView() = default;

    void renderModel(QGraphicsScene* scene, int xPos, int yPos) override;
};

#endif // ENEMYVIEW_H
