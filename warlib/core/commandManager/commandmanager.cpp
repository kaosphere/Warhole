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

void CommandManager::handleServerInfoRequest(MessageDestination dest, QString sender)
{
    QLog_Info(LOG_ID_INFO, "handleServerInfoRequest() : sending server info to " + sender);
    Message m;
    m.setDest(dest);
    m.setMessageSender(sender);
    qDebug() << "ici la dest : " + QString::number((int)dest);

    QByteArray data;
    QDataStream s(&data, QIODevice::WriteOnly);

    s << SERVER_INFO;
    // TODO fill data

    m.setData(data);

    addMessageToOutQueue(m);
}

void CommandManager::handleServerInfo(QByteArray& data)
{
    // TODO do something with data
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

void CommandManager::handlePlayerListRefreshMessage(const Message& m, QDataStream& data)
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



void CommandManager::handleCreateRulerMessage(const Message &m, QDataStream& data)
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

void CommandManager::handleRulerMoveMessage(const Message& m, QDataStream& data)
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

void CommandManager::handleRemoveRulerMessage(const Message& m, QDataStream& data)
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

void CommandManager::handleRemoveTemplateMessage(const Message& m, QDataStream& data)
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

void CommandManager::handleCreateRoundTemplateMessage(const Message &m, QDataStream &data)
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


void CommandManager::handleTemplateMoveMessage(const Message &m, QDataStream &data)
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

void CommandManager::handleNewRegimentMessage(const Message &m, QDataStream &data)
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
            handleServerInfo(data);
            break;

        case PLAYER_LIST_UPDATE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Player list update received.");
            handlePlayerListRefreshMessage(m, stream);
            break;

        case NEW_RULER:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New ruler message received.");
            handleCreateRulerMessage(m, stream);
            break;

        case RULER_POSITION_CHANGE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Ruler moved message received.");
            handleRulerMoveMessage(m, stream);
            break;

        case RULER_REMOVE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Ruler remove message received.");
            handleRemoveRulerMessage(m, stream);
            break;

        case NEW_ROUND_TEMPLATE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New Round template received.");
            handleCreateRoundTemplateMessage(m, stream);
            break;

        case ROUND_TEMPLATE_POSITION_CHANGE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Template moved message received.");
            handleTemplateMoveMessage(m, stream);
            break;

        case ROUND_TEMPLATE_REMOVE:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : Template remove message received.");
            handleRemoveTemplateMessage(m, stream);
            break;

        case NEW_REGIMENT:
            QLog_Info(LOG_ID_INFO, "processIncomingMessage() : New regiment message received.");
            handleNewRegimentMessage(m, stream);
            break;

        default:
            QLog_Error(LOG_ID_ERR, "processIncomingMessage() : network message type not recognized");
            break;

        }
    //}
}
