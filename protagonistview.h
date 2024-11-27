#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include "view.h"

class ProtagonistView : public View
{
public:
    ProtagonistView(QGraphicsScene* scene);
    ~ProtagonistView() = default;

    void renderModel(QGraphicsScene* scene, int xPos, int yPos) override;

private:
    QGraphicsScene* m_scene;
};
#endif // PROTAGONISTVIEW_H
