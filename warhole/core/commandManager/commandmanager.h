#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>

#include "core/messagequeue.h"
#include "game/game.h"
#include "core/network/networkinterface.h"
#include "Utilities/RandomIdGenerator/idgenerator.h"

enum CommandType{
    SERVER_INFO_REQUEST,
    SERVER_INFO,
    GLOBAL_UPDATE_REQUEST,
    GLOBAL_UPDATE,
    PLAYER_LIST_UPDATE,
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
    void newChatMessageAvailable(QString sender,QString msg);
    void refreshPlayerList(QList<Player> l);
    void createRuler(QString id, int l);
    void moveRuler(QString id, QTransform matrix);
    
public slots:
    void processIncomingMessage();
    void enQueueChatMessage(QString message);
    void enQueueServerInfoRequest();
    void enQueuePlayerListRefreshMessage(QList<Player> l);
    void enQueueCreateRulerMessage(int l);
    void enQueueRulerMoveMessage(QString i, QTransform matrix);

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
    void handleNewChatMessage(const Message& m, QDataStream& data);
    void handlePlayerListRefreshMessage(const Message &m, QDataStream &data);
    void handleCreateRulerMessage(const Message &m, QDataStream &data);
    void handleRulerMoveMessage(const Message &m, QDataStream &data);
};

#endif // COMMANDMANAGER_H
