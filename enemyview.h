#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "view.h"
#include "levelmanager.h"
#include "textrender.h"
#include "graphicrender.h"

class EnemyView : public View, public QObject
{
public:
    EnemyView();
    ~EnemyView() = default;

    void connectSlots();

public slots:
    void renderModel(int xPos, int yPos) override;
};

#endif // ENEMYVIEW_H
