#ifndef OWNPENEMY_H
#define OWNPENEMY_H

#include "ownenemy.h"
#include "world.h"

class OwnPEnemy : public OwnEnemy
{
    Q_OBJECT
public:
    OwnPEnemy(const PEnemy& worldPEnemy);
    ~OwnPEnemy() override = default;
    float poisonLevel;


    float getAttacked(const float damage) override;
    float getPoisonLevel() const;
    void setPoisonLevel(float newPoisonLevel);

public slots:
    bool poison();

signals:
    void poisonLevelUpdated(int value);
};

#endif // OWNPENEMY_H
