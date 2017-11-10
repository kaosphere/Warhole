#include "gamewindow.h"
#include "ui_gamewindow.h"

#include "version.h"
#include "warholeinfodialog.h"
#include "backgroundselectiondialog.h"

const QString GameWindow::LOG_ID_INFO = "GameWindow_info";
const QString GameWindow::LOG_ID_TRACE = "GameWindow_trace";
const QString GameWindow::LOG_ID_WARN = "GameWindow_warm";
const QString GameWindow::LOG_ID_ERR = "GameWindow_err";

using namespace QLogger;

GameWindow::GameWindow(bool launchServer, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    initGameWindow(launchServer, false);
}

void GameWindow::initGameWindow(bool launchServer, bool messageListHandling)
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
    setWindowTitle("Warhole " +
                   WARHOLE_VERSION_STRING +
                   tr(" - Partie"));

    // Assign the scene to the view only if we want graphics ON
    // Typically, a server would like its graphics OFF to keep ressources for network
    if (!qApp->arguments().contains(NO_GRAPHICS_ARGUMENT))
        view.setScene(&scene);

    ui->horizontalLayout->addWidget(&view);

    // Actions load and save game
    ui->actionCharger_une_partie->setEnabled(false);
    ui->actionSave_Game->setEnabled(false);
    ui->actionOpen_Army->setEnabled(false);
    ui->actionS_lectionner_le_type_de_terrain->setEnabled(false);

    // We check if a message list has to be handled or not
    handleMessageList = qApp->arguments().contains(MESSAGE_LIST_ARGUMENT) || messageListHandling;
    if(handleMessageList)
        QLog_Info(LOG_ID_INFO, "We are handling previous chat message !");

    // Move controller to its thread
    qRegisterMetaType<QList<Player> >();
    qRegisterMetaType<RegimentAbstract>();
    controller.moveToThread(&controllerThread);

    connect(&controller, SIGNAL(networkEnabled(bool)), ui->actionCharger_une_partie, SLOT(setEnabled(bool)));
    connect(&controller, SIGNAL(networkEnabled(bool)), ui->actionSave_Game, SLOT(setEnabled(bool)));
    connect(&controller, SIGNAL(networkEnabled(bool)), ui->actionOpen_Army, SLOT(setEnabled(bool)));
    connect(&controller, SIGNAL(networkEnabled(bool)), this, SLOT(refreshNetworkState(bool)));
    connect(&controller, SIGNAL(networkEnabled(bool)), ui->actionS_lectionner_le_type_de_terrain, SLOT(setEnabled(bool)));

    // Chat widget
    cw = new ChatWidgetForm(this);
    ui->dockWidget_2->setWidget(cw);
    connect(cw, SIGNAL(newMessageToSend(QString, bool, QString)), &controller, SIGNAL(newChatMessageToSend(QString, bool, QString)));
    connect(&controller, SIGNAL(newChatMessageToPrint(QString,QString)), cw, SLOT(printNewChatMessage(QString,QString)));
    if(handleMessageList)
    {
        connect(&controller, SIGNAL(newChatMessageToPrint(QString,QString)), this, SLOT(addChatMessageToList(QString,QString)));
        connect(this, SIGNAL(newMessageToSend(QString, bool, QString)), &controller, SIGNAL(newChatMessageToSend(QString, bool, QString)));
    }

    tabifyDockWidget(ui->dockWidget, ui->dockWidget_5);

    // Terrain
    terrainsModel = new QFileSystemModel(this);

    // Check if terrain folder exists, create it otherwise
    if(!QDir(TERRAIN_PATH).exists()) QDir().mkdir(TERRAIN_PATH);
    ui->treeViewTerrains->setModel(terrainsModel);
    ui->treeViewTerrains->setRootIndex(terrainsModel->setRootPath(TERRAIN_PATH));
    // hide size, type and date collumns
    ui->treeViewTerrains->hideColumn(1);
    ui->treeViewTerrains->hideColumn(2);
    ui->treeViewTerrains->hideColumn(3);
    placeTerrain = new QAction(tr("Placer terrain"), this);
    ui->treeViewTerrains->setContextMenuPolicy((Qt::CustomContextMenu));
    connect(placeTerrain, SIGNAL(triggered()), this, SLOT(placeTerrainRequest()));

    ///////////////////////////////////////////
    /// Tree view of army
    ///////////////////////////////////////////
    armyModel = new QStandardItemModel(this);
    ui->treeViewArmy->setModel(armyModel);
    ui->treeViewArmy->setContextMenuPolicy((Qt::CustomContextMenu));
    QObject::connect(ui->treeViewArmy,
                     SIGNAL(customContextMenuRequested(QPoint)),
                     SLOT(openArmyModelContextMenu(QPoint)));

    /////////////////////////////////////////////////////////
    /// background of the game (To be removed afterwards) ///
    /////////////////////////////////////////////////////////

    backGroundBrush = NULL;

    // Default background type is grass
    updateBackground(GRASS);

    back = new BackGroundItem(5400,2700);
    scene.addItem(back);

    ///////////////////////////////////////////
    /// Actions
    ///////////////////////////////////////////
    connect(ui->actionRuler_6_inches, SIGNAL(triggered()), this, SLOT(add6InchesRuler()));
    connect(ui->actionRuler_12_inches, SIGNAL(triggered()),this, SLOT(add12InchesRuler()));
    connect(ui->actionRuler_18_inches, SIGNAL(triggered()),this, SLOT(add18InchesRuler()));
    connect(ui->actionRuler_24_inches, SIGNAL(triggered()),this, SLOT(add24InchesRuler()));
    connect(this, SIGNAL(requestNewRuler(int)), &controller, SIGNAL(addRulerToGameSceneRequest(int)));
    connect(&controller, SIGNAL(addRulerToGameScene(QString, int)), this, SLOT(addRulerToScene(QString, int)));
    connect(&controller, SIGNAL(removeRuler(QString)), this, SLOT(removeRulerFromScene(QString)));
    connect(&controller, SIGNAL(removeTemplate(QString)), this, SLOT(removeRoundTemplate(QString)));

    connect(this, SIGNAL(requestNewRoundTemplate(int)), &controller, SIGNAL(addRoundTemplateToGameSceneRequest(int)));
    connect(&controller, SIGNAL(addRoundTemplateScene(QString,int)), this, SLOT(addRoundTemplateToScene(QString, int)));

    connect(ui->actionPivoter_la_vue, SIGNAL(triggered()), this, SLOT(rotateView()));
    invertedView = false;

    connect(ui->actionS_lectionner_le_type_de_terrain, SIGNAL(triggered()), this, SLOT(selectTerrainType()));
    connect(this, SIGNAL(requestBackgroundChange(int)), &controller, SIGNAL(requestBackgroundChange(int)));
    connect(&controller, SIGNAL(changeBackground(int)), this, SLOT(changeBackground(int)));

    actionDeploy = new QAction(tr("Déployer"), this);
    connect(actionDeploy, SIGNAL(triggered()),this,SLOT(deployRegiment()));
    // Deployment signals
    connect(this, SIGNAL(newRegimentRequest(QString, RegimentAbstract)), &controller, SIGNAL(addRegimentRequest(QString, RegimentAbstract)));
    connect(&controller, SIGNAL(createRegiment(QString,QString,RegimentAbstract)), this, SLOT(addRegimentToGameScene(QString, QString, RegimentAbstract)));

    connect(ui->actionOpen_Army, SIGNAL(triggered()), this, SLOT(openArmyMenuClicked()));

    /////////////////////////////////////////////
    /// GameController
    /////////////////////////////////////////////
    connect(&controller, SIGNAL(refreshPlayerListDisplay(QList<Player>)), cw, SLOT(refreshPlayerListDisplay(QList<Player>)));
    connect(&controller, SIGNAL(moveRuler(QString,QPointF, QTransform, qreal)), this, SLOT(moveRuler(QString,QPointF, QTransform, qreal)));
    connect(&controller, SIGNAL(networkEvent(QString)), this, SLOT(printSpecialMessage(QString)));
    connect(&controller, SIGNAL(moveTemplate(QString,QPointF)), this, SLOT(moveTemplate(QString, QPointF)));
    connect(&controller, SIGNAL(moveRegiment(QString,QPointF,QTransform, qreal)), this, SLOT(moveRegiment(QString, QPointF, QTransform, qreal)));

    connect(&controller, SIGNAL(removeRegiment(QString)), this, SLOT(removeRegiment(QString)));
    connect(&controller, SIGNAL(removeDeads(QString,int)), this, SLOT(removeDeadsFromRegiment(QString, int)));
    connect(&controller, SIGNAL(changeRegimentWidth(QString,int)), this, SLOT(changeRegimentWidth(QString, int)));
    connect(&controller, SIGNAL(addModels(QString,int)), this, SLOT(addModelToRegiment(QString, int)));
    connect(&controller, SIGNAL(changeRegInfo(QString,RegimentAbstract)), this, SLOT(changeRegInfo(QString, RegimentAbstract)));
    connect(&controller, SIGNAL(showLineOfSight(QString)), this, SLOT(showRegimentLineOfSight(QString)));
    connect(&controller, SIGNAL(hideLineOfSight(QString)), this, SLOT(hideRegimentLineOfSight(QString)));

    connect(&controller, SIGNAL(serverInfoRequested(QString)), this, SLOT(packGameDataForGlobalUpdate(QString)));
    connect(this, SIGNAL(sendGlobalInfoUpdate(QString,QByteArray)), &controller, SIGNAL(sendGlobalInfoUpdate(QString, QByteArray)));
    connect(&controller, SIGNAL(loadGlobalInfoUpdate(QByteArray)), this, SLOT(loadGlobalInfoUpdate(QByteArray)));

    connect(this, SIGNAL(requestNewTerrain(Terrain)), &controller, SIGNAL(requestNewTerrain(Terrain)));
    connect(&controller, SIGNAL(newTerrain(QString, Terrain)), this, SLOT(addNewTerrainToScene(QString, Terrain)));
    connect(&controller, SIGNAL(removeTerrain(QString)), this, SLOT(removeTerrain(QString)));
    connect(&controller, SIGNAL(lockTerrain(QString, bool)), this, SLOT(lockTerrain(QString, bool)));
    connect(&controller, SIGNAL(moveTerrain(QString,QPointF,QTransform, qreal)), SLOT(moveTerrain(QString, QPointF, QTransform, qreal)));

    connect(&controller, SIGNAL(newBlowTemp(QString)), this, SLOT(addNewBlowTemplateToScene(QString)));
    connect(&controller, SIGNAL(moveBlowTemp(QString,QPointF,QTransform, qreal)), this, SLOT(moveBlowTemplate(QString,QPointF,QTransform, qreal)));
    connect(&controller, SIGNAL(removeBlowTemp(QString)), this, SLOT(removeBlowTemplate(QString)));

    connect(ui->actionBlowTemplate, SIGNAL(triggered()), &controller, SIGNAL(requestBlowTemplate()));
    connect(ui->actionActionAddText, SIGNAL(triggered()), this, SLOT(requestNewText()));
    connect(this, SIGNAL(requestNewText(QString)), &controller, SIGNAL(newTextRequest(QString)));
    connect(&controller, SIGNAL(newText(QString, QString)), this, SLOT(addNewTextToScene(QString, QString)));
    connect(&controller, SIGNAL(moveText(QString,QString,QPointF,QTransform, qreal)), this, SLOT(moveText(QString, QString, QPointF, QTransform, qreal)));
    connect(&controller, SIGNAL(removeText(QString)), this, SLOT(removeText(QString)));

    connect(ui->actionScatterDice, SIGNAL(triggered()), this, SLOT(requestNewScatter()));
    connect(this, SIGNAL(requestNewScatter(int)), &controller, SIGNAL(requestNewScatter(int)));
    connect(&controller, SIGNAL(newScatter(QString,int)), this, SLOT(addNewScatterToScene(QString,int)));
    connect(&controller, SIGNAL(moveScatter(QString,QPointF)), this, SLOT(moveScatter(QString, QPointF)));
    connect(&controller, SIGNAL(removeScatter(QString)), this, SLOT(removeScatter(QString)));

    // start controller thread
    controllerThread.start();

    networkOn = false;

    // If launchServer is true, launch a server right away
    if(launchServer)
    {
        QLog_Info(LOG_ID_INFO, "Launching server right away.");
        controller.getGamePtr()->setMe("_SERVER");
        controller.createNetworkInterface(SERVER);
    }
}

