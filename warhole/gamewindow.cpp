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

    // Actions load and save game
    ui->actionCharger_une_partie->setEnabled(false);
    ui->actionSave_Game->setEnabled(false);
    connect(&controller, SIGNAL(networkEnabled(bool)), ui->actionCharger_une_partie, SLOT(setEnabled(bool)));
    connect(&controller, SIGNAL(networkEnabled(bool)), ui->actionSave_Game, SLOT(setEnabled(bool)));

    // Chat widget
    cw = new ChatWidgetForm(this);
    ui->dockWidget_2->setWidget(cw);
    connect(cw, SIGNAL(newMessageToSend(QString)), &controller, SIGNAL(newChatMessageToSend(QString)));
    connect(&controller, SIGNAL(newChatMessageToPrint(QString,QString)), cw, SLOT(printNewChatMessage(QString,QString)));

    tabifyDockWidget(ui->dockWidget, ui->dockWidget_5);

    // Terrain
    terrainsModel = new QFileSystemModel(this);
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
    connect(&controller, SIGNAL(removeTemplate(QString)), this, SLOT(removeRoundTemplate(QString)));

    connect(this, SIGNAL(requestNewRoundTemplate(int)), &controller, SIGNAL(addRoundTemplateToGameSceneRequest(int)));
    connect(&controller, SIGNAL(addRoundTemplateScene(QString,int)), this, SLOT(addRoundTemplateToScene(QString, int)));

    connect(ui->actionPivoter_la_vue, SIGNAL(triggered()), this, SLOT(rotateView()));

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
    connect(&controller, SIGNAL(moveRegiment(QString,QPointF,QTransform)), this, SLOT(moveRegiment(QString, QPointF, QTransform)));

    connect(&controller, SIGNAL(removeRegiment(QString)), this, SLOT(removeRegiment(QString)));
    connect(&controller, SIGNAL(removeDeads(QString,int)), this, SLOT(removeDeadsFromRegiment(QString, int)));
    connect(&controller, SIGNAL(changeRegimentWidth(QString,int)), this, SLOT(changeRegimentWidth(QString, int)));
    connect(&controller, SIGNAL(addModels(QString,int)), this, SLOT(addModelToRegiment(QString, int)));
    connect(&controller, SIGNAL(changeRegInfo(QString,RegimentAbstract)), this, SLOT(changeRegInfo(QString, RegimentAbstract)));

    connect(&controller, SIGNAL(serverInfoRequested(QString)), this, SLOT(packGameDataForGlobalUpdate(QString)));
    connect(this, SIGNAL(sendGlobalInfoUpdate(QString,QByteArray)), &controller, SIGNAL(sendGlobalInfoUpdate(QString, QByteArray)));
    connect(&controller, SIGNAL(loadGlobalInfoUpdate(QByteArray)), this, SLOT(loadGlobalInfoUpdate(QByteArray)));

    connect(this, SIGNAL(requestNewTerrain(Terrain)), &controller, SIGNAL(requestNewTerrain(Terrain)));
    connect(&controller, SIGNAL(newTerrain(QString, Terrain)), this, SLOT(addNewTerrainToScene(QString, Terrain)));
    connect(&controller, SIGNAL(removeTerrain(QString)), this, SLOT(removeTerrain(QString)));
    connect(&controller, SIGNAL(lockTerrain(QString, bool)), this, SLOT(lockTerrain(QString, bool)));
    connect(&controller, SIGNAL(moveTerrain(QString,QPointF,QTransform)), SLOT(moveTerrain(QString, QPointF, QTransform)));

    connect(&controller, SIGNAL(newBlowTemp(QString)), this, SLOT(addNewBlowTemplateToScene(QString)));
    connect(&controller, SIGNAL(moveBlowTemp(QString,QPointF,QTransform)), this, SLOT(moveBlowTemplate(QString,QPointF,QTransform)));
    connect(&controller, SIGNAL(removeBlowTemp(QString)), this, SLOT(removeBlowTemplate(QString)));

    connect(ui->actionBlowTemplate, SIGNAL(triggered()), &controller, SIGNAL(requestBlowTemplate()));
    connect(ui->actionActionAddText, SIGNAL(triggered()), this, SLOT(requestNewText()));
    connect(this, SIGNAL(requestNewText(QString)), &controller, SIGNAL(newTextRequest(QString)));
    connect(&controller, SIGNAL(newText(QString, QString)), this, SLOT(addNewTextToScene(QString, QString)));
    connect(&controller, SIGNAL(moveText(QString,QString,QPointF,QTransform)), this, SLOT(moveText(QString, QString, QPointF, QTransform)));
    connect(&controller, SIGNAL(removeText(QString)), this, SLOT(removeText(QString)));
}


