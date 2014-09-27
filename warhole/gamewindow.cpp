#include "gamewindow.h"
#include "ui_gamewindow.h"

const QString GameWindow::LOG_ID_INFO = "testGI_info";
const QString GameWindow::LOG_ID_TRACE = "testGI_trace";
const QString GameWindow::LOG_ID_WARN = "testGI_warm";
const QString GameWindow::LOG_ID_ERR = "testGI_err";

using namespace QLogger;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    initGameWindow();
}

void GameWindow::initGameWindow()
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    //ui parameters
    //View and scene
    view.setScene(&scene);
    ui->horizontalLayout->addWidget(&view);


    //Tree view of army
    armyModel = new QStandardItemModel(this);
    ui->treeViewArmy->setModel(armyModel);
    ui->treeViewArmy->setContextMenuPolicy((Qt::CustomContextMenu));
    QObject::connect(ui->treeViewArmy,
                     SIGNAL(customContextMenuRequested(QPoint)),
                     SLOT(openArmyModelContextMenu(QPoint)));



    //background of the game (To be removed afterwards)
    if(!background.load("C:/Users/Psycko/Documents/GitHub/Warhole/warhole/ressources/floor_grass5.jpg"))
    {
        QLog_Error(LOG_ID_ERR, "GAMEWINDOW : Can't load background image");
    }

    backGroundBrush = new QBrush(QColor(51,102,0));
    backGroundBrush = new QBrush(background);
    scene.setBackgroundBrush(*backGroundBrush);

    back = new BackGroundItem(5400,2700);
    scene.addItem(back);


    //Actions
    actionDeploy = new QAction(tr("Déployer"), this);
    connect(actionDeploy, SIGNAL(triggered()),this,SLOT(deployRegiment()));

    connect(ui->actionOpen_Army, SIGNAL(triggered()), this, SLOT(openArmyMenuClicked()));
}

GameWindow::~GameWindow()
{
    delete ui;
    delete back;
    armyModel->deleteLater();
    actionDeploy->deleteLater();
}

void GameWindow::loadArmy()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open army"), ARMY_PATH, tr("Model files (*.army)"));

    QLog_Info(LOG_ID_INFO, "loadArmy(): Path of army to be loaded : " + fileName);
    if(!fileName.isEmpty())
    {
        army.load(fileName);
        QLog_Info(LOG_ID_INFO, "Army loaded : ");
        QLog_Info(LOG_ID_INFO, army.displayInfo());
    }

    updateArmyList();
}

void GameWindow::updateArmyList()
{
    armyModel->clear();
    for(int i=0; i<army.getUnits().size(); ++i)
    {
        QList<QStandardItem *> newRegiment;
        newRegiment<<new QStandardItem(QString::number(army.getUnits().at(i).computeTotalNb()))
                <<new QStandardItem(army.getUnits().at(i).getName())
                <<new QStandardItem(QString::number(army.getUnits().at(i).computePoints()));
        armyModel->appendRow(newRegiment);
    }
}

void GameWindow::openArmyModelContextMenu(QPoint pos)
{
    indexArmy =ui->treeViewArmy->indexAt(pos);

    if(indexArmy.isValid())
    {
        QMenu *menu=new QMenu(this);
        menu->addAction(actionDeploy);
        menu->popup(ui->treeViewArmy->viewport()->mapToGlobal(pos));
    }
}

void GameWindow::deployRegiment()
{
    // Create new regimentGraphics with selected one
    RegimentGraphics* r = new RegimentGraphics(
                army.getUnits().at(indexArmy.row()));
    scene.addItem(r);
}

bool GameWindow::addPlayerToGame(Player p)
{
    return game.addPlayer(p);
}

bool GameWindow::addArmyToPlayer(Army a, QString playerName)
{
    return game.addArmyToPlayer(a, playerName);
}

void GameWindow::openArmyMenuClicked()
{
    loadArmy();
}
