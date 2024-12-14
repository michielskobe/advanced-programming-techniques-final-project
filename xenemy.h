#ifndef XENEMY_H
#define XENEMY_H
#include "world.h"

class XEnemy : public Enemy
{
    Q_OBJECT
public:// constructors / destructors
    XEnemy(int xPosition, int yPosition, float strength);
    ~XEnemy() override = default;

public:// attributes
    float health;
    bool updatePositionAllowed{false};

public:// methods
    float getHealth() const;
    void setHealth(float newHealth);
    bool getUpdatePositionAllowed() const;
    void setUpdatePositionAllowed(bool newUpdatePositionAllowed);

public slots:
    void updateXEnemyPosition();

signals:
    void positionXEnemyUpdated();
};

#endif // XENEMY_H
