#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "world.h"
#include "gamecontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    World world;
    int tileSize = 3;
    GameController gameController = GameController();

    void setupWorldGrid();
    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void zoomIn();
    void zoomOut();
};
#endif // MAINWINDOW_H
