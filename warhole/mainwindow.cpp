#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>

using namespace QLogger;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList("General"), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList("Info"), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList("Warnings"), QLogger::WarnLevel);
    manager->addDestination("./logs/lastrun.log", QStringList("Errors"), QLogger::ErrorLevel);
    manager->addDestination("./logs/errors.log", QStringList("Errors2"), QLogger::ErrorLevel);

    mod = NULL;
    obj = NULL;
    arm = NULL;
    game = NULL;
    ter = NULL;

    // Connect signal from the logger to slot that update the text edit
    QObject::connect(manager, SIGNAL(newLogWritten(QString)), this, SLOT(updateLogOutput(QString)));

    ui->setupUi(this);

    ui->textEdit->setReadOnly(true);

    QMenu *menuFichier = menuBar()->addMenu(tr("&Fichier"));

    QAction *actionLaunchGame = new QAction(tr("&Ecran de jeu"), this);
    menuFichier->addAction(actionLaunchGame);
    connect(actionLaunchGame, SIGNAL(triggered()), this, SLOT(openGameWindow()));

    QAction *actionQuitter = new QAction(tr("&Quitter"), this);
    menuFichier->addAction(actionQuitter);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *menuManageModels = menuBar()->addMenu(tr("&Figurines"));

    QAction *actionCreateModel = new QAction(tr("&Creer une figurine"), this);
    menuManageModels->addAction(actionCreateModel);
    actionCreateModel->setShortcut(QKeySequence("Ctrl+C"));
    connect(actionCreateModel, SIGNAL(triggered()), this, SLOT(openModelWindow()));

    QAction *actionEditModel = new QAction(tr("&Editer une figurine"), this);
    menuManageModels->addAction(actionEditModel);
    actionEditModel->setShortcut(QKeySequence("Ctrl+E"));
    connect(actionEditModel, SIGNAL(triggered()), this, SLOT(openEditModelWindow()));

    QAction *actionManageMagicalObjects = new QAction(tr("&Gérer les objets magiques"), this);
    menuManageModels->addAction(actionManageMagicalObjects);
    actionManageMagicalObjects->setShortcut(QKeySequence("Ctrl+O"));
    connect(actionManageMagicalObjects, SIGNAL(triggered()), this, SLOT(openMagicalObjectWindow()));

    QAction *actionCreateArmy = new QAction(tr("&Créer une armée"), this);
    menuManageModels->addAction(actionCreateArmy);
    actionCreateArmy->setShortcut(QKeySequence("Ctrl+A"));
    connect(actionCreateArmy, SIGNAL(triggered()), this, SLOT(openArmyWindow()));

    QAction *actionEditArmy = new QAction(tr("&Editer une armée"), this);
    menuManageModels->addAction(actionEditArmy);
    actionEditArmy->setShortcut(QKeySequence("Ctrl+D"));
    connect(actionEditArmy, SIGNAL(triggered()), this, SLOT(openEditArmyWindow()));

    QAction *actionCreateTerrains = new QAction(tr("&Créer des décors"), this);
    menuManageModels->addAction(actionCreateTerrains);
    connect(actionCreateTerrains, SIGNAL(triggered()), this, SLOT(openTerrainWindow()));

    //s = new mainWidget(this);
    //setCentralWidget(s);
}

MainWindow::~MainWindow()
{
    if(mod)mod->deleteLater();
    if(arm)arm->deleteLater();
    if(game)game->deleteLater();
    if(obj)obj->deleteLater();
    if(ter)ter->deleteLater();
}


void MainWindow::openModelWindow()
{
    mod = new ModelWindow(); // Be sure to destroy you window somewhere
    mod->show();
}

void MainWindow::openEditModelWindow()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model"), "./models", tr("Model files (*.unit)"));

    mod = new ModelWindow(fileName); // Be sure to destroy you window somewhere
    mod->show();
}

void MainWindow::openArmyWindow()
{
    arm = new ArmyWindow();
    arm->show();
}

void MainWindow::openEditArmyWindow()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Model"), "./armies", tr("Model files (*.army)"));

    arm = new ArmyWindow(fileName);
    arm->show();
}

void MainWindow::openGameWindow()
{
    game = new GameWindow();
    game->show();
}

void MainWindow::openMagicalObjectWindow()
{
    obj = new MagicalObjectWindow();
    obj->show();
}

void MainWindow::openTerrainWindow()
{
    ter = new TerrainWindow();
    ter->show();
}

void MainWindow::updateLogOutput(QString message)
{
    ui->textEdit->insertPlainText(message);
}
