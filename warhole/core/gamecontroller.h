#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "commandManager/commandmanager.h"
#include "network/networkinterface.h"
#include "network/networkclient.h"
#include "network/networkserver.h"
#include "game/game.h"
#include "PlayerAdmninistrator/playeradministrator.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = 0);
    virtual ~GameController();

    void createNetworkInterface(NetworkType t, QString ip = "");
    void disconnectNetworkInterface();

    Game getGame() const;
    Game* getGamePtr();
    void setGame(const Game &value);


signals:
    void newChatMessageToPrint(QString, QString);
    void newChatMessageToSend(QString);
    void refreshPlayerListDisplay(QList<Player>);
    void networkEvent(QString);

public slots:

private:
    NetworkInterface* netInterface;
    CommandManager* comManager;
    PlayerAdministrator playerAdmin;
    MessageQueue inQueue;
    MessageQueue outQueue;
    Game game;
};

#endif // GAMECONTROLLER_H
