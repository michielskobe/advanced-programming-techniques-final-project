#ifndef POISONTILE_H
#define POISONTILE_H
#include "world.h"

class PoisonTile : public QObject, public Tile
{
    Q_OBJECT
public: // constructors / destructors
    PoisonTile(int xPosition, int yPosition, float tileWeight);
    ~PoisonTile() override = default;

public: // attributes
    float damageMultiplier{2.0f};

public: // methods

    float getDamageMultiplier() const;
    void setDamageMultiplier(float newDamageMultiplier);

public slots:
    void removePoison();
};

#endif // POISONTILE_H
