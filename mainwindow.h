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
#include "graphicalprotagonistview.h"
#include "textualprotagonistview.h"
#include "graphicalenemyview.h"
#include "textualenemyview.h"
#include "graphicalhealthpackview.h"
#include "textualhealthpackview.h"


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
    GraphicalProtagonistView* graphicalProtagonistView;
    TextualProtagonistView* textualProtagonistView;
    GraphicalEnemyView* graphicalEnemyView;
    TextualEnemyView* textualEnemyView;
    GraphicalHealthpackView* graphicalHealthpackView;
    TextualHealthpackView* textualHealthpackView;
    GameController* gameController;
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;

    void setupWorldGrid();
    void setupProtagonist();
    void setupEnemiesAndHealthPacks();
    void keyPressEvent(QKeyEvent *event) override;
    QString generateTextRepresentation();
    void setStatBars(float health, float energy);
    void protagonistStatus(float health, float energy);

public slots:
    void zoomIn();
    void zoomOut();
    void updateMainUI();
    void processCommand();
    void onTabChanged(int index);
private slots:
    void on_activeLevelBox_valueChanged(int arg1);
    void on_difficultyBox_valueChanged(int arg1);
};
#endif // MAINWINDOW_H