GameWindow::~GameWindow()
{
    delete ui;
    delete back;
    armyModel->deleteLater();
    actionDeploy->deleteLater();
    placeTerrain->deleteLater();
    cw->deleteLater();
    controllerThread.quit();
}

void GameWindow::closeEvent(QCloseEvent *)
{
    controller.disconnectNetworkInterface();
}

/**
 * @brief GameWindow::sendAllPreviousChatMessages Sends all previous messages contained in the chat message list
 */
void GameWindow::sendAllPreviousChatMessages(QString sender)
{
    for(int i = 0; i < chatMessageList.length(); ++i)
    {
        emit newMessageToSend(chatMessageList.at(i), true, sender);
    }
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
}

void GameWindow::addRegimentToGameScene(QString id, QString owner, RegimentAbstract r)
{
    if(!regimentMap.contains(id))
    {
        RegimentGraphics* rg;
        if(owner == controller.getGame().getMe())
        {
            rg = new RegimentGraphics(r, true, &invertedView);
        }
        else
        {
            rg = new RegimentGraphics(r, false, &invertedView);
        }
        rg->setRegimentID(id);
        rg->setOwner(owner);


        connect(rg, SIGNAL(regimentMoved(QString,QPointF,QTransform, qreal)), &controller, SIGNAL(regimentMoved(QString, QPointF, QTransform, qreal)));
        connect(rg, SIGNAL(removeRegimentRequest(QString)), &controller, SIGNAL(removeRegimentRequest(QString)));
        connect(rg, SIGNAL(removeDeadsRequest(QString, int)), &controller, SIGNAL(removeDeadsRequest(QString, int)));
        connect(rg, SIGNAL(changeWidthRequest(QString, int)), &controller, SIGNAL(changeWidthRequest(QString, int)));
        connect(rg, SIGNAL(addModelRequest(QString,int)), &controller, SIGNAL(addModelToRegRequest(QString, int)));
        connect(rg, SIGNAL(changeRegimentInfoRequest(QString,RegimentAbstract)), &controller, SIGNAL(changeRegInfoRequest(QString, RegimentAbstract)));
        connect(rg, SIGNAL(lineOfSightRequested(QString)), &controller, SIGNAL(showLineOfSightRequest(QString)));
        connect(rg, SIGNAL(lineOfSightHideRequest(QString)), &controller, SIGNAL(hideLineOfSightRequest(QString)));

        scene.addItem(rg);
        scene.clearSelection();
        regimentMap[id] = rg;

        printSpecialMessage("<em><font color=\"DimGray\"><strong>" + owner + "</strong>" +
                            tr(" a ajouté le régiment ") + r.getName() + tr(" à la partie") + "</em></font>");
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

void GameWindow::selectTerrainType()
{
    backGroundSelectionDialog* w = new backGroundSelectionDialog(this);

    int c;

    w->setChoice(&c);

    if(w->exec())
    {
        emit requestBackgroundChange(c);
    }
}

void GameWindow::addRulerToScene(QString id, int l)
{
    RulerGraphics* r = new RulerGraphics(l, id);
    connect(r, SIGNAL(rulerMoved(QString, QPointF, QTransform, qreal)), &controller, SIGNAL(rulerMoved(QString, QPointF, QTransform, qreal)));
    connect(r, SIGNAL(removeRuler(QString)), &controller, SIGNAL(removeRulerRequest(QString)));
    scene.addItem(r);
    scene.clearSelection();
    r->setPos(back->getW()/2, back->getH()/2);

    // Assume that id will be unique for now
    rulerList[id] = r;
}

void GameWindow::moveRuler(QString id, QPointF p, QTransform matrix, qreal pr)
{
    if(rulerList.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "moveRuler() : ruler with ID " + id + " found, now moving it.");
        rulerList[id]->setPos(p);
        rulerList[id]->setTransform(matrix);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "moveRuler() : ruler with ID " + id + " not found is item list.");
    }
}

