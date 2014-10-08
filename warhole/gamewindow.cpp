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

    ///////////////////////////////////////////
    //ui parameters
    //View and scene
    ///////////////////////////////////////////
    view.setScene(&scene);
    ui->horizontalLayout->addWidget(&view);

    // Chat widget
    cw = new ChatWidget(this);
    ui->dockWidget_2->setWidget(cw);

    ///////////////////////////////////////////
    //Tree view of army
    ///////////////////////////////////////////
    armyModel = new QStandardItemModel(this);
    ui->treeViewArmy->setModel(armyModel);
    ui->treeViewArmy->setContextMenuPolicy((Qt::CustomContextMenu));
    QObject::connect(ui->treeViewArmy,
                     SIGNAL(customContextMenuRequested(QPoint)),
                     SLOT(openArmyModelContextMenu(QPoint)));

    ///////////////////////////////////////////
    //background of the game (To be removed afterwards)
    ///////////////////////////////////////////
    if(!background.load("C:/Users/Psycko/Documents/GitHub/Warhole/warhole/ressources/floor_grass5.jpg"))
    {
        QLog_Error(LOG_ID_ERR, "GAMEWINDOW : Can't load background image");
    }

    backGroundBrush = new QBrush(QColor(51,102,0));
    backGroundBrush = new QBrush(background);
    scene.setBackgroundBrush(*backGroundBrush);

    back = new BackGroundItem(5400,2700);
    scene.addItem(back);

    ///////////////////////////////////////////
    //Actions
    ///////////////////////////////////////////
    connect(ui->actionRuler_6_inches, SIGNAL(triggered()),this, SLOT(add6InchesRuler()));
    connect(ui->actionRuler_12_inches, SIGNAL(triggered()),this, SLOT(add12InchesRuler()));
    connect(ui->actionRuler_18_inches, SIGNAL(triggered()),this, SLOT(add18InchesRuler()));
    connect(ui->actionRuler_24_inches, SIGNAL(triggered()),this, SLOT(add24InchesRuler()));

    actionDeploy = new QAction(tr("Déployer"), this);
    connect(actionDeploy, SIGNAL(triggered()),this,SLOT(deployRegiment()));

    connect(ui->actionOpen_Army, SIGNAL(triggered()), this, SLOT(openArmyMenuClicked()));

    ///////////////////////////////////////////
    // Network interface
    ///////////////////////////////////////////
    netInterface = NULL;

    comManager = new CommandManager(&inQueue, &outQueue, &game, this);
    connect(comManager, SIGNAL(newChatMessageAvailable(QString, QString)), cw, SLOT(printNewChatMessage(QString, QString)));
    connect(cw, SIGNAL(newMessageToSend(QString)),comManager, SLOT(enQueueChatMessage(QString)));
}

GameWindow::~GameWindow()
{
    delete ui;
    delete back;
    armyModel->deleteLater();
    actionDeploy->deleteLater();
    cw->deleteLater();
    if (netInterface) netInterface->deleteLater();
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

void GameWindow::add6InchesRuler()
{
    addRulerToScene(6);
}

void GameWindow::add12InchesRuler()
{
    addRulerToScene(12);
}

void GameWindow::add18InchesRuler()
{
    addRulerToScene(18);
}

void GameWindow::add24InchesRuler()
{
    addRulerToScene(24);
}

void GameWindow::addRulerToScene(int l)
{
    RulerGraphics* r = new RulerGraphics(l);
    scene.addItem(r);
    r->setPos(back->getW()/2, back->getH()/2);
}

void GameWindow::openArmyMenuClicked()
{
    loadArmy();
}

void GameWindow::createNetworkInterface(NetworkType t)
{
    if(netInterface)
    {
        delete netInterface;
    }

    switch(t)
    {
    case SERVER:
        netInterface = new NetworkServer(&inQueue, &outQueue, this);
        break;
    case CLIENT:
        netInterface = new NetworkClient(&inQueue, &outQueue, this);
        break;
    default:
        //TODO error
        break;
    }

    connect(netInterface, SIGNAL(stateChanged(QString)),this, SLOT(printNetworkState(QString)));
    connect(&outQueue, SIGNAL(newMessageAvailable()), netInterface, SLOT(send()));
    connect(netInterface, SIGNAL(networkEvent(NetworkEvent, QString)), comManager, SLOT(handleNetworkEvent(NetworkEvent, QString)));
    printNetworkState(netInterface->getState());
}

void GameWindow::on_actionHost_Game_triggered()
{
    GameConfiguratorDialog d;
    d.setModal(true);
    d.setG(&game);
    if(d.exec())
    {
        createNetworkInterface(SERVER);
        // TODO ugly
        printNetworkState(tr("<strong><font color=\"blue\"> Partie créée :</strong></font>") +
             "- " + game.getName() + "\n" +
             "- " + game.getInformation() + "\n" +
             "- " + QString::number(game.getPlayerNumber()) + tr(" joueurs max.\n") +
             "- " + QString::number(game.getPoints()) + tr(" points\n"));
        if(game.getSpectators())
             printNetworkState(tr("- Spéctateurs autorisés."));
        else
             printNetworkState(tr("- Spéctateurs non autorisés."));
    }
}

void GameWindow::on_actionConnect_to_a_game_2_triggered()
{
    createNetworkInterface(CLIENT);
}

void GameWindow::printNetworkState(QString state)
{
    cw->appendString(state);
}
