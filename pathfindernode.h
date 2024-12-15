#ifndef PATHFINDERNODE_H
#define PATHFINDERNODE_H
#include <vector>
#include <memory>
#include "world.h"

class PathFinderNode : public Tile
{
public: // constructor / destructor
    PathFinderNode(int xPosition, int yPosition, float tileWeight);
    ~PathFinderNode() override = default;

public: // attributes
    float f; // final cost
    float g; // given cost
    float h; // heuristic cost
    bool visited;
    bool closed;
    PathFinderNode* prev = nullptr;

};

#endif // PATHFINDERNODE_H
