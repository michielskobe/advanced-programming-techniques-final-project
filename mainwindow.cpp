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
    ui->textView->setWordWrapMode(QTextOption::NoWrap);
    ui->textView->setFont(QFont("Courier", 10));

    QStringList commands = {"up", "down", "left", "right"};
    completer = new QCompleter(commands, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    ui->commandInput->setCompleter(completer);

    levels = LevelManager::GetInstance()->getLevels();

    graphicalWorldView = new GraphicalWorldView(ui->graphicsView->scene(), ":/images/world_images/worldmap.png");
    textualWorldView = new TextualWorldView(ui->textView);
    currentWorldView = graphicalWorldView;

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
    currentWorldView->updateView();
}

void MainWindow::onTabChanged(int index)
{
    if (index == 0) {
        // Graphical view tab selected
        qCInfo(MainWindowCat) << "Switched to Graphical View.";
        currentWorldView = graphicalWorldView;
    } else if (index == 1) {
        // Text view tab selected
        qCInfo(MainWindowCat) << "Switched to Text View.";
        currentWorldView = textualWorldView;
    }
    currentWorldView->updateView();
}
