#include "pathfinderhelper.h"

PathFinderHelper::PathFinderHelper() {}

std::vector<int> PathFinderHelper::getPath(const std::vector<std::unique_ptr<Tile> > &tiles, const int startPos, const int destPos, const int width)
{
    std::vector<PathFinderNode> nodes;
    convNodes(tiles, nodes);
    Comparator<PathFinderNode> nodeComparator = [](const PathFinderNode& a, const PathFinderNode& b) {
        return a.getValue() < b.getValue();
    };

    helper_func<PathFinderNode> costFunction = [](const PathFinderNode& p1, const PathFinderNode& p2) {
        return std::abs(p1.getXPos() - p2.getXPos()) + std::abs(p1.getYPos() - p2.getYPos());
    };

    helper_func<PathFinderNode> distFunction = [](const PathFinderNode& p1, const PathFinderNode& p2) {
        return std::abs(p1.getXPos() - p2.getXPos()) + std::abs(p1.getYPos() - p2.getYPos());
    };

    float heuristicWeight = 1.0f;

    a_star = new PathFinder(nodes, &nodes[startPos], &nodes[destPos], nodeComparator, width, costFunction, distFunction, heuristicWeight);
    auto res = a_star->A_star();
    return res;
}

void PathFinderHelper::convNodes(const std::vector<std::unique_ptr<Tile> > &tiles, std::vector<PathFinderNode> &nodes)
{
    nodes.reserve(tiles.size());

    for (int i = 0; i < (int)(tiles).size(); i++) {
        auto tile = (&(*(tiles[i])));
        const int xPos = tile->getXPos();
        const int yPos = tile->getYPos();
        const float tileValue = tile->getValue();
        nodes.push_back(PathFinderNode(xPos, yPos, tileValue));
    }
}
