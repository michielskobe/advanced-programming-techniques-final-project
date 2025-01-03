#include "pathfindernode.h"
#include "difficultycontroller.h"

QLoggingCategory PathFinderNodeCat("PathFinderNode");


PathFinderNode::PathFinderNode(int xPosition, int yPosition, float tileWeight): Tile(xPosition, yPosition, tileWeight)
{

}

PathFinderNode::PathFinderNode(const Tile &worldTile): Tile(worldTile.getXPos(), worldTile.getYPos(), worldTile.getValue())
{

}

bool PathFinderNode::getAutoPlayHighlight() const
{
    return autoPlayHighlight;
}

void PathFinderNode::setAutoPlayHighlight(bool newAutoPlayHighlight)
{
    autoPlayHighlight = newAutoPlayHighlight;
}

void PathFinderNode::resetAutoPlayHighlight()
{
    autoPlayHighlight = false;
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
    setDamageMultiplier(DifficultyController::GetInstance()->getPoisonTileDamageMul());
}
