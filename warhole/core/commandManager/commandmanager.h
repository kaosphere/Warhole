#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>

#include "core/messagequeue.h"
#include "game/game.h"
#include "core/network/networkinterface.h"

enum CommandType{
    SERVER_INFO_REQUEST,
    SERVER_INFO,
    GLOBAL_UPDATE_REQUEST,
    GLOBAL_UPDATE,
    CHAT_MESSAGE,
    NEW_RULER,
    RULER_POSITION_CHANGE,
    RULER_REMOVE,
    NEW_REGIMENT,
    REGIMENT_MOVE,
    REGIMENT_INFO_CHANGE,
    REGIMENT_REMOVE
};

class CommandManager : public QObject
{
    Q_OBJECT
public:
    explicit CommandManager(MessageQueue* iq, MessageQueue* oq, Game* g, QObject *parent = 0);

signals:
    void newChatMessageAvailable(QString player, QString msg);
    
public slots:
    void processIncomingMessage();
    void enQueueChatMessage(QString player, QString message);
    void handleNetworkEvent(NetworkEvent e, QString details);

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    MessageQueue* outQueue;
    MessageQueue* inQueue;
    Game* game;
    //QMap<int, RegimentGraphics>* regimentMap;


    void addMessageToOutQueue(const Message &m);
    void addMessageToInQueue(const Message &m);
    void handleServerInfoRequest(MessageDestination dest, QString sender);
    void handleServerInfo(QByteArray &data);
    void enQueueServerInfoRequest();
    void handleNewChatMessage(QDataStream& data);
};

#endif // COMMANDMANAGER_H
