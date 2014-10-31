#include "commandmanager.h"

using namespace QLogger;

const QString CommandManager::LOG_ID_INFO = "CommandManager_info";
const QString CommandManager::LOG_ID_TRACE = "CommandManager_trace";
const QString CommandManager::LOG_ID_WARN = "CommandManager_warm";
const QString CommandManager::LOG_ID_ERR = "CommandManager_err";

CommandManager::CommandManager(MessageQueue *iq, MessageQueue *oq, Game *g, QObject *parent) :
    QObject(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    outQueue = oq;
    inQueue = iq;
    game = g;

    if(inQueue)
    {
        connect(inQueue, SIGNAL(newMessageAvailable()), this, SLOT(processIncomingMessage()));
    }
}

void CommandManager::addMessageToInQueue(const Message& m)
{
    if(inQueue)
    {
        QLog_Info(LOG_ID_INFO,"Adding Message to InQueue with sender : "  + m.getMessageSender() +
                  " Destination : " + QString::number(m.getDest()) + " Data : "
                  + QString::number(m.getData().toUShort()));
        inQueue->addMessage(m);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "addMessageToInQueue : inQueue pointer is null");
    }
}

void CommandManager::addMessageToOutQueue(const Message& m)
{
    if(outQueue)
    {
        QLog_Info(LOG_ID_INFO,"Adding Message to outQueue with sender : "  + m.getMessageSender() +
                  " Destination : " + QString::number(m.getDest()) + " Data : "
                  + QString::number(m.getData().toUShort()));
        outQueue->addMessage(m);
    }
    else
    {
        QLog_Error(LOG_ID_ERR, "addMessageToOutQueue : outQueue pointer is null");
    }
}


void CommandManager::enQueueChatMessage(QString message)
{
    QLog_Info(LOG_ID_INFO, "enQueueChatMessage() : sending chat message to all.");
    Message m;
    m.setMessageSender(game->getMe());
    m.setDest(ALL);
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    stream << CHAT_MESSAGE
           << message;

    m.setData(data);

    qDebug() << "Destination du chat : " + QString::number((int)(m.getDest()));

    addMessageToOutQueue(m);
}

void CommandManager::handleNewChatMessage(const Message& m, QDataStream& data)
{
    QString msg;
    data >> msg;
    emit newChatMessageAvailable(m.getMessageSender(), msg);
}

void CommandManager::enQueueServerInfoRequest()
{
    QLog_Info(LOG_ID_INFO, "enQueueServerInfoRequest() : sending server info request to server.");
    Message m;
    m.setDest(ME);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    stream << SERVER_INFO_REQUEST;

    addMessageToOutQueue(m);
}


void CommandManager::enQueueServerInfo(QString destination, QByteArray info)
{
    QLog_Info(LOG_ID_INFO, "enQueueServerInfo() : sending server info to " + destination);
    Message m;

    if(destination != "")
    {
        m.setDest(ME);
        m.setMessageSender(destination);
    }
    else
    {
        m.setDest(ALL_BUT_ME);
        m.setMessageSender(game->getMe());
    }

    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);
    stream << SERVER_INFO;
    stream << info;

    m.setData(data);

    addMessageToOutQueue(m);
}

void CommandManager::handleServerInfoRequest(MessageDestination dest, QString sender)
{
    QLog_Info(LOG_ID_INFO, "handleServerInfoRequest() : asking for game info for " + sender);
    emit serverInfoRequested(sender);
}

void CommandManager::handleServerInfo(QDataStream& data)
{
    QLog_Info(LOG_ID_INFO, "handleServerInfo() : global update");
    QByteArray info;

    data >> info;

    emit loadGlobalInfoUpdate(info);
}

void CommandManager::enQueuePlayerListRefreshMessage(QList<Player> l)
{
    QLog_Info(LOG_ID_INFO, "enQueuePlayerListRefreshMessage() : sending player list to all clients");
    Message m;
    m.setDest(ALL_BUT_ME);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << PLAYER_LIST_UPDATE;
    s << l.size();
    for(int i = 0; i < l.size(); ++i)
    {
        s << l.at(i);
    }

    m.setData(data);

    addMessageToOutQueue(m);
}

void CommandManager:: handlePlayerListRefreshMessage(QDataStream& data)
{
    QLog_Info(LOG_ID_INFO, "handlePlayerListRefreshMessage() : refreshing player list");
    int size;
    QList<Player> l;

    data >> size;

    for(int i = 0; i < size; ++i)
    {
        Player p;
        data >> p;
        l.append(p);
    }
    emit refreshPlayerList(l);
}

