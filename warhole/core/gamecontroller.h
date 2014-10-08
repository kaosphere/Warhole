#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "commandManager/commandmanager.h"
#include "network/networkinterface.h"
#include "network/networkclient.h"
#include "network/networkserver.h"
#include "game/game.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = 0);

    void createNetworkInterface(NetworkType t, QString ip = "");

    Game getGame() const;
    Game* getGamePtr();
    void setGame(const Game &value);

signals:
    void newChatMessageToPrint(QString, QString);
    void newChatMessageToSend(QString);

public slots:

private:
    NetworkInterface* netInterface;
    CommandManager* comManager;
    MessageQueue inQueue;
    MessageQueue outQueue;
    Game game;
};

#endif // GAMECONTROLLER_H
