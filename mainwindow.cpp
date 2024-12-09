#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColor>
#include <QDebug>
#include <QtLogging>
#include <QLoggingCategory>
#include "rendermethod.h"
#include "graphicrender.h"

QLoggingCategory MainWindowCat("MainWindow");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->textView->setScene(scene);

    setupWorldGrid();

    // self.invalidate(self.sceneRect(), QGraphicsScene.ForegroundLayer)
    // ui->graphicsView_2->invalidateScene(ui->graphicsView_2->sceneRect(), QGraphicsScene::BackgroundLayer);
    QObject::connect(&gameController, &GameController::updateUI, this, &MainWindow::updateMainUI);

    qCInfo(MainWindowCat) << "Making game controller.";
    updateMainUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWorldGrid() {
    protagonistView = new ProtagonistView(":/images/protagonist.png");
    protagonistView->pixmap->setScale(0.2);
    scene->addItem(protagonistView->pixmap);

    std::shared_ptr<std::vector<std::unique_ptr<Level>>> levels = LevelManager::GetInstance()->getLevels();

    for (int i = 0; i < (int)levels->size(); i++) {
        for (auto& enemy :(*levels)[*(gameController.activeLevelIndex)]->enemies){
            EnemyView* enemyView = new EnemyView(":/images/enemy.png");
            enemyView->pixmap->setScale(0.09);
            scene->addItem(enemyView->pixmap);
            enemyView->renderModel(enemy->getXPos(), enemy->getYPos());
        }
        for (auto& hp :(*levels)[*(gameController.activeLevelIndex)]->healthPacks){
            HealthPackView* healthPackView = new HealthPackView(":/images/health_pack.png");
            healthPackView->pixmap->setScale(0.2);
            scene->addItem(healthPackView->pixmap);
            healthPackView->renderModel(hp->getXPos(),hp->getYPos());
        }
    }

    QString imageFile = ":/images/world_images/worldmap.png";
    world.createWorld(imageFile, 1, 1, 0.25f);
    scene->addPixmap(QPixmap(imageFile))->setScale(50);
}

/*
 *  This method parses key presses and translates them into actions for the game controller
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()){
        case Qt::Key_Z:
            qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST UP";
            gameController.moveProtagonistRelative(0,-50);
            break;
        case Qt::Key_Q:
            qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST LEFT";
            gameController.moveProtagonistRelative(-50,0);
            break;
        case Qt::Key_S:
            qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST DOWN";
            gameController.moveProtagonistRelative(0,50);
            break;
        case Qt::Key_D:
            qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST RIGHT";
            gameController.moveProtagonistRelative(50,0);
            break;
        default:
            qCDebug(MainWindowCat) << "Detected " << event->key() << " being pressed. This currently does not have an action binding.";
    }
}

void MainWindow::zoomIn()
{
    ++tileSize;
}

void MainWindow::zoomOut()
{
    --tileSize;
}

void MainWindow::updateMainUI()
{
    qCInfo(MainWindowCat) << "Updating main window!";
    ui->energy_bar->setValue((int)gameController.getActiveProtagonistEnergy());
    ui->health_bar->setValue((int)gameController.getActiveProtagonistHealth());
}
