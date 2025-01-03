#include "pathfinderhelper.h"
#include <chrono>
using namespace std::chrono;

QLoggingCategory pathFinderHelperCat("PathFinderHelper");

PathFinderHelper::PathFinderHelper() {}

std::vector<std::pair<int, int>> PathFinderHelper::getPath(std::vector<std::unique_ptr<PathFinderNode> > &tiles, const int startPos, const int destPos, const int width)
{
    std::vector<PathFinderNode> nodes;
    auto start = high_resolution_clock::now();
    resetNodes(tiles, nodes);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    qCInfo(pathFinderHelperCat) << "It took this many microseconds to reset the nodes: " << duration.count();

    Comparator<PathFinderNode> nodeComparator = [](const PathFinderNode& a, const PathFinderNode& b) {
        return a.getValue() < b.getValue();
    };

    helper_func<PathFinderNode> costFunction = [](const PathFinderNode& p1, const PathFinderNode& p2) {
        return p2.getValue() + 2.0f;
    };

    helper_func<PathFinderNode> distFunction = [](const PathFinderNode& p1, const PathFinderNode& p2) {
        return std::abs(p1.getXPos() - p2.getXPos()) + std::abs(p1.getYPos() - p2.getYPos());
    };

    float heuristicWeight = 100.0f;
    start = high_resolution_clock::now();
    a_star = new PathFinder(nodes, &nodes[startPos], &nodes[destPos], nodeComparator, width, costFunction, distFunction, heuristicWeight);
    auto res = a_star->A_star();
    delete a_star;
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    qCInfo(pathFinderHelperCat) << "It took this many microseconds to find a path: " << duration.count();

    std::array<std::pair<int, int>, 8> directions = {
        std::make_pair(0, -1),
        std::make_pair(1, -1),
        std::make_pair(1, 0),
        std::make_pair(1, 1),
        std::make_pair(0, 1),
        std::make_pair(-1, 1),
        std::make_pair(-1, 0),
        std::make_pair(-1, -1)
    };

    std::vector<std::pair<int, int>> res_pair;
    foreach (auto& step, res) {
        res_pair.push_back(directions[step]);
    }

    return res_pair;
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

void PathFinderHelper::resetNodes(std::vector<std::unique_ptr<PathFinderNode>> &tiles, std::vector<PathFinderNode> &nodes)
{
    for (int i = 0; i < (int)(tiles).size(); i++) {
        tiles[i]->resetPathFinderAttr();
        nodes.push_back(PathFinderNode(*tiles[i]));
    }

}
