#include "gamewindow.h"
#include "ui_gamewindow.h"

const QString GameWindow::LOG_ID_INFO = "GameWindow_info";
const QString GameWindow::LOG_ID_TRACE = "GameWindow_trace";
const QString GameWindow::LOG_ID_WARN = "GameWindow_warm";
const QString GameWindow::LOG_ID_ERR = "GameWindow_err";

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
    cw = new ChatWidgetForm(this);
    ui->dockWidget_2->setWidget(cw);
    connect(cw, SIGNAL(newMessageToSend(QString)), &controller, SIGNAL(newChatMessageToSend(QString)));
    connect(&controller, SIGNAL(newChatMessageToPrint(QString,QString)), cw, SLOT(printNewChatMessage(QString,QString)));

    // Display stats widget
    sd = new StatsDisplayForm(this);
    ui->dockWidget_3->setWidget(sd);

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
    connect(ui->actionRuler_6_inches, SIGNAL(triggered()), this, SLOT(add6InchesRuler()));
    connect(ui->actionRuler_12_inches, SIGNAL(triggered()),this, SLOT(add12InchesRuler()));
    connect(ui->actionRuler_18_inches, SIGNAL(triggered()),this, SLOT(add18InchesRuler()));
    connect(ui->actionRuler_24_inches, SIGNAL(triggered()),this, SLOT(add24InchesRuler()));
    connect(this, SIGNAL(requestNewRuler(int)), &controller, SIGNAL(addRulerToGameSceneRequest(int)));
    connect(&controller, SIGNAL(addRulerToGameScene(QString, int)), this, SLOT(addRulerToScene(QString, int)));
    connect(&controller, SIGNAL(removeRuler(QString)), this, SLOT(removeRulerFromScene(QString)));
    connect(&controller, SIGNAL(removeTemplate(QString)), this, SLOT(removeRulerFromScene(QString)));

    connect(this, SIGNAL(requestNewRoundTemplate(int)), &controller, SIGNAL(addRoundTemplateToGameSceneRequest(int)));
    connect(&controller, SIGNAL(addRoundTemplateScene(QString,int)), this, SLOT(addRoundTemplateToScene(QString, int)));


    actionDeploy = new QAction(tr("Déployer"), this);
    connect(actionDeploy, SIGNAL(triggered()),this,SLOT(deployRegiment()));
    // Deployment signals
    connect(this, SIGNAL(newRegimentRequest(QString, RegimentAbstract)), &controller, SIGNAL(addRegimentRequest(QString, RegimentAbstract)));
    connect(&controller, SIGNAL(createRegiment(QString,QString,RegimentAbstract)), this, SLOT(addRegimentToGameScene(QString, QString, RegimentAbstract)));

    connect(ui->actionOpen_Army, SIGNAL(triggered()), this, SLOT(openArmyMenuClicked()));


    /////////////////////////////////////////////
    //GameController
    /////////////////////////////////////////////
    connect(&controller, SIGNAL(refreshPlayerListDisplay(QList<Player>)), cw, SLOT(refreshPlayerListDisplay(QList<Player>)));
    connect(&controller, SIGNAL(moveRuler(QString,QPointF, QTransform)), this, SLOT(moveRuler(QString,QPointF, QTransform)));
    connect(&controller, SIGNAL(networkEvent(QString)), this, SLOT(printSpecialMessage(QString)));
    connect(&controller, SIGNAL(moveTemplate(QString,QPointF)), this, SLOT(moveTemplate(QString, QPointF)));
}

GameWindow::~GameWindow()
{
    delete ui;
    delete back;
    armyModel->deleteLater();
    actionDeploy->deleteLater();
    cw->deleteLater();
}

void GameWindow::closeEvent(QCloseEvent *)
{
    controller.disconnectNetworkInterface();
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
    RegimentAbstract r = army.getUnits().at(indexArmy.row());
    emit newRegimentRequest(controller.getGame().getMe(), r);

    // Remove the regiment deployed from the army list
    army.removeUnit(army.getUnits().at(indexArmy.row()));
    updateArmyList();
    // Create new regimentGraphics with selected one
    /*RegimentGraphics* r = new RegimentGraphics(
                army.getUnits().at(indexArmy.row()));
    scene.addItem(r);*/
}

