#ifndef OWNENEMY_H
#define OWNENEMY_H
#include "world.h"
#include <QPixmap>

class OwnEnemy : public Enemy
{
    Q_OBJECT
public:
    OwnEnemy(int xPos, int yPos, int strength);
    OwnEnemy(const Enemy& worldEnemy);
    ~OwnEnemy() override = default;

    virtual float getAttacked(const float damage);
    QPixmap getPixmap();

    QPixmap deadPixmap;
    QPixmap idlePixmap;

};

#endif // OWNENEMY_H
