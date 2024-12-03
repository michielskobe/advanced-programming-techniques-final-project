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
};

#endif // PATHFINDERHELPER_H
