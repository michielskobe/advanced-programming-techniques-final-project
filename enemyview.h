#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "view.h"

class EnemyView : public View
{
public:
    EnemyView();
    ~EnemyView() = default;

    virtual void updateView() = 0;
};

#endif // ENEMYVIEW_H
