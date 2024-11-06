#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);;

    QString imageFile = ":/images/test2.jpg";
    world.createWorld(imageFile, 1, 1, 0.25f);
    setupWorldGrid();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWorldGrid() {
    auto tiles = world.getTiles();

    for (auto& tilePtr : tiles) {
        Tile& tile = *tilePtr;
        int tileXPos = tile.getXPos();
        int tileYPos = tile.getYPos();
        float tileValue = tile.getValue();

        int greyValue = static_cast<int>(tileValue * 255);
        QColor color(greyValue, greyValue, greyValue);

        QGraphicsRectItem *tileItem = new QGraphicsRectItem(tileXPos * tileSize, tileYPos * tileSize, tileSize, tileSize);
        tileItem->setBrush(color);
        tileItem->setPen(Qt::NoPen);
        scene->addItem(tileItem);
    }
}
