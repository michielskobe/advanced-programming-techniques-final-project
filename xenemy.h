#ifndef XENEMY_H
#define XENEMY_H
#include "world.h"
#include "ownenemy.h"

class XEnemy : public OwnEnemy
{
    Q_OBJECT
public:// constructors / destructors
    XEnemy(int xPosition, int yPosition, float strength);
    XEnemy(const Enemy& enemy);
    ~XEnemy() override = default;

public:// attributes
    float health;
    bool updatePositionAllowed{false};

public:// methods
    float getHealth() const;
    void setHealth(float newHealth);
    bool getUpdatePositionAllowed() const;
    void setUpdatePositionAllowed(bool newUpdatePositionAllowed);
    void updatePosition(std::pair<int, int> move);
    int protagonistDistance() const;
    float getAttacked(const float damage) override;

public slots:
    void updateXEnemyPosition();

signals:
    void positionXEnemyUpdated();
};

#endif // XENEMY_H