void GameWindow::removeRulerFromScene(QString id)
{
    if(rulerList.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "removeRulerFromScene() : ruler with ID " + id + " found, now removing it.");
        QGraphicsItem* r = rulerList[id];
        scene.removeItem(r);
        delete r;
        rulerList.remove(id);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "removeRulerFromScene() : ruler with ID " + id + " not found is map.");
    }
}

void GameWindow::moveRegiment(QString id, QPointF p, QTransform matrix, qreal pr)
{
    if(regimentMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "moveRegiment() : regiment with ID " + id + " found, now moving it.");
        regimentMap[id]->setPos(p);
        regimentMap[id]->setTransform(matrix);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "moveRegiment() : regiment with ID " + id + " not found is item list.");
    }
}

void GameWindow::removeRegiment(QString id)
{
    if(regimentMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "removeRegiment() : regiment with ID " + id + " found, now removing it.");
        RegimentGraphics* r = regimentMap[id];
        printSpecialMessage("<em><font color=\"DimGray\"><strong>" + r->getOwner() + "</strong>" +
                            tr(" a retiré le régiment ") + r->getRegiment().getName() + tr(" de la partie") + "</em></font>");
        scene.removeItem(r);
        delete r;
        regimentMap.remove(id);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "removeRegiment() : regiment with ID " + id + " not found is map.");
    }
}