void GameWindow::addRegimentToGameScene(QString id, QString owner, RegimentAbstract r)
{
    if(!regimentMap.contains(id))
    {
        RegimentGraphics* rg;
        if(owner == controller.getGame().getMe())
        {
            rg = new RegimentGraphics(r, true);
        }
        else
        {
            rg = new RegimentGraphics(r, false);
        }
        rg->setRegimentID(id);
        rg->setOwner(owner);

        regimentMap[id] = rg;
        scene.addItem(rg);
    }
}

void GameWindow::add6InchesRuler()
{
    emit requestNewRuler(6);
}

void GameWindow::add12InchesRuler()
{
    emit requestNewRuler(12);
}

void GameWindow::add18InchesRuler()
{
    emit requestNewRuler(18);
}

void GameWindow::add24InchesRuler()
{
    emit requestNewRuler(24);
}

void GameWindow::addRulerToScene(QString id, int l)
{
    RulerGraphics* r = new RulerGraphics(l, id);
    connect(r, SIGNAL(rulerMoved(QString, QPointF, QTransform)), &controller, SIGNAL(rulerMoved(QString, QPointF, QTransform)));
    connect(r, SIGNAL(removeRuler(QString)), &controller, SIGNAL(removeRulerRequest(QString)));
    scene.addItem(r);
    r->setPos(back->getW()/2, back->getH()/2);

    // Assume that id will be unique for now
    toolItemList[id] = r;
}

void GameWindow::moveRuler(QString id, QPointF p, QTransform matrix)
{
    if(toolItemList.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "moveRuler() : ruler with ID " + id + " found, now moving it.");
        toolItemList[id]->setPos(p);
        toolItemList[id]->setTransform(matrix);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "moveRuler() : ruler with ID " + id + " not found is item list.");
    }
}

void GameWindow::removeRulerFromScene(QString id)
{
    if(toolItemList.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "moveRuler() : ruler (or template) with ID " + id + " found, now removing it.");
        QGraphicsItem* r = toolItemList[id];
        scene.removeItem(r);
        delete r;
        toolItemList.remove(id);
    }
}

void GameWindow::openArmyMenuClicked()
{
    loadArmy();
}

void GameWindow::on_actionHost_Game_triggered()
{
    GameConfiguratorDialog d;
    d.setModal(true);
    d.setG(controller.getGamePtr());
    if(d.exec())
    {
        controller.createNetworkInterface(SERVER);
        // TODO ugly
        printSpecialMessage(tr("<strong><font color=\"blue\"> Partie créée :</strong></font>\n\r") +
             "- " + controller.getGame().getName() + "\n\r" +
             "- " + controller.getGame().getInformation() + "\n\r" +
             "- " + QString::number(controller.getGame().getPlayerNumber()) + tr(" joueurs max.\n\r") +
             "- " + QString::number(controller.getGame().getPoints()) + tr(" points\n\r"));
        if(controller.getGame().getSpectators())
             printSpecialMessage(tr("- Spéctateurs autorisés.\n\r"));
        else
             printSpecialMessage(tr("- Spéctateurs non autorisés.\n\r"));
    }
}

void GameWindow::on_actionConnect_to_a_game_2_triggered()
{
    ClientInfo info;
    ConnectToServerDialog d;
    d.setModal(true);
    d.setG(controller.getGamePtr());
    d.setInfo(&info);
    if(d.exec())
    {
        controller.createNetworkInterface(CLIENT, info.ip);
    }
}

void GameWindow::printSpecialMessage(QString state)
{
    cw->appendString(state);
}

void GameWindow::on_actionExpTemplateSmall_triggered()
{
    emit requestNewRoundTemplate(3);
}

void GameWindow::on_actionExpTemplateBig_triggered()
{
    emit requestNewRoundTemplate(5);
}

void GameWindow::addRoundTemplateToScene(QString id, int d)
{
    RoundTemplateGraphics* r = new RoundTemplateGraphics(d, id);
    connect(r, SIGNAL(templateMoved(QString,QPointF)), &controller, SIGNAL(templateMoved(QString, QPointF)));
    connect(r, SIGNAL(removeTemplateRequest(QString)), &controller, SIGNAL(removeTemplateRequest(QString)));
    scene.addItem(r);
    r->setPos(back->getW()/2, back->getH()/2);

    // Assume that id will be unique for now
    toolItemList[id] = r;
}

void GameWindow::moveTemplate(QString id, QPointF p)
{
    if(toolItemList.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "moveTemplate() : template with ID " + id + " found, now moving it.");
        toolItemList[id]->setPos(p);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "moveTemplate() : template with ID " + id + " not found is item list.");
    }
}