void CommandManager::enQueueCreateRulerMessage(int l)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << NEW_RULER;
    QString id = IdGenerator::generateRandomID(IdGenerator::ID_SIZE);
    s << id;
    s << l;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueCreateRulerMessage() : sending new ruler message with ID " +
              id + " with length " + QString::number(l));

    addMessageToOutQueue(m);
}



void CommandManager::handleCreateRulerMessage(QDataStream& data)
{
    int length;
    QString id;

    data >> id;
    data >> length;

    QLog_Info(LOG_ID_INFO, "handleCreateRulerMessage() : received new ruler message with ID " +
              id + " with length " + QString::number(length));


    emit createRuler(id,length);
}

void CommandManager::enQueueRulerMoveMessage(QString i, QPointF p, QTransform matrix)
{
    Message m;
    m.setDest(ALL_BUT_ME);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << RULER_POSITION_CHANGE;

    s << i;
    s << p;
    s << matrix;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueRulerMoveMessage() : ruler move message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::handleRulerMoveMessage(QDataStream& data)
{
    QString id;
    QPointF point;
    QTransform matrix;

    data >> id;
    data >> point;
    data >> matrix;

    QLog_Info(LOG_ID_INFO, "handleRulerMoveMessage() : received ruler moved message with ID " + id);


    emit moveRuler(id,point,matrix);
}

void CommandManager::enQueueRemoveRulerMessage(QString i)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << RULER_REMOVE;

    s << i;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueRemoveRulerMessage() : ruler remove message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::handleRemoveRulerMessage(QDataStream& data)
{
    QString id;

    data >> id;

    QLog_Info(LOG_ID_INFO, "handleRemoveRulerMessage() : received remove ruler message with ID " + id);

    emit removeRuler(id);
}

void CommandManager::enQueueRemoveTemplateMessage(QString i)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << ROUND_TEMPLATE_REMOVE;

    s << i;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueRemoveTemplateMessage() : template remove message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::handleRemoveTemplateMessage(QDataStream& data)
{
    QString id;

    data >> id;

    QLog_Info(LOG_ID_INFO, "handleRemoveTemplateMessage() : received remove template message with ID " + id);

    emit removeTemplate(id);
}


void CommandManager::enqueueCreateRoundTemplateMessage(int d)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << NEW_ROUND_TEMPLATE;

    QString id = IdGenerator::generateRandomID(IdGenerator::ID_SIZE);
    s << id;
    s << d;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enqueueCreateRoundTemplateMessage() : new round template created with ID " + id);

    addMessageToOutQueue(m);
}

void CommandManager::handleCreateRoundTemplateMessage(QDataStream &data)
{
    int diameter;
    QString id;

    data >> id;
    data >> diameter;

    QLog_Info(LOG_ID_INFO, "handleCreateRoundTemplateMessage() : received new ruler message with ID " +
              id + " with diameter " + QString::number(diameter));


    emit createRoundTemplate(id,diameter);
}

void CommandManager::enQueueTemplateMoveMessage(QString id, QPointF p)
{
    Message m;
    m.setDest(ALL_BUT_ME);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << ROUND_TEMPLATE_POSITION_CHANGE;

    s << id;
    s << p;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueTemplateMoveMessage() : template move message with ID " + id);

    addMessageToOutQueue(m);
}


void CommandManager::handleTemplateMoveMessage(QDataStream &data)
{
    QString id;
    QPointF point;

    data >> id;
    data >> point;

    QLog_Info(LOG_ID_INFO, "handleTemplateMoveMessage() : received template moved message with ID " + id);

    emit moveTemplate(id,point);
}


void CommandManager::enqueueNewRegimentMessage(QString o, RegimentAbstract r)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << NEW_REGIMENT;
    QString id = IdGenerator::generateRandomID(IdGenerator::ID_SIZE);
    s << id;
    s << o;
    s << r;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enqueueNewRegimentMessage() : new regiment message with ID " + id);

    addMessageToOutQueue(m);
}

void CommandManager::handleNewRegimentMessage(QDataStream &data)
{
    QString id;
    QString owner;
    // TODO : pointer?
    RegimentAbstract r;

    data >> id;
    data >> owner;
    data >> r;

    QLog_Info(LOG_ID_INFO, "handleNewRegimentMessage() : received new regiment message with ID " + id +
              " and owner " + owner);
    QLog_Info(LOG_ID_INFO, "handleNewRegimentMessage() : regiment received : \n" + r.displayShortInfo());

    emit createRegiment(id, owner, r);
}