void GameWindow::removeDeadsFromRegiment(QString id, int nb)
{
    if(regimentMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "removeDeadsFromRegiment() : regiment with ID " + id + " found, now removing " +
                  QString::number(nb) + " deads.");
        regimentMap[id]->removeDeads(nb);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "removeDeadsFromRegiment() : regiment with ID " + id + " not found is map.");
    }
}

void GameWindow::changeRegimentWidth(QString id, int w)
{
    if(regimentMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "removeDeadsFromRegiment() : regiment with ID " + id + " found, now setting wdth to " +
                  QString::number(w));
        regimentMap[id]->setRegimentWidth(w);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "addModelToRegiment() : regiment with ID " + id + " not found is map.");
    }
}

void GameWindow::addModelToRegiment(QString id, int nb)
{
    if(regimentMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "addModelToRegiment() : regiment with ID " + id + " found, now adding " +
                  QString::number(nb) + " models to it");
        regimentMap[id]->addModels(nb);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "addModelToRegiment() : regiment with ID " + id + " not found is map.");
    }
}


void GameWindow::changeRegInfo(QString id, RegimentAbstract r)
{
    if(regimentMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "changeRegInfo() : regiment with ID " + id +
                  " found, now changing regiment info");
        regimentMap[id]->setRegiment(r);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "changeRegInfo() : regiment with ID " + id + " not found is map.");
    }
}

void GameWindow::showRegimentLineOfSight(QString id)
{
    if(regimentMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "showRegimentLineOfSight() : regiment with ID " + id +
                  " found, now displaying line of sight");
        regimentMap[id]->displayLineOfSight();
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "showRegimentLineOfSight() : regiment with ID " + id + " not found is map.");
    }
}

void GameWindow::hideRegimentLineOfSight(QString id)
{
    if(regimentMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "hideRegimentLineOfSight() : regiment with ID " + id +
                  " found, now hiding line of sight");
        regimentMap[id]->hideLineOfSight();
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "hideRegimentLineOfSight() : regiment with ID " + id + " not found is map.");
    }
}

void GameWindow::packGameDataForGlobalUpdate(QString sender)
{
    QByteArray data;

    QDataStream stream(&data, QIODevice::WriteOnly);

    getGlobalInfo(stream);

    emit sendGlobalInfoUpdate(sender, data);

    // If we are handling a copy of all chat messages, send them as well
    if(handleMessageList)
        sendAllPreviousChatMessages(sender);

}

void GameWindow::loadGlobalInfoUpdate(QByteArray info)
{
    QDataStream stream(info);

    setGlobalInfo(stream);
}

void GameWindow::openArmyMenuClicked()
{
    loadArmy();
    emit newMessageToSend("<em><font color=\"DimGray\">" +
                          tr("Armée chargée : ") +
                          army.getName() + " " +
                          QString::number(army.computePoints()) +
                          tr(" points") +  "</em></font>", false);
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
    scene.clearSelection();
    r->setPos(back->getW()/2, back->getH()/2);

    // Assume that id will be unique for now
    roundTemplateList[id] = r;
}

void GameWindow::moveTemplate(QString id, QPointF p)
{
    if(roundTemplateList.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "moveTemplate() : template with ID " + id + " found, now moving it.");
        roundTemplateList[id]->setPos(p);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "moveTemplate() : template with ID " + id + " not found is item list.");
    }
}

void GameWindow::removeRoundTemplate(QString id)
{
    if(roundTemplateList.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "removeRoundTemplate() : round template with ID " + id + " found, now removing it.");
        QGraphicsItem* r = roundTemplateList[id];
        scene.removeItem(r);
        delete r;
        roundTemplateList.remove(id);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "removeRoundTemplate() : round template with ID " + id + " not found is map.");
    }
}

