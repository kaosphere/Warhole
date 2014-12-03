#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "commandManager/commandmanager.h"
#include "network/networkinterface.h"
#include "network/networkclient.h"
#include "network/networkserver.h"
#include "game/game.h"
#include "game/terrain/terrain.h"
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
    bool networkActive();

signals:
    void networkEnabled(bool);
    void newChatMessageToPrint(QString, QString);
    void newChatMessageToSend(QString);
    void refreshPlayerListDisplay(QList<Player>);
    void networkEvent(QString);
    void addRulerToGameScene(QString id, int l);
    void addRulerToGameSceneRequest(int l);
    void rulerMoved(QString, QPointF, QTransform, qreal);
    void moveRuler(QString, QPointF, QTransform, qreal);
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
    void regimentMoved(QString, QPointF, QTransform, qreal);
    void moveRegiment(QString, QPointF, QTransform, qreal);
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
    void serverInfoRequested(QString);
    void sendGlobalInfoUpdate(QString, QByteArray);
    void loadGlobalInfoUpdate(QByteArray);
    void requestNewTerrain(Terrain);
    void newTerrain(QString, Terrain);
    void removeTerrainRequest(QString);
    void lockTerrainRequest(QString, bool);
    void terrainMoved(QString, QPointF, QTransform, qreal);
    void removeTerrain(QString);
    void lockTerrain(QString, bool);
    void moveTerrain(QString,QPointF,QTransform, qreal);
    void removeBlowTemplateRequest(QString);
    void blowTemplateMoved(QString, QPointF, QTransform, qreal);
    void requestBlowTemplate();
    void removeBlowTemp(QString);
    void moveBlowTemp(QString, QPointF, QTransform, qreal);
    void newBlowTemp(QString);
    void newTextRequest(QString);
    void removeTextRequest(QString);
    void textChanged(QString, QString, QPointF, QTransform, qreal);
    void newText(QString, QString);
    void moveText(QString, QString, QPointF, QTransform, qreal);
    void removeText(QString);
    void requestNewScatter(int);
    void scatterMoved(QString, QPointF);
    void removeScatterRequest(QString);
    void newScatter(QString, int);
    void moveScatter(QString, QPointF);
    void removeScatter(QString);

public slots:
    void setNetwork();
    void clearNetwork();
    void changeMyName(QString n);

private:
    NetworkInterface* netInterface;
    CommandManager* comManager;
    PlayerAdministrator playerAdmin;
    MessageQueue inQueue;
    MessageQueue outQueue;
    Game game;
    bool network;
};

#endif // GAMECONTROLLER_H