void CommandManager::enqueueRegimentMoveMessage(QString i, QPointF p , QTransform matrix)
{
    Message m;
    m.setDest(ALL_BUT_ME);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << REGIMENT_MOVE;

    s << i;
    s << p;
    s << matrix;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enqueueRegimentMoveMessage() : regiment move message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::handleRegimentMoveMessage(QDataStream &data)
{
    QString id;
    QPointF point;
    QTransform matrix;

    data >> id;
    data >> point;
    data >> matrix;

    QLog_Info(LOG_ID_INFO, "handleRegimentMoveMessage() : received regiment moved message with ID " + id);


    emit moveRegiment(id,point,matrix);
}


void CommandManager::enqueueRemoveRegimentMessage(QString i)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << REGIMENT_REMOVE;

    s << i;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enqueueRemoveRegimentMessage() : regiment remove message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::enqueueRemoveDeadsMessage(QString i, int n)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << REGIMENT_REMOVE_DEADS;

    s << i;
    s << n;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enqueueRemoveDeadsMessage() : deads remove message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::enqueueChangeWidthMessage(QString i, int w)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << REGIMENT_WIDTH_CHANGE;

    s << i;
    s << w;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enqueueChangeWidthMessage() : change width message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::handleRemoveRegimentMessage(QDataStream &data)
{
    QString id;

    data >> id;

    QLog_Info(LOG_ID_INFO, "handleRemoveRegimentMessage() : received regiment remove message with ID " + id);

    emit removeRegiment(id);
}

void CommandManager::handleRemoveDeadsRegimentMessage(QDataStream &data)
{
    QString id;
    int nb;

    data >> id;
    data >> nb;

    QLog_Info(LOG_ID_INFO, "handleRemoveRegimentMessage() : received remove " +
              QString::number(nb) + " deads to regiment with ID " + id);

    emit removeDeads(id,nb);
}

void CommandManager::handleChangeWidthRegimentMessage(QDataStream &data)
{
    QString id;
    int w;

    data >> id;
    data >> w;

    QLog_Info(LOG_ID_INFO, "handleChangeWidthRegimentMessage() : change width message to regiment with ID " + id);

    emit changeRegimentWidth(id,w);
}

void CommandManager::handleAddModelsMessage(QDataStream &data)
{
    QString id;
    int nb;

    data >> id;
    data >> nb;

    QLog_Info(LOG_ID_INFO, "handleAddModelsMessage() : add models message to regiment with ID " + id);

    emit addModels(id,nb);
}

void CommandManager::handleChangeRegInfoMessage(QDataStream &data)
{
    QString id;
    RegimentAbstract r;

    data >> id;
    data >> r;

    QLog_Info(LOG_ID_INFO, "handleAddModelsMessage() : change reg info, regiment with ID " + id);

    emit changeRegInfo(id,r);
}


void CommandManager::enqueueAddModelMessage(QString i, int nb)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << REGIMENT_ADD_MODELS;

    s << i;
    s << nb;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enqueueAddModelMessage() : add models message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::enqueueChangeRegInfoMessage(QString i, RegimentAbstract r)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << REGIMENT_CHANGE_INFO;
    s << i;
    s << r;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enqueueChangeRegInfoMessage() : change reg indo message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::enQueueNewTerrainMessage(Terrain t)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << NEW_TERRAIN;
    QString id = IdGenerator::generateRandomID(IdGenerator::ID_SIZE);
    s << id;
    s << t;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueNewTerrainMessage() : new terrain message with ID " + id);

    addMessageToOutQueue(m);
}

void CommandManager::enQueueRemoveTerrainMessage(QString id)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << TERRAIN_DELETE;
    s << id;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueRemoveTerrainMessage() : remove terrain message with ID " + id);

    addMessageToOutQueue(m);
}

void CommandManager::enQueueLockTerrainMessage(QString id, bool l)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << TERRAIN_LOCK;
    s << id;
    s << l;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueLockTerrainMessage() : lock terrain message with ID " + id);

    addMessageToOutQueue(m);
}