void GameWindow::getGlobalInfo(QDataStream& stream)
{
    QLog_Info(LOG_ID_INFO, "getGlobalInfo(): starting to gather game info...");

    // Store version of the game
    stream << WARHOLE_VERSION_STRING;

    // Store game info
    stream << controller.getGame();

    // Store background
    stream << (int)backType;

    // Store regiments
    stream << regimentMap.size();
    QMap<QString, RegimentGraphics*>::const_iterator i = regimentMap.constBegin();
    while (i != regimentMap.constEnd()) {
        (*i)->serializeOut(stream);
        ++i;
    }

    // Store rulers
    stream << rulerList.size();
    QMap<QString, RulerGraphics*>::const_iterator j = rulerList.constBegin();
    while (j != rulerList.constEnd()) {
        (*j)->serializeOut(stream);
        ++j;
    }

    // Store templates
    stream << roundTemplateList.size();
    QMap<QString, RoundTemplateGraphics*>::const_iterator k = roundTemplateList.constBegin();
    while (k != roundTemplateList.constEnd()) {
        (*k)->serializeOut(stream);
        ++k;
    }
    
    // Store terrains
    stream << terrainMap.size();
    QMap<QString, TerrainGraphics*>::const_iterator l = terrainMap.constBegin();
    while (l != terrainMap.constEnd()) {
        (*l)->serializeOut(stream);
        ++l;
    }
    
    // Store blow templates
    stream << blowTemplateList.size();
    QMap<QString, BlowTemplateGraphics*>::const_iterator m = blowTemplateList.constBegin();
    while (m != blowTemplateList.constEnd()) {
        (*m)->serializeOut(stream);
        ++m;
    }

    // Store text
    stream << textMap.size();
    QMap<QString, TextGraphics*>::const_iterator n = textMap.constBegin();
    while (n != textMap.constEnd()) {
        (*n)->serializeOut(stream);
        ++n;
    }

    // Store text
    stream << scatterMap.size();
    QMap<QString, DispersionGraphics*>::const_iterator o = scatterMap.constBegin();
    while (o != scatterMap.constEnd()) {
        (*o)->serializeOut(stream);
        ++o;
    }
    QLog_Info(LOG_ID_INFO, "getGlobalInfo(): finished to gather game info");
}

void GameWindow::clearAllMaps()
{
    // clearing regiments
    QMap<QString, RegimentGraphics*>::const_iterator i = regimentMap.constBegin();
    while (i != regimentMap.constEnd()) {
        scene.removeItem(*i);
        i++;
    }

    // clearing rulers
    QMap<QString, RulerGraphics*>::const_iterator j = rulerList.constBegin();
    while (j != rulerList.constEnd()) {
        scene.removeItem(*j);
        ++j;
    }

    // clearing templates
    QMap<QString, RoundTemplateGraphics*>::const_iterator k = roundTemplateList.constBegin();
    while (k != roundTemplateList.constEnd()) {
        scene.removeItem(*k);
        ++k;
    }
    
    // clearing terrains
    QMap<QString, TerrainGraphics*>::const_iterator l = terrainMap.constBegin();
    while (l != terrainMap.constEnd()) {
        scene.removeItem(*l);
        ++l;
    }
    
    // clearing blow templates
    QMap<QString, BlowTemplateGraphics*>::const_iterator m = blowTemplateList.constBegin();
    while (m != blowTemplateList.constEnd()) {
        scene.removeItem(*m);
        ++m;
    }

    // Clearing text
    QMap<QString, TextGraphics*>::const_iterator n = textMap.constBegin();
    while (n != textMap.constEnd()) {
        scene.removeItem(*n);
        ++n;
    }

    // Clearing scatter
    QMap<QString, DispersionGraphics*>::const_iterator o = scatterMap.constBegin();
    while (o != scatterMap.constEnd()) {
        scene.removeItem(*o);
        ++o;
    }
    
    regimentMap.clear();
    rulerList.clear();
    roundTemplateList.clear();
    terrainMap.clear();
    blowTemplateList.clear();
    textMap.clear();
    scatterMap.clear();
    // TODO : verify if clear() deletes items
}

