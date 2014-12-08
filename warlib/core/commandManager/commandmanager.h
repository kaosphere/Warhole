#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>

#include "core/messagequeue.h"
#include "game/game.h"
#include "game/terrain/terrain.h"
#include "core/network/networkinterface.h"
#include "Utilities/RandomIdGenerator/idgenerator.h"

enum CommandType{
    SERVER_INFO_REQUEST = 0,
    SERVER_INFO,
    PLAYER_LIST_UPDATE,
    PLAYER_NAME_CHANGE,
    CHAT_MESSAGE,
    NEW_RULER,
    RULER_POSITION_CHANGE,
    RULER_REMOVE,
    NEW_ROUND_TEMPLATE,
    ROUND_TEMPLATE_POSITION_CHANGE,
    ROUND_TEMPLATE_REMOVE,
    NEW_REGIMENT,
    REGIMENT_MOVE,
    REGIMENT_REMOVE_DEADS,
    REGIMENT_WIDTH_CHANGE,
    REGIMENT_REMOVE,
    REGIMENT_ADD_MODELS,
    REGIMENT_CHANGE_INFO,
    NEW_TERRAIN,
    TERRAIN_MOVE,
    TERRAIN_DELETE,
    TERRAIN_LOCK,
    NEW_BLOW_TEMP,
    BLOW_TEMP_MOVE,
    REMOVE_BLOW_TEMP,
    NEW_TEXT,
    TEXT_CHANGED,
    REMOVE_TEXT,
    NEW_SCATTER,
    SCATTER_MOVE,
    REMOVE_SCATTER
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
    void moveRuler(QString id, QPointF p, QTransform a, qreal pr);
    void removeRuler(QString id);
    void createRoundTemplate(QString id, int d);
    void moveTemplate(QString id, QPointF p);
    void removeTemplate(QString);
    void createRegiment(QString, QString, RegimentAbstract);
    void moveRegiment(QString, QPointF, QTransform, qreal);
    void removeRegiment(QString);
    void removeDeads(QString, int);
    void changeRegimentWidth(QString, int);
    void addModels(QString, int);
    void changeRegInfo(QString, RegimentAbstract);
    void serverInfoRequested(QString);
    void loadGlobalInfoUpdate(QByteArray);
    void newTerrain(QString, Terrain);
    void removeTerrain(QString);
    void lockTerrain(QString, bool);
    void moveTerrain(QString, QPointF, QTransform, qreal);
    void newBlowTemp(QString);
    void moveBlowTemp(QString, QPointF, QTransform, qreal);
    void removeBlowTemp(QString);
    void newText(QString, QString);
    void moveText(QString, QString, QPointF, QTransform, qreal);
    void removeText(QString);
    void newScatter(QString, int);
    void moveScatter(QString, QPointF);
    void removeScatter(QString);
    void playerNameChange(QString);
    void changeClientName(QString, QString);
    
public slots:
    void processIncomingMessage();
    void enQueueChatMessage(QString message);
    void enQueueServerInfoRequest();
    void enQueueServerInfo(QString destination, QByteArray info);
    void enQueuePlayerListRefreshMessage(QList<Player> l);
    void enQueueCreateRulerMessage(int l);
    void enQueueRulerMoveMessage(QString i, QPointF p, QTransform matrix, qreal pr);
    void enqueueCreateRoundTemplateMessage(int d);
    void enQueueTemplateMoveMessage(QString id, QPointF p);
    void enQueueRemoveRulerMessage(QString i);
    void enQueueRemoveTemplateMessage(QString i);
    void enqueueNewRegimentMessage(QString o, RegimentAbstract r);
    void enqueueRegimentMoveMessage(QString i, QPointF p, QTransform matrix, qreal pr);
    void enqueueRemoveRegimentMessage(QString i);
    void enqueueRemoveDeadsMessage(QString i, int n);
    void enqueueChangeWidthMessage(QString i, int w);
    void enqueueAddModelMessage(QString i, int nb);
    void enqueueChangeRegInfoMessage(QString i, RegimentAbstract r);
    void enQueueNewTerrainMessage(Terrain t);
    void enQueueRemoveTerrainMessage(QString id);
    void enQueueLockTerrainMessage(QString id, bool l);
    void enQueueMoveTerrainMessage(QString i, QPointF p, QTransform matrix, qreal pr);
    void enQueueNewBlowTemplateMessage();
    void enQueueBlowTemplateMoveMessage(QString i, QPointF p, QTransform matrix, qreal pr);
    void enQueueRemoveBlowTemplateMessage(QString i);
    void enQueueNewTextMessage(QString text);
    void enQueueRemoveTextMessage(QString i);
    void enQueueTextChangeMessage(QString i, QString t, QPointF p, QTransform matrix, qreal pr);
    void enQueueNewScatterMessage(int angle);
    void enQueueRemoveScatterMessage(QString i);
    void enQueueScatterMoveMessage(QString i, QPointF p);
    void enqueuePlayerNameChangeRequest(QString n1, QString n2);

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
    void handleServerInfo(QDataStream &data);
    void handleNewChatMessage(const Message& m, QDataStream& data);
    void handlePlayerListRefreshMessage(QDataStream &data);
    void handleCreateRulerMessage(QDataStream &data);
    void handleRulerMoveMessage(QDataStream &data);
    void handleCreateRoundTemplateMessage( QDataStream& data);
    void handleTemplateMoveMessage(QDataStream &data);
    void handleRemoveRulerMessage(QDataStream &data);
    void handleRemoveTemplateMessage(QDataStream &data);
    void handleNewRegimentMessage(QDataStream &data);
    void handleRegimentMoveMessage(QDataStream &data);
    void handleRemoveRegimentMessage(QDataStream &data);
    void handleRemoveDeadsRegimentMessage(QDataStream &data);
    void handleChangeWidthRegimentMessage(QDataStream &data);
    void handleAddModelsMessage(QDataStream &data);
    void handleChangeRegInfoMessage(QDataStream &data);
    void handleNewTerrainMessage(QDataStream &data);
    void handleRemoveTerrainMessage(QDataStream& data);
    void handleLockTerrainMessage(QDataStream& data);
    void handleMoveTerrainMessage(QDataStream& data);
    void handleNewBlowTempMessage(QDataStream& data);
    void handleMoveBlowTempMessage(QDataStream& data);
    void handleRemoveBlowTempMessage(QDataStream& data);
    void handleNewTextMessage(QDataStream& data);
    void handleMoveTextMessage(QDataStream& data);
    void handleRemoveTextMessage(QDataStream& data);
    void handleNewScatterMessage(QDataStream& data);
    void handleMoveScatterMessage(QDataStream& data);
    void handleRemoveScatterMessage(QDataStream& data);
    void hangleChangePlayerNameMessage(QDataStream &data);
};

#endif // COMMANDMANAGER_H