void CommandManager::enQueueMoveTerrainMessage(QString i, QPointF p, QTransform matrix)
{
    Message m;
    m.setDest(ALL_BUT_ME);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << TERRAIN_MOVE;

    s << i;
    s << p;
    s << matrix;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueMoveTerrainMessage() : terrain move message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::handleNewTerrainMessage(QDataStream &data)
{
    QString id;
    Terrain t;

    data >> id;
    data >> t;

    QLog_Info(LOG_ID_INFO, "handleNewTerrainMessage() : add new terrain with ID " + id);

    emit newTerrain(id,t);
}

void CommandManager::handleRemoveTerrainMessage(QDataStream &data)
{
    QString id;

    data >> id;

    QLog_Info(LOG_ID_INFO, "handleRemoveTerrainMessage() : remove terraub message with ID " + id);

    emit removeTerrain(id);
}

void CommandManager::handleLockTerrainMessage(QDataStream &data)
{
    QString id;
    bool l;

    data >> id;
    data >> l;

    QLog_Info(LOG_ID_INFO, "handleLockTerrainMessage() : lock terraub message with ID " + id);

    emit lockTerrain(id, l);
}

void CommandManager::handleMoveTerrainMessage(QDataStream &data)
{
    QString id;
    QPointF p;
    QTransform matrix;

    data >> id;
    data >> p;
    data >> matrix;

    QLog_Info(LOG_ID_INFO, "handleMoveTerrainMessage() : move terrain message with ID " + id);

    emit moveTerrain(id, p, matrix);
}

void CommandManager::handleNewBlowTempMessage(QDataStream &data)
{
    QString id;

    data >> id;

    QLog_Info(LOG_ID_INFO, "handleNewBlowTempMessage() : new blow temp message with ID " + id);

    emit newBlowTemp(id);
}

void CommandManager::handleMoveBlowTempMessage(QDataStream &data)
{
    QString id;
    QPointF p;
    QTransform matrix;

    data >> id;
    data >> p;
    data >> matrix;

    QLog_Info(LOG_ID_INFO, "handleMoveBlowTempMessage() : move blow temp message with ID " + id);

    emit moveBlowTemp(id, p, matrix);
}

void CommandManager::handleRemoveBlowTempMessage(QDataStream &data)
{
    QString id;

    data >> id;

    QLog_Info(LOG_ID_INFO, "handleRemoveBlowTempMessage() : remove blow temp message with ID " + id);

    emit removeBlowTemp(id);
}


void CommandManager::enQueueNewBlowTemplateMessage()
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << NEW_BLOW_TEMP;

    QString id = IdGenerator::generateRandomID(IdGenerator::ID_SIZE);

    s << id;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueNewBlowTemplateMessage() : new blow template message with ID " + id);

    addMessageToOutQueue(m);
}

void CommandManager::enQueueBlowTemplateMoveMessage(QString i, QPointF p, QTransform matrix)
{
    Message m;
    m.setDest(ALL_BUT_ME);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << BLOW_TEMP_MOVE;

    s << i;
    s << p;
    s << matrix;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueNewBlowTemplateMoveMessage() : blow template move message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::enQueueRemoveBlowTemplateMessage(QString i)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << REMOVE_BLOW_TEMP;

    s << i;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueRemoveBlowTemplateMessage() : blow template remove message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::enQueueNewTextMessage(QString text)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << NEW_TEXT;

    QString id = IdGenerator::generateRandomID(IdGenerator::ID_SIZE);

    s << id;
    s << text;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueNewTextMessage() : new text message with ID " + id);

    addMessageToOutQueue(m);
}

void CommandManager::enQueueRemoveTextMessage(QString i)
{
    Message m;
    m.setDest(ALL);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << REMOVE_TEXT;

    s << i;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueRemoveTextMessage() : text remove message with ID " + i);

    addMessageToOutQueue(m);
}

void CommandManager::enQueueTextChangeMessage(QString i, QString t, QPointF p, QTransform matrix)
{
    Message m;
    m.setDest(ALL_BUT_ME);
    m.setMessageSender(game->getMe());

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << TEXT_CHANGED;

    s << i;
    s << t;
    s << p;
    s << matrix;

    m.setData(data);

    QLog_Info(LOG_ID_INFO, "enQueueTextChangeMessage() : text move message with ID " + i +
              " and text : " + t);

    addMessageToOutQueue(m);
}

void CommandManager::handleNewTextMessage(QDataStream &data)
{
    QString id;
    QString text;

    data >> id;
    data >> text;

    QLog_Info(LOG_ID_INFO, "handleNewTextMessage() : new text message with ID " + id +
              " and text : " + text);

    emit newText(id, text);
}

void CommandManager::handleMoveTextMessage(QDataStream &data)
{
    QString id;
    QString text;
    QPointF p;
    QTransform matrix;

    data >> id;
    data >> text;
    data >> p;
    data >> matrix;

    QLog_Info(LOG_ID_INFO, "handleMoveTextMessage() : move blow temp message with ID " + id);

    emit moveText(id, text, p, matrix);
}

