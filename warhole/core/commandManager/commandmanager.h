#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>

#include "core/messagequeue.h"
#include "game/game.h"

enum CommandType{
    SERVER_INFO,
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

private:
    MessageQueue* outQueue;
    MessageQueue* inQueue;

    Game* game;
    
};

#endif // COMMANDMANAGER_H
