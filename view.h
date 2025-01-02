#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <QString>
#include <QObject>

class Level;
class GameController;

class View : public QObject
{
    Q_OBJECT
public:
    View();
    virtual ~View() = default;

    virtual void updateView() = 0;

protected:
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    GameController* gameController;
};

#endif // VIEW_H