void CommandManager::handleRemoveTextMessage(QDataStream &data)
{
    QString id;

    data >> id;

    QLog_Info(LOG_ID_INFO, "handleRemoveTextMessage() : remove blow temp message with ID " + id);

    emit removeText(id);
}


void CommandManager::processIncomingMessage()
{
    Message m;

    if(!inQueue)
    {
        QLog_Error(LOG_ID_ERR, "processIncomingMessage() : Inqueue pointer is null");
        return;
    }

    //while(!inQueue->isMessageListEmpty())
    //{
        if(inQueue)
        {
            m = inQueue->getAndRemoveFirstMessage();
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Still " + QString::number(inQueue->getMessageList().size()) +
                      " message to be handled.");
        }
        QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New Message to process. Sender : " + m.getMessageSender() +
                  " Destination : " + QString::number(m.getDest()) + " Data : " + QString::number(m.getData().toUShort()));

        QByteArray data = m.getData();
        QDataStream stream(data);

        // Get command type
        int command;
        stream >> command;

        // TODO log each type of message received
        switch(command)
        {
        case CHAT_MESSAGE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Chat message received from " + m.getMessageSender());
            handleNewChatMessage(m, stream);
            break;

        case SERVER_INFO_REQUEST:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Server info request received from " + m.getMessageSender() +
                      " with dest : " + QString::number((int)m.getDest()));
            handleServerInfoRequest(m.getDest(), m.getMessageSender());
            break;

        case SERVER_INFO:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Server info received from server.");
            handleServerInfo(stream);
            break;

        case PLAYER_LIST_UPDATE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Player list update received.");
            handlePlayerListRefreshMessage(stream);
            break;

        case NEW_RULER:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New ruler message received.");
            handleCreateRulerMessage(stream);
            break;

        case RULER_POSITION_CHANGE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Ruler moved message received.");
            handleRulerMoveMessage(stream);
            break;

        case RULER_REMOVE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Ruler remove message received.");
            handleRemoveRulerMessage(stream);
            break;

        case NEW_ROUND_TEMPLATE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New Round template received.");
            handleCreateRoundTemplateMessage(stream);
            break;

        case ROUND_TEMPLATE_POSITION_CHANGE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Template moved message received.");
            handleTemplateMoveMessage(stream);
            break;

        case ROUND_TEMPLATE_REMOVE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Template remove message received.");
            handleRemoveTemplateMessage(stream);
            break;

        case NEW_REGIMENT:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New regiment message received.");
            handleNewRegimentMessage(stream);
            break;

        case REGIMENT_MOVE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New regiment move message received.");
            handleRegimentMoveMessage(stream);
            break;

        case REGIMENT_REMOVE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() :Regiment remove message received.");
            handleRemoveRegimentMessage(stream);
            break;

        case REGIMENT_REMOVE_DEADS:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() :Regiment remove deads message received.");
            handleRemoveDeadsRegimentMessage(stream);
            break;

        case REGIMENT_WIDTH_CHANGE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() :Regiment width change message received.");
            handleChangeWidthRegimentMessage(stream);
            break;

        case REGIMENT_ADD_MODELS:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Add models message received.");
            handleAddModelsMessage(stream);
            break;

        case REGIMENT_CHANGE_INFO:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() :Regiment info change message received.");
            handleChangeRegInfoMessage(stream);
            break;

        case NEW_TERRAIN:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New terrain message received.");
            handleNewTerrainMessage(stream);
            break;

        case TERRAIN_DELETE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New terrain message received.");
            handleRemoveTerrainMessage(stream);
            break;

        case TERRAIN_LOCK:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Terrain lock message received.");
            handleLockTerrainMessage(stream);
            break;

        case TERRAIN_MOVE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Move terrain message received.");
            handleMoveTerrainMessage(stream);
            break;

        case NEW_BLOW_TEMP:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() :New blow template message received.");
            handleNewBlowTempMessage(stream);
            break;

        case BLOW_TEMP_MOVE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : blow template move message received.");
            handleMoveBlowTempMessage(stream);
            break;

        case REMOVE_BLOW_TEMP:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : blow template remove message received.");
            handleRemoveBlowTempMessage(stream);
            break;

        case NEW_TEXT:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() :New text message received.");
            handleNewTextMessage(stream);
            break;

        case TEXT_CHANGED:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : text move message received.");
            handleMoveTextMessage(stream);
            break;

        case REMOVE_TEXT:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : text remove message received.");
            handleRemoveTextMessage(stream);
            break;

        default:
            QLog_Error(LOG_ID_ERR, "processIncomingMessage() : network message type not recognized");
            break;

        }
    //}
}
