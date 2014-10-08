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

    ///////////////////////////////////////////
    // Player Administrator
    ///////////////////////////////////////////
    connect(&playerAdmin, SIGNAL(playerListChanged(QList<Player>)), comManager, SLOT(enQueuePlayerListRefreshMessage(QList<Player>)));
    connect(comManager, SIGNAL(refreshPlayerList(QList<Player>)), this, SIGNAL(refreshPlayerListDisplay(QList<Player>)));
}

void GameController::createNetworkInterface(NetworkType t, QString ip)
{
    switch(t)
    {
    case SERVER:
        netInterface = new NetworkServer(&inQueue, &outQueue, this);
        connect(netInterface, SIGNAL(newPlayerConnected(Client)), &playerAdmin, SLOT(handleNewPlayerConnection(Client)));
        break;
    case CLIENT:
        netInterface = new NetworkClient(&inQueue, &outQueue, this, ip);
        break;
    default:
        //TODO error
        break;
    }

    // TODO handle this more cleanly
    //connect(netInterface, SIGNAL(stateChanged(QString)),comManager, SIGNAL(newChatMessageToPrint(QString,QString)));
    connect(&outQueue, SIGNAL(newMessageAvailable()), netInterface, SLOT(send()));
    connect(netInterface, SIGNAL(networkEvent(NetworkEvent, QString)), comManager, SLOT(handleNetworkEvent(NetworkEvent, QString)));
    //printNetworkState(netInterface->getState());
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

