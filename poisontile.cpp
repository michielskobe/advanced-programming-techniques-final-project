#include "poisontile.h"
#include <QDateTime>
#include <QImage>
#include <QRgb>
#include <QTimer>
#include <QtDebug>
#include <ctime>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <QtLogging>
#include <QLoggingCategory>
#include "difficultycontroller.h"

QLoggingCategory poisonTileCat("PoisonTile");

PoisonTile::PoisonTile(int xPosition, int yPosition, float tileWeight) : Tile(xPosition, yPosition, tileWeight)
{
    int t = rand() % DifficultyController::GetInstance()->getPoisonTileLingeringTime(); // should be dependent on game difficulty (hopefully)
    setDamageMultiplier(DifficultyController::GetInstance()->getPoisonTileDamageMul());
    qCInfo(poisonTileCat) <<  "starting timer for " << t << " seconds for PoisonTile x=" << xPos << ", y=" << yPos;
    QTimer::singleShot(t * 1000, this, SLOT(removePoison()));

}

float PoisonTile::getDamageMultiplier() const
{
    return damageMultiplier;
}

void PoisonTile::setDamageMultiplier(float newDamageMultiplier)
{
    damageMultiplier = newDamageMultiplier;
}

void PoisonTile::removePoison()
{
    qCInfo(poisonTileCat) <<  "Removing tile poison for tile x=" << xPos << ", y=" << yPos;
    setDamageMultiplier(0.0f);
}