void GameWindow::setGlobalInfo(QDataStream& stream)
{
    clearAllMaps();
    int size;
    Game g;
    QString me;
    QString version;

    // get version
    stream >> version;

    QLog_Info(LOG_ID_INFO, "setGlobalInfo() version : " + version);

    if(version != WARHOLE_VERSION_STRING)
    {
        QMessageBox::warning(this, tr("Version"), tr("Attention : Votre version de Warhole (") +
                             WARHOLE_VERSION_STRING + tr(") est différente de la version du serveur (") +
                             version + tr("). Utiliser des versions différentes peut rendre le logiciel instable et provoquer des crashs."));
    }

    // Store game info
    stream >> g;

    // Load game info, but keep the Me value
    // TODO Find other way to handle this
    me = controller.getGame().getMe();
    controller.setGame(g);
    controller.getGamePtr()->setMe(me);

    // Store background and update it
    int b;
    stream >> b;
    updateBackground((BackGroundTypes)b);

    // Store regiments
    stream >> size;
    QLog_Info(LOG_ID_INFO, "setGlobalInfo() Storing " + QString::number(size) + " regiments");
    for(int i = 0; i < size; ++i)
    {
        RegimentGraphics* r = new RegimentGraphics();
        r->serializeIn(stream);
        if(r->getOwner() == controller.getGame().getMe()) r->setIsOwnedByMe(true);
        r->initModels();
        r->setInvertedView(&invertedView);
        regimentMap[r->getRegimentID()] = r;

        // TODO : put all this in a method so that code isn't duplicated
        connect(r, SIGNAL(regimentMoved(QString,QPointF,QTransform, qreal)), &controller, SIGNAL(regimentMoved(QString, QPointF, QTransform, qreal)));
        connect(r, SIGNAL(removeRegimentRequest(QString)), &controller, SIGNAL(removeRegimentRequest(QString)));
        connect(r, SIGNAL(removeDeadsRequest(QString, int)), &controller, SIGNAL(removeDeadsRequest(QString, int)));
        connect(r, SIGNAL(changeWidthRequest(QString, int)), &controller, SIGNAL(changeWidthRequest(QString, int)));
        connect(r, SIGNAL(addModelRequest(QString,int)), &controller, SIGNAL(addModelToRegRequest(QString, int)));
        connect(r, SIGNAL(changeRegimentInfoRequest(QString,RegimentAbstract)), &controller, SIGNAL(changeRegInfoRequest(QString, RegimentAbstract)));
        connect(r, SIGNAL(lineOfSightRequested(QString)), &controller, SIGNAL(showLineOfSightRequest(QString)));
        connect(r, SIGNAL(lineOfSightHideRequest(QString)), &controller, SIGNAL(hideLineOfSightRequest(QString)));

        scene.addItem(r);
    }

    // Store rulers
    stream >> size;
    QLog_Info(LOG_ID_INFO, "setGlobalInfo() Storing " + QString::number(size) + " rulers");
    for(int i = 0; i < size; ++i)
    {
        RulerGraphics* r = new RulerGraphics();
        r->serializeIn(stream);
        rulerList[r->getId()] = r;

        connect(r, SIGNAL(rulerMoved(QString, QPointF, QTransform, qreal)), &controller, SIGNAL(rulerMoved(QString, QPointF, QTransform, qreal)));
        connect(r, SIGNAL(removeRuler(QString)), &controller, SIGNAL(removeRulerRequest(QString)));
        scene.addItem(r);
    }

    // Store templates
    stream >> size;
    QLog_Info(LOG_ID_INFO, "setGlobalInfo() Storing " + QString::number(size) + " templates");
    for(int i = 0; i < size; ++i)
    {
        RoundTemplateGraphics* r = new RoundTemplateGraphics();
        r->serializeIn(stream);
        roundTemplateList[r->getId()] = r;

        connect(r, SIGNAL(templateMoved(QString,QPointF)), &controller, SIGNAL(templateMoved(QString, QPointF)));
        connect(r, SIGNAL(removeTemplateRequest(QString)), &controller, SIGNAL(removeTemplateRequest(QString)));
        scene.addItem(r);
    }
    
    // Store terrains
    stream >> size;
    QLog_Info(LOG_ID_INFO, "setGlobalInfo() Storing " + QString::number(size) + " terrains");
    for(int i = 0; i < size; ++i)
    {
        TerrainGraphics* t = new TerrainGraphics(&invertedView);
        t->serializeIn(stream);
        terrainMap[t->getId()] = t;

        connect(t, SIGNAL(removeTerrainRequest(QString)), &controller, SIGNAL(removeTerrainRequest(QString)));
        connect(t, SIGNAL(lockTerrainRequest(QString, bool)), &controller, SIGNAL(lockTerrainRequest(QString, bool)));
        connect(t, SIGNAL(terrainMoved(QString,QPointF,QTransform, qreal)), &controller, SIGNAL(terrainMoved(QString, QPointF, QTransform, qreal)));
    
        scene.addItem(t);
    }
    
    // Store blow template
    stream >> size;
    QLog_Info(LOG_ID_INFO, "setGlobalInfo() Storing " + QString::number(size) + " blow templates");
    for(int i = 0; i < size; ++i)
    {
        BlowTemplateGraphics* b = new BlowTemplateGraphics();
        b->serializeIn(stream);
        blowTemplateList[b->getId()] = b;

        connect(b, SIGNAL(removeTemplateRequest(QString)), &controller, SIGNAL(removeTemplateRequest(QString)));
        connect(b, SIGNAL(templateMoved(QString,QPointF,QTransform, qreal)), &controller, SIGNAL(blowTemplateMoved(QString,QPointF,QTransform, qreal)));
    
        scene.addItem(b);
    }

    // Store text
    stream >> size;
    QLog_Info(LOG_ID_INFO, "setGlobalInfo() Storing " + QString::number(size) + " texts");
    for(int i = 0; i < size; ++i)
    {
        TextGraphics* b = new TextGraphics();
        b->serializeIn(stream);
        textMap[b->getId()] = b;

        connect(b, SIGNAL(removeTextRequest(QString)), &controller, SIGNAL(removeTextRequest(QString)));
        connect(b, SIGNAL(textChanged(QString,QString,QPointF,QTransform, qreal)), &controller, SIGNAL(textChanged(QString,QString,QPointF,QTransform, qreal)));
        connect(b, SIGNAL(textDoubleClicked()), this, SLOT(editText()));
        scene.addItem(b);
    }

    // Store scatters
    stream >> size;
    QLog_Info(LOG_ID_INFO, "setGlobalInfo() Storing " + QString::number(size) + " scatters");
    for(int i = 0; i < size; ++i)
    {
        DispersionGraphics* b = new DispersionGraphics();
        b->serializeIn(stream);
        scatterMap[b->getId()] = b;

        connect(b, SIGNAL(scatterMoved(QString,QPointF)), &controller, SIGNAL(scatterMoved(QString, QPointF)));
        connect(b, SIGNAL(removeScatter(QString)), &controller, SIGNAL(removeScatterRequest(QString)));

        scene.addItem(b);
    }
}


