#include "pathfindernode.h"
#include "difficultycontroller.h"
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

QLoggingCategory PathFinderNodeCat("PathFinderNode");


PathFinderNode::PathFinderNode(int xPosition, int yPosition, float tileWeight): Tile(xPosition, yPosition, tileWeight)
{

}

PathFinderNode::PathFinderNode(const Tile &worldTile): Tile(worldTile.getXPos(), worldTile.getYPos(), worldTile.getValue())
{

}

bool PathFinderNode::getPlayerVisited() const
{
    return playerVisited;
}

void PathFinderNode::setPlayerVisited(bool newPlayerVisited)
{
    playerVisited = newPlayerVisited;
}

float PathFinderNode::getDamageMultiplier() const
{
    return damageMultiplier;
}

void PathFinderNode::setDamageMultiplier(float newDamageMultiplier)
{
    damageMultiplier = newDamageMultiplier;
}

void PathFinderNode::resetPathFinderAttr()
{
    visited = false;
    closed = false;
}

void PathFinderNode::setPoison()
{
    // int t = rand() % DifficultyController::GetInstance()->getPoisonTileLingeringTime();
    setDamageMultiplier(DifficultyController::GetInstance()->getPoisonTileDamageMul());
    // qCInfo(PathFinderNodeCat) <<  "starting timer for " << t << " seconds for PoisonTile x=" << xPos << ", y=" << yPos;
    // QTimer::singleShot(t * 1000, this, SLOT(removePoison()));

}

// void PathFinderNode::removePoison()
// {
//     qCInfo(PathFinderNodeCat) <<  "Removing tile poison for tile x=" << xPos << ", y=" << yPos;
//     setDamageMultiplier(0.0f);
// }
