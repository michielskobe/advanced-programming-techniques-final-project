#ifndef GRAPHICALPROTAGONISTVIEW_H
#define GRAPHICALPROTAGONISTVIEW_H

#include "graphicalview.h"
#include <QTimer>

class GraphicalProtagonistView : public GraphicalView
{
    Q_OBJECT
public:
    GraphicalProtagonistView(QGraphicsScene* scene);
    ~GraphicalProtagonistView() = default;

    void updateView() override;
    void connectSlots();
    void updateAnimationFrame(const std::vector<QPixmap>& animationFrames);

public slots:
    void updateForState(const QString& state);

protected:
    std::unique_ptr<QTimer> animationTimer;
    int currentFrame {0};
    std::vector<QPixmap> animationFrames;
};

#endif // GRAPHICALPROTAGONISTVIEW_H