void GameWindow::on_actionSave_Game_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Sauvegarde du fichier"), controller.getGame().getName() + ".war", tr("fichiers war(*.war)"));

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
             return;

    QDataStream stream(&file);

    getGlobalInfo(stream);

    emit newMessageToSend("<em><font color=\"DimGray\">" + tr("Partie sauvegardée.") + "</em></font>", false);
    file.close();
}

void GameWindow::on_actionCharger_une_partie_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Charger partie"), "", tr("Fichiers war (*.war)"));

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
             return;

    QDataStream stream(&file);

    setGlobalInfo(stream);

    // Send global info to all
    packGameDataForGlobalUpdate("");

    emit newMessageToSend("<em><font color=\"DimGray\">" + tr("Fichier de partie chargé : ") + path + "</em></font>", false);
    
    file.close();
}


void GameWindow::on_treeViewTerrains_customContextMenuRequested(const QPoint &pos)
{
    indexTerrain =ui->treeViewTerrains->indexAt(pos);

    if(indexTerrain.isValid())
    {
        QString name = indexTerrain.data().toString();
        QStringList pieces = name.split(".");
        if(pieces.last() == "ter")
        {
            currentSelectedTerrainPath = terrainsModel->filePath(indexTerrain);
            QMenu *menu=new QMenu(this);
            menu->addAction(placeTerrain);
            menu->popup(ui->treeViewTerrains->viewport()->mapToGlobal(pos));
        }
        else currentSelectedTerrainPath = "";
    }
}

void GameWindow::rotateView()
{
    view.changeSideView();
    invertedView = !invertedView;
}

void GameWindow::placeTerrainRequest()
{
    Terrain ter;
    ter.load(currentSelectedTerrainPath);

    emit requestNewTerrain(ter);
}

void GameWindow::addNewTerrainToScene(QString id, Terrain t)
{
    TerrainGraphics* ter = new TerrainGraphics(t, &invertedView);
    ter->setId(id);

    connect(ter, SIGNAL(removeTerrainRequest(QString)), &controller, SIGNAL(removeTerrainRequest(QString)));
    connect(ter, SIGNAL(lockTerrainRequest(QString, bool)), &controller, SIGNAL(lockTerrainRequest(QString, bool)));
    connect(ter, SIGNAL(terrainMoved(QString,QPointF,QTransform, qreal)), &controller, SIGNAL(terrainMoved(QString, QPointF, QTransform, qreal)));

    terrainMap[id] = ter;
    scene.addItem(ter);
    scene.clearSelection();
}

void GameWindow::removeTerrain(QString id)
{
    if(terrainMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "removeTerrain() : terrain with ID " + id +
                  " found, now removing it");
        TerrainGraphics* t = terrainMap[id];
        scene.removeItem(t);
        delete t;
        terrainMap.remove(id);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "removeTerrain() : terrain with ID " + id + " not found in map.");
    }
}

void GameWindow::lockTerrain(QString id, bool l)
{
    if(terrainMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "lockTerrain() : terrain with ID " + id +
                  " found, now locking it");
        terrainMap[id]->setLock(l);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "removeTerrain() : terrain with ID " + id + " not found in map.");
    }
}

void GameWindow::moveTerrain(QString id, QPointF p, QTransform matrix, qreal pr)
{
    if(terrainMap.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "moveTerrain() : terrain with ID " + id +
                  " found, now moving it");
        terrainMap[id]->setPos(p);
        terrainMap[id]->setTransform(matrix);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "moveTerrain() : terrain with ID " + id + " not found in map.");
    }
}

void GameWindow::addNewBlowTemplateToScene(QString id)
{
    BlowTemplateGraphics* b = new BlowTemplateGraphics(id);
    QLog_Info(LOG_ID_INFO, "addNewBlowTemplateToScene(): adding blow template to list with ID " + id);

    connect(b, SIGNAL(removeTemplateRequest(QString)), &controller, SIGNAL(removeBlowTemplateRequest(QString)));
    connect(b, SIGNAL(templateMoved(QString,QPointF,QTransform, qreal)), &controller, SIGNAL(blowTemplateMoved(QString, QPointF, QTransform, qreal)));

    blowTemplateList[id] = b;
    b->setPos(back->getW()/2, back->getH()/2);
    scene.addItem(b);
    scene.clearSelection();
}

void GameWindow::moveBlowTemplate(QString id, QPointF p, QTransform matrix, qreal pr)
{
    if(blowTemplateList.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "moveBlowTemplate() : blow template with ID " + id +
                  " found, now moving it");
        blowTemplateList[id]->setPos(p);
        blowTemplateList[id]->setTransform(matrix);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "moveBlowTemplate() : blow template with ID " + id + " not found in map.");
    }
}

void GameWindow::removeBlowTemplate(QString id)
{
    if(blowTemplateList.contains(id))
    {
        QLog_Info(LOG_ID_INFO, "removeBlowTemplate() : blow template with ID " + id +
                  " found, now removing it");
        BlowTemplateGraphics* t = blowTemplateList[id];
        scene.removeItem(t);
        delete t;
        blowTemplateList.remove(id);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "removeBlowTemplate() : blow template with ID " + id + " not found in map.");
    }
}

void GameWindow::editText()
{
    bool ok;
    QString text;
    TextGraphics* t = qobject_cast<TextGraphics*>(sender());
    text = QInputDialog::getText(this, tr("Changer le texte"),
                                  tr("Texte :"), QLineEdit::Normal,
                                 t->getText(), &ok);
    if(ok)
    {
        t->setText(text);
    }
}

