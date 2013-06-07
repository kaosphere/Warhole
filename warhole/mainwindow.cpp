#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

    QAction *actionCreateModel = new QAction("&Creer une figurine", this);
    menuFichier->addAction(actionCreateModel);
    actionCreateModel->setShortcut(QKeySequence("Ctrl+C"));
    connect(actionCreateModel, SIGNAL(triggered()), this, SLOT(openModelWindow()));

    QAction *actionEditModel = new QAction("&Editer une figurine", this);
    menuFichier->addAction(actionEditModel);
    actionEditModel->setShortcut(QKeySequence("Ctrl+E"));
    connect(actionEditModel, SIGNAL(triggered()), this, SLOT(openEditModelWindow()));

    QAction *actionCreateArmy = new QAction("&Créer une armée", this);
    menuFichier->addAction(actionCreateArmy);
    actionCreateArmy->setShortcut(QKeySequence("Ctrl+A"));
    connect(actionCreateArmy, SIGNAL(triggered()), this, SLOT(openArmyWindow()));

    QAction *actionEditArmy = new QAction("&Editer une armée", this);
    menuFichier->addAction(actionEditArmy);
    actionEditArmy->setShortcut(QKeySequence("Ctrl+D"));
    connect(actionEditArmy, SIGNAL(triggered()), this, SLOT(openEditArmyWindow()));

    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionQuitter);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    //s = new mainWidget(this);
    //setCentralWidget(s);
}

MainWindow::~MainWindow()
{
    //delete mod;
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
