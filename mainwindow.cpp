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

    protagonistView = new ProtagonistView();
    TextRender* protagonistTextRender = new TextRender(new QTextEdit);
    GraphicRender* protagonistGraphicRender = new GraphicRender(new QGraphicsPixmapItem(QPixmap(":/images/protagonist.png")));
    std::vector<std::shared_ptr<RenderMethod>> protagonistRender;
    protagonistRender.emplace_back(protagonistTextRender);
    protagonistRender.emplace_back(protagonistGraphicRender);
    protagonistView->setRenderMethods(protagonistRender);
    scene->addItem(protagonistGraphicRender->pixmapItem());

    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(scene);


    QString imageFile = ":/images/world_images/maze2.png";
    world.createWorld(imageFile, 1, 1, 0.25f);
    QPainter p = QPainter();
    ui->graphicsView_2->drawBackground(&p, scene->sceneRect());
    setupWorldGrid();

    // self.invalidate(self.sceneRect(), QGraphicsScene.ForegroundLayer)
    // ui->graphicsView_2->invalidateScene(ui->graphicsView_2->sceneRect(), QGraphicsScene::BackgroundLayer);

    qCInfo(MainWindowCat) << "Making game controller.";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWorldGrid() {
    auto tiles = world.getTiles();

    // GraphicRender *method = new GraphicRender();
    // scene->addItem(method);

    for (auto& tilePtr : tiles) {
        // Tile& tile = *tilePtr;
        int tileXPos = tilePtr->getXPos();
        int tileYPos = tilePtr->getYPos();
        float tileValue = tilePtr->getValue() == INFINITY ? 0 : tilePtr->getValue();


        int greyValue = static_cast<int>(tileValue * 255);
        QColor color(greyValue, greyValue, greyValue);

        QGraphicsRectItem *tileItem = new QGraphicsRectItem(tileXPos * tileSize, tileYPos * tileSize, tileSize, tileSize);
        tileItem->setBrush(color);
        tileItem->setPen(Qt::NoPen);
        scene->addItem(tileItem);
    }
}

/*
 *  This method parses key presses and translates them into actions for the game controller
 */
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int currentXPos = gameController.levels[gameController.activeLevelIndex]->protagonist->getXPos();
    int currentYPos = gameController.levels[gameController.activeLevelIndex]->protagonist->getYPos();
    switch (event->key()){
        case Qt::Key_Z:
            qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST UP";
            gameController.moveProtagonistRelative(0,-1);
            protagonistView->renderModel(currentXPos, currentYPos-1);
            break;
        case Qt::Key_Q:
            qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST LEFT";
            gameController.moveProtagonistRelative(-1,0);
            protagonistView->renderModel(currentXPos-1, currentYPos);
            break;
        case Qt::Key_S:
            qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST DOWN";
            gameController.moveProtagonistRelative(0,1);
            protagonistView->renderModel(currentXPos, currentYPos+1);
            break;
        case Qt::Key_D:
            qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST RIGHT";
            gameController.moveProtagonistRelative(1,0);
            protagonistView->renderModel(currentXPos+1, currentYPos);
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