GameWindow::~GameWindow()
{
    delete ui;
    delete back;
    armyModel->deleteLater();
    actionDeploy->deleteLater();
    placeTerrain->deleteLater();
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


        connect(rg, SIGNAL(regimentMoved(QString,QPointF,QTransform)), &controller, SIGNAL(regimentMoved(QString, QPointF, QTransform)));
        connect(rg, SIGNAL(removeRegimentRequest(QString)), &controller, SIGNAL(removeRegimentRequest(QString)));
        connect(rg, SIGNAL(removeDeadsRequest(QString, int)), &controller, SIGNAL(removeDeadsRequest(QString, int)));
        connect(rg, SIGNAL(changeWidthRequest(QString, int)), &controller, SIGNAL(changeWidthRequest(QString, int)));
        connect(rg, SIGNAL(addModelRequest(QString,int)), &controller, SIGNAL(addModelToRegRequest(QString, int)));
        connect(rg, SIGNAL(changeRegimentInfoRequest(QString,RegimentAbstract)), &controller, SIGNAL(changeRegInfoRequest(QString, RegimentAbstract)));

        scene.addItem(rg);
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

void GameWindow::addRulerToScene(QString id, int l)
{
    RulerGraphics* r = new RulerGraphics(l, id);
    connect(r, SIGNAL(rulerMoved(QString, QPointF, QTransform)), &controller, SIGNAL(rulerMoved(QString, QPointF, QTransform)));
    connect(r, SIGNAL(removeRuler(QString)), &controller, SIGNAL(removeRulerRequest(QString)));
    scene.addItem(r);
    r->setPos(back->getW()/2, back->getH()/2);

    // Assume that id will be unique for now
    rulerList[id] = r;
}

void GameWindow::moveRuler(QString id, QPointF p, QTransform matrix)
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

void GameWindow::moveRegiment(QString id, QPointF p, QTransform matrix)
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
        emit cw->newMessageToSend("<em><font color=\"DimGray\">" + tr("Régiment ") +
                                  regimentMap[id]->getRegiment().getName() + tr(" se reforme, sa largeur passe à ") +
                                  QString::number(regimentMap[id]->getRegimentWidth()) + "</em></font>");
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

void GameWindow::packGameDataForGlobalUpdate(QString sender)
{
    QByteArray data;

    QDataStream stream(&data, QIODevice::WriteOnly);

    getGlobalInfo(stream);

    emit sendGlobalInfoUpdate(sender, data);
}

void GameWindow::loadGlobalInfoUpdate(QByteArray info)
{
    QDataStream stream(info);

    setGlobalInfo(stream);
}

void GameWindow::openArmyMenuClicked()
{
    loadArmy();
    emit cw->newMessageToSend("<em><font color=\"DimGray\">" +
                              tr("Armée chargée : ") +
                              army.getName() + " " +
                              QString::number(army.computePoints()) +
                              tr(" points") +  "</em></font>");
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
    // Store game info
    stream << controller.getGame();

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
    
    regimentMap.clear();
    rulerList.clear();
    roundTemplateList.clear();
    terrainMap.clear();
    blowTemplateList.clear();
    textMap.clear();
    // TODO : verify if clear() deletes items
}

void GameWindow::setGlobalInfo(QDataStream& stream)
{
    clearAllMaps();
    int size;
    Game g;
    QString me;

    // Store game info
    stream >> g;

    // Load game info, but keep the Me value
    // TODO Find other way to handle this
    me = controller.getGame().getMe();
    controller.setGame(g);
    controller.getGamePtr()->setMe(me);

    // Store regiments
    stream >> size;
    for(int i = 0; i < size; ++i)
    {
        RegimentGraphics* r = new RegimentGraphics();
        r->serializeIn(stream);
        if(r->getOwner() == controller.getGame().getMe()) r->setIsOwnedByMe(true);
        r->initModels();
        regimentMap[r->getRegimentID()] = r;

        connect(r, SIGNAL(regimentMoved(QString,QPointF,QTransform)), &controller, SIGNAL(regimentMoved(QString, QPointF, QTransform)));
        connect(r, SIGNAL(removeRegimentRequest(QString)), &controller, SIGNAL(removeRegimentRequest(QString)));
        connect(r, SIGNAL(removeDeadsRequest(QString, int)), &controller, SIGNAL(removeDeadsRequest(QString, int)));
        connect(r, SIGNAL(changeWidthRequest(QString, int)), &controller, SIGNAL(changeWidthRequest(QString, int)));
        connect(r, SIGNAL(addModelRequest(QString,int)), &controller, SIGNAL(addModelToRegRequest(QString, int)));
        connect(r, SIGNAL(changeRegimentInfoRequest(QString,RegimentAbstract)), &controller, SIGNAL(changeRegInfoRequest(QString, RegimentAbstract)));

        scene.addItem(r);
    }

    // Store rulers
    stream >> size;
    for(int i = 0; i < size; ++i)
    {
        RulerGraphics* r = new RulerGraphics();
        r->serializeIn(stream);
        rulerList[r->getId()] = r;

        connect(r, SIGNAL(rulerMoved(QString, QPointF, QTransform)), &controller, SIGNAL(rulerMoved(QString, QPointF, QTransform)));
        connect(r, SIGNAL(removeRuler(QString)), &controller, SIGNAL(removeRulerRequest(QString)));
        scene.addItem(r);
    }

    // Store templates
    stream >> size;
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
    for(int i = 0; i < size; ++i)
    {
        TerrainGraphics* t = new TerrainGraphics();
        t->serializeIn(stream);
        terrainMap[t->getId()] = t;

        connect(t, SIGNAL(removeTerrainRequest(QString)), &controller, SIGNAL(removeTerrainRequest(QString)));
        connect(t, SIGNAL(lockTerrainRequest(QString, bool)), &controller, SIGNAL(lockTerrainRequest(QString, bool)));
        connect(t, SIGNAL(terrainMoved(QString,QPointF,QTransform)), &controller, SIGNAL(terrainMoved(QString, QPointF, QTransform)));
    
        scene.addItem(t);
    }
    
    // Store blow template
    stream >> size;
    for(int i = 0; i < size; ++i)
    {
        BlowTemplateGraphics* b = new BlowTemplateGraphics();
        b->serializeIn(stream);
        blowTemplateList[b->getId()] = b;

        connect(b, SIGNAL(removeTemplateRequest(QString)), &controller, SIGNAL(removeTemplateRequest(QString)));
        connect(b, SIGNAL(templateMoved(QString,QPointF,QTransform)), &controller, SIGNAL(blowTemplateMoved(QString,QPointF,QTransform)));
    
        scene.addItem(b);
    }

    // Store text
    stream >> size;
    for(int i = 0; i < size; ++i)
    {
        TextGraphics* b = new TextGraphics();
        b->serializeIn(stream);
        textMap[b->getId()] = b;

        connect(b, SIGNAL(removeTextRequest(QString)), &controller, SIGNAL(removeTextRequest(QString)));
        connect(b, SIGNAL(textChanged(QString,QString,QPointF,QTransform)), &controller, SIGNAL(textChanged(QString,QString,QPointF,QTransform)));
        connect(b, SIGNAL(textDoubleClicked()), this, SLOT(editText()));
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

    emit cw->newMessageToSend("<em><font color=\"DimGray\">" + tr("Partie sauvegardée.") + "</em></font>");
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

    emit cw->newMessageToSend("<em><font color=\"DimGray\">" + tr("Fichier de partie chargé : ") + path + "</em></font>");
    
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
}

void GameWindow::placeTerrainRequest()
{
    Terrain ter;
    ter.load(currentSelectedTerrainPath);

    emit requestNewTerrain(ter);
}

void GameWindow::addNewTerrainToScene(QString id, Terrain t)
{
    TerrainGraphics* ter = new TerrainGraphics(t);
    ter->setId(id);

    connect(ter, SIGNAL(removeTerrainRequest(QString)), &controller, SIGNAL(removeTerrainRequest(QString)));
    connect(ter, SIGNAL(lockTerrainRequest(QString, bool)), &controller, SIGNAL(lockTerrainRequest(QString, bool)));
    connect(ter, SIGNAL(terrainMoved(QString,QPointF,QTransform)), &controller, SIGNAL(terrainMoved(QString, QPointF, QTransform)));

    terrainMap[id] = ter;
    scene.addItem(ter);
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

void GameWindow::moveTerrain(QString id, QPointF p, QTransform matrix)
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
    connect(b, SIGNAL(templateMoved(QString,QPointF,QTransform)), &controller, SIGNAL(blowTemplateMoved(QString, QPointF, QTransform)));

    blowTemplateList[id] = b;
    scene.addItem(b);
}

void GameWindow::moveBlowTemplate(QString id, QPointF p, QTransform matrix)
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
    connect(b, SIGNAL(textChanged(QString,QString,QPointF,QTransform)), &controller, SIGNAL(textChanged(QString, QString, QPointF, QTransform)));
    connect(b, SIGNAL(textDoubleClicked()), this, SLOT(editText()));

    textMap[id] = b;
    scene.addItem(b);
}

void GameWindow::moveText(QString i, QString text, QPointF p, QTransform matrix)
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
        QLog_Info(LOG_ID_INFO, "removeText() : blow template with ID " + i +
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

