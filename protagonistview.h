#ifndef PROTAGONISTVIEW_H
#define PROTAGONISTVIEW_H

#include "view.h"
#include <QObject>
#include <memory>
#include <vector>
#include <functional>
#include <map>

class Level;
class GameController;

class ProtagonistView : public QObject, public View
{
    Q_OBJECT
public:
    ProtagonistView();
    virtual ~ProtagonistView() = default;

    virtual void updateView() = 0;
    virtual void connectSlots() = 0;

protected:
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // PROTAGONISTVIEW_H
