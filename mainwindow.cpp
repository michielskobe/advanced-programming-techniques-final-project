#include <functional>
#include <QDebug>
#include <QtLogging>
#include <QLoggingCategory>
#include <QKeyEvent>
#include <QPixmap>
#include <QScrollBar>
#include <QTextEdit>
#include <QLineEdit>
#include <QHash>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "difficultycontroller.h"

QLoggingCategory MainWindowCat("MainWindow");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graphicsScene(new QGraphicsScene(this))
    , completer(nullptr)
{
    // Initialize singletons
    gameController = GameController::GetInstance();
    levels = LevelManager::GetInstance()->getLevels();

    // Setup UI
    ui->setupUi(this);
    ui->activeLevelBox->setMaximum(levels->size()-1);
    setupGraphicsView();
    setupTextView();
    setupCommandHandler();
    setupCommandCompleter();

    // Initialize game components
    initializeGameComponents();

    // Setup connections
    connectSlots();

    // Initial interface update
    qCInfo(MainWindowCat) << "Making game controller.";
    updateMainUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupGraphicsView()
{
    ui->graphicsView->setScene(graphicsScene);
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::setupTextView()
{
    ui->textView->setWordWrapMode(QTextOption::NoWrap);
    ui->textView->setFont(QFont("Courier", 10));
    ui->textView->zoomIn(5);
}

void MainWindow::setupCommandCompleter()
{
    commands = commandHandlers.keys();

    completer = new QCompleter(commands, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    ui->commandInput->setCompleter(completer);
}

void MainWindow::setupCommandHandler()
{
    commandHandlers["up"] = [this](const QStringList &) {
        gameController->moveProtagonistRelative(0, -1);
        qCInfo(MainWindowCat) << "Moving up";
    };
    commandHandlers["down"] = [this](const QStringList &) {
        gameController->moveProtagonistRelative(0, 1);
        qCInfo(MainWindowCat) << "Moving down";
    };
    commandHandlers["left"] = [this](const QStringList &) {
        gameController->moveProtagonistRelative(-1, 0);
        qCInfo(MainWindowCat) << "Moving left";
    };
    commandHandlers["right"] = [this](const QStringList &) {
        gameController->moveProtagonistRelative(1, 0);
        qCInfo(MainWindowCat) << "Moving right";
    };
    commandHandlers["goto"] = [this](const QStringList &args) {
        handleGotoCommand(args);
    };
    commandHandlers["help"] = [this](const QStringList &) {
        displayHelp();
    };
}

void MainWindow::initializeGameComponents()
{
    graphicalWorldView = new GraphicalWorldView(ui->graphicsView->scene());
    textualWorldView = new TextualWorldView(ui->textView);
    currentWorldView = graphicalWorldView;

    graphicalEnemyView = new GraphicalEnemyView(ui->graphicsView->scene());
    textualEnemyView = new TextualEnemyView(ui->textView);

    graphicalHealthpackView = new GraphicalHealthpackView(ui->graphicsView->scene());
    textualHealthpackView = new TextualHealthpackView(ui->textView);

    graphicalProtagonistView = new GraphicalProtagonistView(ui->graphicsView->scene());
    textualProtagonistView = new TextualProtagonistView(ui->textView);

    graphicalOverlayView = new GraphicalOverlayView(ui->graphicsView->scene());
}

void MainWindow::connectSlots()
{
    connect(gameController, &GameController::updateUI, this, &MainWindow::updateMainUI);
    connect(ui->commandInput, &QLineEdit::returnPressed, this, &MainWindow::processCommand);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    connect(ui->zoomInBtn, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(ui->zoomOutBtn, &QPushButton::clicked, this, &MainWindow::zoomOut);
    connect(ui->overlayButton, &QPushButton::clicked, this,&MainWindow::switchOverlayStatus);
}

void MainWindow::handleGotoCommand(const QStringList &args)
{
    if (args.size() != 2) {
        qCInfo(MainWindowCat) << "Usage: goto x y";
        return;
    }

    bool validX, validY;
    int x = args[0].toInt(&validX);
    int y = args[1].toInt(&validY);

    if (!validX || !validY) {
        qCInfo(MainWindowCat) << "Invalid coordinates.";
        return;
    }

    qCInfo(MainWindowCat) << "Moving protagonist to: " << x << y;
    // TODO: Implement move protagonist to (x, y)
}

void MainWindow::displayHelp()
{
    QString helpText = "Available commands:\n";
    for (const auto &command : commands) {
        helpText += " - " + command + "\n";
    }

    ui->help_label->setText(helpText);
    ui->help_label->setHidden(false);
    qCInfo(MainWindowCat) << helpText;
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

void MainWindow::processCommand()
{
    QString commandLine = ui->commandInput->text().toLower();
    QStringList parts = commandLine.split(" ");
    QString command = parts.takeFirst();

    if (commandHandlers.contains(command)) {
        commandHandlers[command](parts);
    } else {
        qCInfo(MainWindowCat) << "Invalid command: " << command;
    }

    ui->commandInput->clear();
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


void MainWindow::zoomIn()
{
    if (currentWorldView == graphicalWorldView){
        ui->graphicsView->scale(1.1, 1.1);
    }
    else if (currentWorldView == textualWorldView && ui->textView->font().pointSize() < 18){
        // Increase font size
        QFont font = ui->textView->font();
        int currentFontSize = font.pointSize();
        font.setPointSize(currentFontSize + 1);
        ui->textView->setFont(font);

        // Decrease nr of visisble rows and collums
        textualRepresentation.visibleWidth -= 1;
        textualRepresentation.visibleHeight -= 1;

        // Adjust border
        textualRepresentation.firstVisibleRow = std::min(textualRepresentation.firstVisibleRow, 2 * ((*levels)[*(gameController->getActiveLevelIndex())]->rows - textualRepresentation.visibleHeight));
        textualRepresentation.firstVisibleCol = std::min(textualRepresentation.firstVisibleCol, 4 * ((*levels)[*(gameController->getActiveLevelIndex())]->cols - textualRepresentation.visibleWidth));
    }
    updateMainUI();
}



void MainWindow::zoomOut()
{
    if (currentWorldView == graphicalWorldView){
        ui->graphicsView->scale(0.9, 0.9);
    }
    else if (currentWorldView == textualWorldView && ui->textView->font().pointSize() > 10){
        // Decrease font size
        QFont font = ui->textView->font();
        int currentFontSize = font.pointSize();
        font.setPointSize(currentFontSize - 1);
        ui->textView->setFont(font);

        // Increase nr of visisble rows and collums
        textualRepresentation.visibleWidth += 1;
        textualRepresentation.visibleHeight += 1;

        // Adjust border
        textualRepresentation.firstVisibleRow = std::min(textualRepresentation.firstVisibleRow, 2 * ((*levels)[*(gameController->getActiveLevelIndex())]->rows - textualRepresentation.visibleHeight));
        textualRepresentation.firstVisibleCol = std::min(textualRepresentation.firstVisibleCol, 4 * ((*levels)[*(gameController->getActiveLevelIndex())]->cols - textualRepresentation.visibleWidth));
    }
    updateMainUI();


}

void MainWindow::updateMainUI()
{
    qCInfo(MainWindowCat) << "Updating main window!";

    // Update stats bars
    setStatBars(gameController->getActiveProtagonistHealth(), gameController->getActiveProtagonistEnergy());

    // Update protagonist status
    protagonistStatus(gameController->getActiveProtagonistHealth(), gameController->getActiveProtagonistEnergy());

    // Update world view
    currentWorldView->updateView();
    if (currentWorldView == graphicalWorldView){
        graphicalEnemyView->updateView();
        graphicalProtagonistView->updateView();
        graphicalHealthpackView->updateView();
        graphicalOverlayView->updateView();
    }
    else if (currentWorldView == textualWorldView){
        int verticalScrollPos = ui->textView->verticalScrollBar()->value();
        int horizontalScrollPos = ui->textView->horizontalScrollBar()->value();

        textualEnemyView->updateView();
        textualHealthpackView->updateView();
        textualProtagonistView->updateView();

        ui->textView->verticalScrollBar()->setValue(verticalScrollPos);
        ui->textView->horizontalScrollBar()->setValue(horizontalScrollPos);
    }

    // Center view on protagonist
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
        ui->overlayButton->setHidden(false);
        ui->overlay_label->setHidden(false);
    } else if (index == 1) {
        // Text view tab selected
        qCInfo(MainWindowCat) << "Switched to Text View.";
        currentWorldView = textualWorldView;
        ui->overlayButton->setHidden(true);
        ui->overlay_label->setHidden(true);
    }
    updateMainUI();
}

void MainWindow::switchOverlayStatus(){
    if (graphicalOverlayView->getOverlayStatus()){
        ui->overlayButton->setText("Enable");
    }
    else {
        ui->overlayButton->setText("Disable");
    }
    graphicalOverlayView->switchOverlayStatus();
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
