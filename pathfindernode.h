#ifndef PATHFINDERNODE_H
#define PATHFINDERNODE_H
#include <vector>
#include <memory>
#include "world.h"

class PathFinderNode: public Tile
{
    // Q_OBJECT
public: // constructor / destructor
    PathFinderNode(int xPosition, int yPosition, float tileWeight);
    PathFinderNode(const Tile& worldTile);
    ~PathFinderNode() override = default;

public: // attributes
    float f; // final cost
    float g; // given cost
    float h; // heuristic cost
    bool visited;
    bool closed;
    PathFinderNode* prev = nullptr;

    float damageMultiplier{0.0f};
    bool playerVisited;
    bool autoPlayHighlight{false};

    void setPoison();

    float getDamageMultiplier() const;
    void setDamageMultiplier(float newDamageMultiplier);

    void resetPathFinderAttr();

// public slots:
//     void removePoison();
    bool getPlayerVisited() const;
    void setPlayerVisited(bool newPlayerVisited);
    bool getAutoPlayHighlight() const;
    void setAutoPlayHighlight(bool newAutoPlayHighlight);
    void resetAutoPlayHighlight();
};

#endif // PATHFINDERNODE_H
