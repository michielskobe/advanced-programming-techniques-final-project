#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "view.h"

class EnemyView : public View
{
public:
    EnemyView();
    ~EnemyView() = default;

    void renderModel(int xPos, int yPos) override;
};

#endif // ENEMYVIEW_H
