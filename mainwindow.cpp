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
#include "difficultycontroller.h"

QLoggingCategory MainWindowCat("MainWindow");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), grahpicsScene(new QGraphicsScene(this)), textScene(new QTextEdit(this)), completer(nullptr)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(grahpicsScene);
    ui->textView->setWordWrapMode(QTextOption::NoWrap);
    ui->textView->setFont(QFont("Courier", 10));

    // Set up commands for text view
    QStringList commands = {"up", "down", "left", "right", "goto", "attack nearest enemy", "take nearest health pack", "help"};
    completer = new QCompleter(commands, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    ui->commandInput->setCompleter(completer);

    commandHandlers["up"] = [this](const QStringList &) {
        gameController->moveProtagonistRelative(0, -1);
        qCInfo(MainWindowCat) << "Moving up";
        ui->help_label->setHidden(true);
    };
    commandHandlers["down"] = [this](const QStringList &) {
        gameController->moveProtagonistRelative(0, 1);
        qCInfo(MainWindowCat) << "Moving down";
        ui->help_label->setHidden(true);
    };
    commandHandlers["left"] = [this](const QStringList &) {
        gameController->moveProtagonistRelative(-1, 0);
        qCInfo(MainWindowCat) << "Moving left";
        ui->help_label->setHidden(true);
    };
    commandHandlers["right"] = [this](const QStringList &) {
        gameController->moveProtagonistRelative(1, 0);
        qCInfo(MainWindowCat) << "Moving right";
        ui->help_label->setHidden(true);
    };
    commandHandlers["goto"] = [this](const QStringList &args) {
        if (args.size() != 2) {
            qCInfo(MainWindowCat) << "Usage: goto x y";
            return;
        }
        bool validX, validY;
        int x = args[0].toInt(&validX);
        int y = args[1].toInt(&validY);

        if (!validX || !validY) {
            qCInfo(MainWindowCat) << "Invalid coordinates";
            return;
        }

        // TODO: MOVE PROTAGONIST TO GIVEN LOCATION
        qCInfo(MainWindowCat) << "Moving protagonist to:" << x << y;
        ui->help_label->setHidden(true);
    };
    commandHandlers["attack nearest enemy"] = [this](const QStringList &) {
        // TODO: ATTACK NEAREST ENEMY
        qCInfo(MainWindowCat) << "Attacking nearest enemy";
        ui->help_label->setHidden(true);
    };
    commandHandlers["take nearest health pack"] = [this](const QStringList &) {
        // TODO: TAKE NEAREST HEALTH PACK
        qCInfo(MainWindowCat) << "Taking nearest health pack";
        ui->help_label->setHidden(true);
    };
    commandHandlers["help"] = [this, commands](const QStringList &) {
        ui->help_label->setText("Available commands:\n");
        qCInfo(MainWindowCat) << "Available commands:";
        for (const auto &command : commands) {
            qCInfo(MainWindowCat) << " - " << command;
            ui->help_label->setText(ui->help_label->text() + " - " + command + "\n");
        }
        ui->help_label->setHidden(false);
    };

    // Create instances of singletons
    gameController = GameController::GetInstance();
    levels = LevelManager::GetInstance()->getLevels();

    // Set up world view
    graphicalWorldView = new GraphicalWorldView(ui->graphicsView->scene());
    textualWorldView = new TextualWorldView(ui->textView);
    textualWorldView->updateView();

    // Set up enemy views
    graphicalEnemyView = new GraphicalEnemyView(ui->graphicsView->scene());
    textualEnemyView = new TextualEnemyView(ui->textView, textualWorldView);

    // Set up healthpack views
    graphicalHealthpackView = new GraphicalHealthpackView(ui->graphicsView->scene());
    textualHealthpackView = new TextualHealthpackView(ui->textView, textualWorldView);

    // Set up protagonist views
    graphicalProtagonistView = new GraphicalProtagonistView(ui->graphicsView->scene());
    textualProtagonistView = new TextualProtagonistView(ui->textView, textualWorldView);

    // Start game in graphical view
    currentWorldView = graphicalWorldView;
    ui->tabWidget->setCurrentIndex(0);

    // Connect signals to slots
    connect(gameController, &GameController::updateUI, this, &MainWindow::updateMainUI);
    connect(ui->commandInput, &QLineEdit::returnPressed, this, &MainWindow::processCommand);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    connect(ui->zoomInBtn, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(ui->zoomOutBtn, &QPushButton::clicked, this, &MainWindow::zoomOut);

    // Update interface
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
        gameController->moveProtagonistRelative(0,-1);
        break;
    case Qt::Key_Q:
        qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST LEFT";
        gameController->moveProtagonistRelative(-1,0);
        break;
    case Qt::Key_S:
        qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST DOWN";
        gameController->moveProtagonistRelative(0,1);
        break;
    case Qt::Key_D:
        qCInfo(MainWindowCat) << "Detected input: MOVE PROTAGONIST RIGHT";
        gameController->moveProtagonistRelative(1,0);
        break;
    default:
        qCDebug(MainWindowCat) << "Detected " << event->key() << " being pressed. This currently does not have an action binding.";
    }
}

