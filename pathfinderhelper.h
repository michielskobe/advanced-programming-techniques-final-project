#ifndef PATHFINDERHELPER_H
#define PATHFINDERHELPER_H
#include <vector>
#include <memory>
#include "pathfinder_class.h"
#include "world.h"
#include "pathfindernode.h"

class PathFinderHelper
{
public:// constructor/destructor
    PathFinderHelper();

public:// attributes
    PathFinder<PathFinderNode, PathFinderNode>* a_star;

public:// methods
    std::vector<int> getPath(const std::vector<std::unique_ptr<Tile>>& tiles, const int startPos, const int destPos);
    void convNodes(const std::vector<std::unique_ptr<Tile> > &tiles, std::vector<PathFinderNode> &nodes);

};

#endif // PATHFINDERHELPER_H
