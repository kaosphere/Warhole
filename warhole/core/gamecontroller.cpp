#include "gamecontroller.h"

GameController::GameController(QObject *parent) :
    QObject(parent)
{
    ///////////////////////////////////////////
    // Network interface
    ///////////////////////////////////////////
    netInterface = NULL;
    network = false;

    ///////////////////////////////////////////
    // Command manager
    ///////////////////////////////////////////
    comManager = new CommandManager(&inQueue, &outQueue, &game, this);
    connect(comManager, SIGNAL(newChatMessageAvailable(QString, QString)), this, SIGNAL(newChatMessageToPrint(QString,QString)));
    connect(this, SIGNAL(newChatMessageToSend(QString, bool, QString)), comManager, SLOT(enQueueChatMessage(QString, bool, QString)));

    connect(this, SIGNAL(addRulerToGameSceneRequest(int)), comManager, SLOT(enQueueCreateRulerMessage(int)));
    connect(comManager, SIGNAL(createRuler(QString, int)), this, SIGNAL(addRulerToGameScene(QString, int)));

    connect(this, SIGNAL(rulerMoved(QString, QPointF, QTransform, qreal)), comManager, SLOT(enQueueRulerMoveMessage(QString, QPointF, QTransform, qreal)));
    connect(comManager, SIGNAL(moveRuler(QString, QPointF, QTransform, qreal)), this, SIGNAL(moveRuler(QString, QPointF, QTransform, qreal)));

    connect(this, SIGNAL(addRoundTemplateToGameSceneRequest(int)), comManager, SLOT(enqueueCreateRoundTemplateMessage(int)));
    connect(comManager, SIGNAL(createRoundTemplate(QString,int)), this, SIGNAL(addRoundTemplateScene(QString, int)));

    connect(this, SIGNAL(templateMoved(QString,QPointF)), comManager, SLOT(enQueueTemplateMoveMessage(QString, QPointF)));
    connect(comManager, SIGNAL(moveTemplate(QString,QPointF)), this, SIGNAL(moveTemplate(QString,QPointF)));

    connect(this, SIGNAL(removeRulerRequest(QString)), comManager, SLOT(enQueueRemoveRulerMessage(QString)));
    connect(comManager, SIGNAL(removeRuler(QString)), this, SIGNAL(removeRuler(QString)));

    connect(this, SIGNAL(removeTemplateRequest(QString)), comManager, SLOT(enQueueRemoveTemplateMessage(QString)));
    connect(comManager, SIGNAL(removeTemplate(QString)), this, SIGNAL(removeTemplate(QString)));

    connect(this, SIGNAL(addRegimentRequest(QString, RegimentAbstract)), comManager,SLOT(enqueueNewRegimentMessage(QString, RegimentAbstract)));
    connect(comManager, SIGNAL(createRegiment(QString,QString,RegimentAbstract)), this, SIGNAL(createRegiment(QString, QString, RegimentAbstract)));

    connect(this, SIGNAL(regimentMoved(QString,QPointF,QTransform, qreal)), comManager, SLOT(enqueueRegimentMoveMessage(QString, QPointF, QTransform, qreal)));
    connect(comManager, SIGNAL(moveRegiment(QString,QPointF,QTransform, qreal)), this, SIGNAL(moveRegiment(QString, QPointF, QTransform, qreal)));

    connect(this, SIGNAL(removeRegimentRequest(QString)), comManager, SLOT(enqueueRemoveRegimentMessage(QString)));
    connect(this, SIGNAL(removeDeadsRequest(QString, int)), comManager, SLOT(enqueueRemoveDeadsMessage(QString, int)));
    connect(this, SIGNAL(changeWidthRequest(QString, int)), comManager, SLOT(enqueueChangeWidthMessage(QString, int)));
    connect(this, SIGNAL(addModelToRegRequest(QString,int)), comManager, SLOT(enqueueAddModelMessage(QString, int)));
    connect(this, SIGNAL(changeRegInfoRequest(QString,RegimentAbstract)), comManager, SLOT(enqueueChangeRegInfoMessage(QString, RegimentAbstract)));
    connect(this, SIGNAL(showLineOfSightRequest(QString)), comManager, SLOT(enqueueShowLineOfSightMessage(QString)));
    connect(this, SIGNAL(hideLineOfSightRequest(QString)), comManager, SLOT(enqueueHideLineOfSightMessage(QString)));
    connect(comManager, SIGNAL(removeRegiment(QString)), this, SIGNAL(removeRegiment(QString)));
    connect(comManager, SIGNAL(removeDeads(QString,int)), this, SIGNAL(removeDeads(QString, int)));
    connect(comManager, SIGNAL(changeRegimentWidth(QString,int)), this, SIGNAL(changeRegimentWidth(QString, int)));
    connect(comManager, SIGNAL(addModels(QString,int)), this, SIGNAL(addModels(QString, int)));
    connect(comManager, SIGNAL(changeRegInfo(QString,RegimentAbstract)), this, SIGNAL(changeRegInfo(QString, RegimentAbstract)));
    connect(comManager, SIGNAL(showLineOfSight(QString)), this, SIGNAL(showLineOfSight(QString)));
    connect(comManager, SIGNAL(hideLineOfSight(QString)), this, SIGNAL(hideLineOfSight(QString)));

    connect(comManager, SIGNAL(serverInfoRequested(QString)), this, SIGNAL(serverInfoRequested(QString)));
    connect(this, SIGNAL(sendGlobalInfoUpdate(QString, QByteArray)), comManager, SLOT(enQueueServerInfo(QString, QByteArray)));
    connect(comManager, SIGNAL(loadGlobalInfoUpdate(QByteArray)), this, SIGNAL(loadGlobalInfoUpdate(QByteArray)));

    connect(this, SIGNAL(requestNewTerrain(Terrain)), comManager, SLOT(enQueueNewTerrainMessage(Terrain)));
    connect(comManager, SIGNAL(newTerrain(QString, Terrain)), this, SIGNAL(newTerrain(QString, Terrain)));
    connect(this, SIGNAL(removeTerrainRequest(QString)), comManager, SLOT(enQueueRemoveTerrainMessage(QString)));
    connect(this, SIGNAL(lockTerrainRequest(QString, bool)), comManager, SLOT(enQueueLockTerrainMessage(QString, bool)));
    connect(this, SIGNAL(terrainMoved(QString,QPointF,QTransform, qreal)), comManager, SLOT(enQueueMoveTerrainMessage(QString, QPointF, QTransform, qreal)));
    connect(comManager, SIGNAL(removeTerrain(QString)), this, SIGNAL(removeTerrain(QString)));
    connect(comManager, SIGNAL(lockTerrain(QString, bool)), this, SIGNAL(lockTerrain(QString, bool)));
    connect(comManager, SIGNAL(moveTerrain(QString,QPointF,QTransform, qreal)), this, SIGNAL(moveTerrain(QString,QPointF,QTransform, qreal)));

    connect(this, SIGNAL(requestBlowTemplate()), comManager, SLOT(enQueueNewBlowTemplateMessage()));
    connect(this, SIGNAL(blowTemplateMoved(QString,QPointF,QTransform, qreal)), comManager, SLOT(enQueueBlowTemplateMoveMessage(QString, QPointF, QTransform, qreal)));
    connect(this, SIGNAL(removeBlowTemplateRequest(QString)), comManager, SLOT(enQueueRemoveBlowTemplateMessage(QString)));
    connect(comManager, SIGNAL(newBlowTemp(QString)), this, SIGNAL(newBlowTemp(QString)));
    connect(comManager, SIGNAL(moveBlowTemp(QString, QPointF, QTransform, qreal)), this, SIGNAL(moveBlowTemp(QString, QPointF, QTransform, qreal)));
    connect(comManager, SIGNAL(removeBlowTemp(QString)), this, SIGNAL(removeBlowTemp(QString)));

    connect(this, SIGNAL(newTextRequest(QString)), comManager, SLOT(enQueueNewTextMessage(QString)));
    connect(this, SIGNAL(removeTextRequest(QString)), comManager, SLOT(enQueueRemoveTextMessage(QString)));
    connect(this, SIGNAL(textChanged(QString,QString,QPointF,QTransform, qreal)), comManager, SLOT(enQueueTextChangeMessage(QString, QString, QPointF, QTransform, qreal)));
    connect(comManager, SIGNAL(newText(QString,QString)), this, SIGNAL(newText(QString, QString)));
    connect(comManager, SIGNAL(moveText(QString,QString,QPointF,QTransform, qreal)), this, SIGNAL(moveText(QString, QString, QPointF, QTransform, qreal)));
    connect(comManager, SIGNAL(removeText(QString)), this, SIGNAL(removeText(QString)));

    connect(this, SIGNAL(requestNewScatter(int)), comManager, SLOT(enQueueNewScatterMessage(int)));
    connect(this, SIGNAL(removeScatterRequest(QString)), comManager, SLOT(enQueueRemoveScatterMessage(QString)));
    connect(this, SIGNAL(scatterMoved(QString,QPointF)), comManager, SLOT(enQueueScatterMoveMessage(QString, QPointF)));
    connect(comManager, SIGNAL(newScatter(QString,int)), this, SIGNAL(newScatter(QString, int)));
    connect(comManager, SIGNAL(moveScatter(QString,QPointF)), this, SIGNAL(moveScatter(QString, QPointF)));
    connect(comManager, SIGNAL(removeScatter(QString)), this, SIGNAL(removeScatter(QString)));

    connect(this, SIGNAL(requestBackgroundChange(int)), comManager, SLOT(enqueueBackgroundChangeMessage(int)));
    connect(comManager, SIGNAL(changeBackground(int)), this, SIGNAL(changeBackground(int)));

    ///////////////////////////////////////////
    // Player Administrator
    ///////////////////////////////////////////
    connect(&playerAdmin, SIGNAL(playerListChanged(QList<Player>)), comManager, SLOT(enQueuePlayerListRefreshMessage(QList<Player>)));
    connect(comManager, SIGNAL(refreshPlayerList(QList<Player>)), this, SIGNAL(refreshPlayerListDisplay(QList<Player>)));
    connect(&playerAdmin, SIGNAL(playerNameToChange(QString,QString)), comManager, SLOT(enqueuePlayerNameChangeRequest(QString, QString)));
    connect(comManager, SIGNAL(playerNameChange(QString)), this, SLOT(changeMyName(QString)));
}