void MainWindow::setStatBars(float health, float energy)
{
    ui->energy_bar->setValue((int)energy);
    ui->health_bar->setValue((int)health);
}

void MainWindow::protagonistStatus(float health, float energy)
{
    if(health == 0.0f || energy == 0.0f){
        ui->protagonist_label->setHidden(false);
    } else {
        ui->protagonist_label->setHidden(true);
    }
}

void MainWindow::processCommand() {
    QString commandLine = ui->commandInput->text().toLower();
    if (commandHandlers.contains(commandLine)) {
        commandHandlers[commandLine]({});
    } else {
        QStringList parts = commandLine.split(" ");
        QString command = parts.takeFirst();
        QStringList args = parts;

        if (commandHandlers.contains(command)) {
            commandHandlers[command](args);
        } else {
            qCInfo(MainWindowCat) << "Invalid command: " << command;
        }
    }
    ui->commandInput->clear();
}


void MainWindow::zoomIn()
{
    ui->graphicsView->scale(1.1, 1.1);
}

void MainWindow::zoomOut()
{
    ui->graphicsView->scale(0.9, 0.9);
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        event->accept();
        if (event->angleDelta().y() > 0) {
            zoomIn();
        } else {
            zoomOut();
        }
    }
}

void MainWindow::updateMainUI()
{
    qCInfo(MainWindowCat) << "Updating main window!";
    setStatBars(gameController->getActiveProtagonistHealth(), gameController->getActiveProtagonistEnergy());
    protagonistStatus(gameController->getActiveProtagonistHealth(), gameController->getActiveProtagonistEnergy());
    currentWorldView->updateView();
    if (currentWorldView == graphicalWorldView){
        graphicalEnemyView->updateView();
        graphicalProtagonistView->updateView();
        graphicalHealthpackView->updateView();
    }
    else if (currentWorldView == textualWorldView){
        textualEnemyView->updateView();
        textualProtagonistView->updateView();
        textualHealthpackView->updateView();
    }
    QPointF protagonistPos((*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getXPos()*50, (*levels)[*(gameController->getActiveLevelIndex())]->protagonist->getYPos()*50);
    ui->graphicsView->centerOn(protagonistPos);
}

void MainWindow::onTabChanged(int index)
{
    if (index == 0) {
        // Graphical view tab selected
        qCInfo(MainWindowCat) << "Switched to Graphical View.";
        currentWorldView = graphicalWorldView;
        ui->help_label->setHidden(true);
    } else if (index == 1) {
        // Text view tab selected
        qCInfo(MainWindowCat) << "Switched to Text View.";
        currentWorldView = textualWorldView;
    }
    updateMainUI();
}

void MainWindow::on_activeLevelBox_valueChanged(int arg1)
{
    gameController->setActiveLevelIndex(arg1);
    updateMainUI();
}


void MainWindow::on_difficultyBox_valueChanged(int arg1)
{
    DifficultyController::GetInstance()->setDifficultySetting(arg1);
}

