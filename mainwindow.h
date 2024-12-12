#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "world.h"
#include "gamecontroller.h"
#include <QTextEdit>
#include <QCompleter>
#include "worldview.h"
#include "graphicalworldview.h"
#include "textualworldview.h"

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
    QGraphicsScene *grahpicsScene;
    QTextEdit *textScene;
    QCompleter* completer;
    World world;
    WorldView* currentWorldView;
    GraphicalWorldView* graphicalWorldView;
    TextualWorldView* textualWorldView;
    int tileSize = 3;
    GameController gameController = GameController();
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;

    void setupWorldGrid();
    void setupProtagonist();
    void setupEnemiesAndHealthPacks();
    void keyPressEvent(QKeyEvent *event) override;
    QString generateTextRepresentation();

public slots:
    void zoomIn();
    void zoomOut();
    void updateMainUI();
    void processCommand();
    void onTabChanged(int index);
};
#endif // MAINWINDOW_H
