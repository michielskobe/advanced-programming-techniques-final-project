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
    std::vector<std::pair<int, int>> getPath(std::vector<std::unique_ptr<PathFinderNode>>& tiles, const int startPos, const int destPos, const int width);
    void convNodes(const std::vector<std::unique_ptr<Tile> > &tiles, std::vector<PathFinderNode> &nodes);
    void resetNodes(std::vector<std::unique_ptr<PathFinderNode>> &tiles, std::vector<PathFinderNode> &nodes);

};

#endif // PATHFINDERHELPER_H
