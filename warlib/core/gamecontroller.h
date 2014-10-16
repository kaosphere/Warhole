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
    void addRulerToGameScene(QString id, int l);
    void addRulerToGameSceneRequest(int l);
    void rulerMoved(QString, QPointF, QTransform);
    void moveRuler(QString, QPointF, QTransform);
    void addRoundTemplateToGameSceneRequest(int d);
    void addRoundTemplateScene(QString i, int d);
    void templateMoved(QString, QPointF);
    void moveTemplate(QString, QPointF);
    void removeRulerRequest(QString);
    void removeRuler(QString);
    void removeTemplateRequest(QString);
    void removeTemplate(QString);
    void addRegimentRequest(QString, RegimentAbstract);
    void createRegiment(QString, QString, RegimentAbstract);
    void regimentMoved(QString, QPointF, QTransform);
    void moveRegiment(QString, QPointF, QTransform);
    void removeRegimentRequest(QString);
    void removeDeadsRequest(QString, int);
    void changeWidthRequest(QString, int);
    void removeRegiment(QString);
    void removeDeads(QString, int);
    void changeRegimentWidth(QString, int);
    void addModelToRegRequest(QString, int);
    void changeRegInfoRequest(QString, RegimentAbstract);
    void addModels(QString, int);
    void changeRegInfo(QString, RegimentAbstract);


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
