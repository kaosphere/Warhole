#include "gamecontroller.h"

GameController::GameController(QObject *parent) :
    QObject(parent)
{
    ///////////////////////////////////////////
    // Network interface
    ///////////////////////////////////////////
    netInterface = NULL;

    ///////////////////////////////////////////
    // Command manager
    ///////////////////////////////////////////
    comManager = new CommandManager(&inQueue, &outQueue, &game, this);
    connect(comManager, SIGNAL(newChatMessageAvailable(QString, QString)), this, SIGNAL(newChatMessageToPrint(QString,QString)));
    connect(this, SIGNAL(newChatMessageToSend(QString)), comManager, SLOT(enQueueChatMessage(QString)));

    connect(this, SIGNAL(addRulerToGameSceneRequest(int)), comManager, SLOT(enQueueCreateRulerMessage(int)));
    connect(comManager, SIGNAL(createRuler(QString, int)), this, SIGNAL(addRulerToGameScene(QString, int)));

    connect(this, SIGNAL(rulerMoved(QString, QPointF, QTransform)), comManager, SLOT(enQueueRulerMoveMessage(QString, QPointF, QTransform)));
    connect(comManager, SIGNAL(moveRuler(QString, QPointF, QTransform)), this, SIGNAL(moveRuler(QString, QPointF, QTransform)));

    connect(this, SIGNAL(addRoundTemplateToGameSceneRequest(int)), comManager, SLOT(enqueueCreateRoundTemplateMessage(int)));
    connect(comManager, SIGNAL(createRoundTemplate(QString,int)), this, SIGNAL(addRoundTemplateScene(QString, int)));

    connect(this, SIGNAL(templateMoved(QString,QPointF)), comManager, SLOT(enQueueTemplateMoveMessage(QString, QPointF)));
    connect(comManager, SIGNAL(moveTemplate(QString,QPointF)), this, SIGNAL(moveTemplate(QString,QPointF)));

    connect(this, SIGNAL(removeRulerRequest(QString)), comManager, SLOT(enQueueRemoveRulerMessage(QString)));
    connect(comManager, SIGNAL(removeRuler(QString)), this, SIGNAL(removeRuler(QString)));

    connect(this, SIGNAL(removeTemplateRequest(QString)), comManager, SLOT(enQueueRemoveTemplateMessage(QString)));
    connect(comManager, SIGNAL(removeTemplate(QString)), this, SIGNAL(removeTemplate(QString)));

    ///////////////////////////////////////////
    // Player Administrator
    ///////////////////////////////////////////
    connect(&playerAdmin, SIGNAL(playerListChanged(QList<Player>)), comManager, SLOT(enQueuePlayerListRefreshMessage(QList<Player>)));
    connect(comManager, SIGNAL(refreshPlayerList(QList<Player>)), this, SIGNAL(refreshPlayerListDisplay(QList<Player>)));
}

GameController::~GameController()
{
    comManager->deleteLater();
}

void GameController::createNetworkInterface(NetworkType t, QString ip)
{
    switch(t)
    {
    case SERVER:
        netInterface = new NetworkServer(&inQueue, &outQueue, this);
        connect(netInterface, SIGNAL(newPlayerConnected(Client)), &playerAdmin, SLOT(handleNewPlayerConnection(Client)));
        connect(netInterface, SIGNAL(playerDisconnected(Client)), &playerAdmin, SLOT(handlePlayerDisconnection(Client)));
        connect(&playerAdmin, SIGNAL(playerListChanged(QList<Player>)), SIGNAL(refreshPlayerListDisplay(QList<Player>)));
        // Add server to the player list
        playerAdmin.authorizePlayer(Player(game.getMe(), "127.0.0.1", true));
        break;
    case CLIENT:
        netInterface = new NetworkClient(&inQueue, &outQueue, this, ip);
        connect(netInterface, SIGNAL(firstConnectionToServer()), comManager, SLOT(enQueueServerInfoRequest()));
        break;
    default:
        //TODO error
        break;
    }

    // TODO handle this more cleanly
    //connect(netInterface, SIGNAL(stateChanged(QString)),comManager, SIGNAL(newChatMessageToPrint(QString,QString)));
    connect(&outQueue, SIGNAL(newMessageAvailable()), netInterface, SLOT(send()));
    connect(netInterface, SIGNAL(networkEvent(QString)), this, SIGNAL(networkEvent(QString)));
    //printNetworkState(netInterface->getState());
}

void GameController::disconnectNetworkInterface()
{
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


