#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColor>
#include <QDebug>
#include <QtLogging>
#include <QLoggingCategory>
#include <QLineEdit>
#include <QStringListModel>

QLoggingCategory MainWindowCat("MainWindow");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), grahpicsScene(new QGraphicsScene(this)), textScene(new QTextEdit(this)), completer(nullptr)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(grahpicsScene);
    ui->textView->setText(textScene->toPlainText());
    ui->textView->setWordWrapMode(QTextOption::NoWrap);
    ui->textView->setFont(QFont("Courier", 10));
    ui->tabWidget->setCurrentIndex(0);

    QStringList commands = {
        "up",
        "down",
        "left",
        "right"
    };

    completer = new QCompleter(commands, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    ui->commandInput->setCompleter(completer);

    levels = LevelManager::GetInstance()->getLevels();
    setupWorldGrid();

    // self.invalidate(self.sceneRect(), QGraphicsScene.ForegroundLayer)
    // ui->graphicsView_2->invalidateScene(ui->graphicsView_2->sceneRect(), QGraphicsScene::BackgroundLayer);
    connect(&gameController, &GameController::updateUI, this, &MainWindow::updateMainUI);
    connect(ui->commandInput, &QLineEdit::returnPressed, this, &MainWindow::processCommand);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    qCInfo(MainWindowCat) << "Making game controller.";
    updateMainUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupWorldGrid() {
    QString imageFile = ":/images/world_images/worldmap.png";
    world.createWorld(imageFile, 1, 1, 0.25f);
    grahpicsScene->addPixmap(QPixmap(imageFile))->setScale(50);
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

void MainWindow::processCommand() {
    QString command = ui->commandInput->text().toLower();
    if (command == "up") {
        gameController.moveProtagonistRelative(0, -50);
    } else if (command == "down") {
        gameController.moveProtagonistRelative(0, 50);
    } else if (command == "left") {
        gameController.moveProtagonistRelative(-50, 0);
    } else if (command == "right") {
        gameController.moveProtagonistRelative(50, 0);
    } else {
        qCInfo(MainWindowCat) << "Invalid command: " << command;
    }
    ui->commandInput->clear();
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

void MainWindow::onTabChanged(int index)
{
    if (index == 0) {
        // Graphical view tab selected
        qCInfo(MainWindowCat) << "Switched to Graphical View.";
    } else if (index == 1) {
        // Text view tab selected
        qCInfo(MainWindowCat) << "Switched to Text View.";

        QString textRepresentation = generateTextRepresentation();
        ui->textView->setPlainText(textRepresentation);
    }
}

QString MainWindow::generateTextRepresentation() {
    // Define the size of the grid
    const int gridWidth = (*levels)[*(gameController.activeLevelIndex)]->cols;
    const int gridHeight = (*levels)[*(gameController.activeLevelIndex)]->rows;
    QVector<QVector<QString>> grid(gridHeight, QVector<QString>(gridWidth, " ")); // Empty grid

    // Create string representation of the grid
    QString representation;
    for (int y = 0; y < gridHeight; ++y) {
        representation += QString("+---").repeated(gridWidth) + "+\n"; // Top border
        for (int x = 0; x < gridWidth; ++x) {
            representation += "| " + grid[y][x] + " ";
        }
        representation += "|\n"; // End of row
    }
    representation += QString("+---").repeated(gridWidth) + "+\n"; // Bottom border

    return representation;
}