void GameWindow::addNewTextToScene(QString id, QString text)
{
    TextGraphics* b = new TextGraphics();
    b->setTextWithoutSignal(text);
    b->setId(id);
    QLog_Info(LOG_ID_INFO, "addNewTextToScene(): adding text to list with ID " + id);

    connect(b, SIGNAL(removeTextRequest(QString)), &controller, SIGNAL(removeTextRequest(QString)));
    connect(b, SIGNAL(textChanged(QString,QString,QPointF,QTransform, qreal)), &controller, SIGNAL(textChanged(QString, QString, QPointF, QTransform, qreal)));
    connect(b, SIGNAL(textDoubleClicked()), this, SLOT(editText()));

    textMap[id] = b;
    b->setPos(back->getW()/2, back->getH()/2);
    scene.addItem(b);
    scene.clearSelection();
}

void GameWindow::moveText(QString i, QString text, QPointF p, QTransform matrix, qreal pr)
{
    if(textMap.contains(i))
    {
        QLog_Info(LOG_ID_INFO, "moveText() : text with ID " + i +
                  " found, now moving it");
        TextGraphics* t = textMap[i];
        t->setPos(p);
        t->setTransform(matrix);
        t->setTextWithoutSignal(text);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "moveText() : text with ID " + i + " not found in map.");
    }
}

void GameWindow::removeText(QString i)
{
    if(textMap.contains(i))
    {
        QLog_Info(LOG_ID_INFO, "removeText() : text with ID " + i +
                  " found, now removing it");
        TextGraphics* t = textMap[i];
        scene.removeItem(t);
        delete t;
        textMap.remove(i);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "removeText() : text with ID " + i + " not found in map.");
    }
}

void GameWindow::requestNewScatter()
{
    emit newMessageToSend("<em><font color=\"DimGray\">" + tr("Lance un dé de dispersion.") + "</em></font>", false);
    int angle = DiceRoller::getDispersion();
    emit requestNewScatter(angle);
}

void GameWindow::addNewScatterToScene(QString i, int a)
{
    DispersionGraphics* d = new DispersionGraphics(i, a);

    connect(d, SIGNAL(scatterMoved(QString,QPointF)), &controller, SIGNAL(scatterMoved(QString, QPointF)));
    connect(d, SIGNAL(removeScatter(QString)), &controller, SIGNAL(removeScatterRequest(QString)));

    scatterMap[i] = d;
    d->setPos(back->getW()/2, back->getH()/2);
    scene.addItem(d);
    scene.clearSelection();
}

void GameWindow::requestNewText()
{
    bool ok;
    QString text;
    text = QInputDialog::getText(this, tr("Entrez votre texte"),
                                  tr("Texte :"), QLineEdit::Normal,
                                 "", &ok);
    if(ok)
    {
        emit requestNewText(text);
    }
}

void GameWindow::moveScatter(QString i, QPointF p)
{
    if(scatterMap.contains(i))
    {
        QLog_Info(LOG_ID_INFO, "moveScatter() : scatter with ID " + i +
                  " found, now moving it");
        DispersionGraphics* t = scatterMap[i];
        t->setPos(p);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "moveScatter() : scatter with ID " + i + " not found in map.");
    }
}

void GameWindow::removeScatter(QString i)
{
    if(scatterMap.contains(i))
    {
        QLog_Info(LOG_ID_INFO, "removeText() : Scatter with ID " + i +
                  " found, now removing it");
        DispersionGraphics* t = scatterMap[i];
        scene.removeItem(t);
        delete t;
        scatterMap.remove(i);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "removeScatter() : scatter with ID " + i + " not found in map.");
    }
}

void GameWindow::changeBackground(int b)
{
    updateBackground((BackGroundTypes)b);
}

void GameWindow::on_actionWiki_Warhole_triggered()
{
    QDesktopServices::openUrl(WARHOLE_WIKI_URL);
}

void GameWindow::on_actionA_propos_triggered()
{
    WarholeInfoDialog* inf = new WarholeInfoDialog();
    inf = new WarholeInfoDialog();
    inf->show();
}

void GameWindow::refreshNetworkState(bool s)
{
    networkOn = s;
}

void GameWindow::updateBackground(BackGroundTypes b)
{
    QString path;

    // update type value
    backType = b;

    switch(b)
    {
    case GRASS:
        path = ":/tile/ressources/tiles/grass.png";
        break;
    case DIRT:
        path = ":/tile/ressources/tiles/dirt.jpg";
        break;
    case SAND:
        path = ":/tile/ressources/tiles/sand.jpg";
        break;
    case SNOW:
        path = ":/tile/ressources/tiles/snow.jpg";
        break;
    case ROCK:
        path = ":/tile/ressources/tiles/rock.jpg";
        break;
    default:
        break;
    }

    if(!background.load(path))
    {
        QLog_Error(LOG_ID_ERR, "GAMEWINDOW : Can't load background image");
    }

    if(backGroundBrush) delete backGroundBrush;
    backGroundBrush = new QBrush(background);
    scene.setBackgroundBrush(*backGroundBrush);
}

void GameWindow::addChatMessageToList(QString sender, QString msg)
{
    QString s;
    QTextStream stream(&s);
    stream << "<strong>" << sender << " : </strong>" << msg;

    chatMessageList.append(s);
}
