#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QCompleter>
#include "world.h"
#include "gamecontroller.h"
#include "graphicalworldview.h"
#include "textualworldview.h"
#include "graphicalprotagonistview.h"
#include "textualprotagonistview.h"
#include "graphicalenemyview.h"
#include "textualenemyview.h"
#include "graphicalhealthpackview.h"
#include "textualhealthpackview.h"
#include "graphicaloverlayview.h"
#include "autoplaycontroller.h"

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

public slots:
    void zoomIn();
    void zoomOut();
    void updateMainUI();
    void processCommand();
    void onTabChanged(int index);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *graphicsScene;
    QTextEdit *textScene;

    GameController* gameController;
    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels;
    AutoPlayController* autoplay;

    World world;
    View* currentWorldView;
    GraphicalWorldView* graphicalWorldView;
    TextualWorldView* textualWorldView;
    GraphicalProtagonistView* graphicalProtagonistView;
    TextualProtagonistView* textualProtagonistView;
    GraphicalEnemyView* graphicalEnemyView;
    TextualEnemyView* textualEnemyView;
    GraphicalHealthpackView* graphicalHealthpackView;
    TextualHealthpackView* textualHealthpackView;
    GraphicalOverlayView* graphicalOverlayView;

    QHash<QString, std::function<void(const QStringList&)>> commandHandlers;
    QStringList commands;
    QCompleter* completer;

    void setupGraphicsView();
    void setupTextView();
    void setupCommandCompleter();
    void setupCommandHandler();
    void initializeGameComponents();
    void connectSlots();
    void handleGotoCommand(const QStringList &args);
    void executePathFinderTextCommand(const int destPos);
    void attackNearestEnemy();
    void takeNearestHealthPack();
    void displayHelp();
    void setStatBars(float health, float energy);
    void protagonistStatus(float health, float energy);
    void keyPressEvent(QKeyEvent *event) override;
    void switchOverlayStatus();

private slots:
    void on_activeLevelBox_valueChanged(int arg1);
    void on_difficultyBox_valueChanged(int arg1);
    void on_autoplayButton_clicked();
};
#endif // MAINWINDOW_H