GameController::~GameController()
{
    comManager->deleteLater();
    netInterface->deleteLater();
    networkThread.quit();
}

void GameController::createNetworkInterface(NetworkType t, QString ip)
{
    switch(t)
    {
    case SERVER:
        // Register Client as a metatype, to enable object passing through signals of different threads
        qRegisterMetaType<Client>();
        netInterface = new NetworkServer(&inQueue, &outQueue);
        netInterface->moveToThread(&networkThread);
        connect(netInterface, SIGNAL(newPlayerConnected(Client)), &playerAdmin, SLOT(handleNewPlayerConnection(Client)));
        connect(netInterface, SIGNAL(playerDisconnected(Client)), &playerAdmin, SLOT(handlePlayerDisconnection(Client)));
        connect(&playerAdmin, SIGNAL(playerListChanged(QList<Player>)), SIGNAL(refreshPlayerListDisplay(QList<Player>)));
        connect(comManager, SIGNAL(changeClientName(QString,QString)), dynamic_cast<NetworkServer*>(netInterface), SLOT(changeClientName(QString, QString)));
        // Add server to the player list
        playerAdmin.authorizePlayer(Player(game.getMe(), "127.0.0.1", true));
        setNetwork();
        break;
    case CLIENT:
        netInterface = new NetworkClient(&inQueue, &outQueue, ip);
        netInterface->moveToThread(&networkThread);
        connect(netInterface, SIGNAL(firstConnectionToServer()), comManager, SLOT(enQueueServerInfoRequest()));
        connect(netInterface, SIGNAL(firstConnectionToServer()), this, SLOT(setNetwork()));
        connect(netInterface, SIGNAL(disconnected()), this, SLOT(clearNetwork()));
        break;
    default:
        //TODO error
        break;
    }

    // TODO handle this more cleanly
    //connect(netInterface, SIGNAL(stateChanged(QString)),comManager, SIGNAL(newChatMessageToPrint(QString,QString)));
    connect(&outQueue, SIGNAL(newMessageAvailable()), netInterface, SLOT(send()));
    connect(netInterface, SIGNAL(networkEvent(QString)), this, SIGNAL(networkEvent(QString)));

    // Move network interface to network thread so that all networking doesn't impact UI rendering
    networkThread.start();

    //printNetworkState(netInterface->getState());
}

void GameController::disconnectNetworkInterface()
{
    if(netInterface)
        netInterface->disconnection();
}

Game GameController::getGame() const
{
    return game;
}

Game* GameController::getGamePtr()
{
    return &game;
}

void GameController::setGame(const Game &value)
{
    game = value;
}

bool GameController::networkActive()
{
    return network;
}

void GameController::setNetwork()
{
    network = true;
    emit networkEnabled(network);
}

void GameController::clearNetwork()
{
    network = false;
    emit networkEnabled(network);
}

void GameController::changeMyName(QString n)
{
    game.setMe(n);
}
