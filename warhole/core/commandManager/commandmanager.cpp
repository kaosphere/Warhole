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
        inQueue->addMessage(m);
    }
}

void CommandManager::addMessageToOutQueue(const Message& m)
{
    if(outQueue)
    {
        outQueue->addMessage(m);
    }
}

void CommandManager::handleNetworkEvent(NetworkEvent e, QString details)
{
    switch(e)
    {
    case CLIENT_IS_CONNECTED:
        emit newChatMessageAvailable("client", "Connexion au serveur résussie.");
        // Create a message to be sent to the server resquesting game parameters
        // and global update of the game
        enQueueServerInfoRequest();
        break;

    case CLIENT_IS_DISCONNECTED:
        emit newChatMessageAvailable("client", "Connexion au serveur interrompue.");
        break;

    case CLIENT_ERROR:
        emit newChatMessageAvailable("client", "Connexion au serveur résussie.");
        break;

    case SERVER_IS_LAUNCHED:
        break;

    case SERVER_ERROR:
        break;

    default:
        QLog_Error(LOG_ID_ERR, "handleNetworkEvent() : network event not recognized");
        break;
    }
}

void CommandManager::enQueueChatMessage(QString player, QString message)
{
    QLog_Info(LOG_ID_INFO, "enQueueChatMessage() : sending chat message to all.");
    Message m;
    m.setMessageSender(player);
    m.setDest(ALL);
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    stream << CHAT_MESSAGE
           << player
           << message;

    m.setData(data);

    qDebug() << "Destination du chat : " + QString::number((int)(m.getDest()));

    addMessageToOutQueue(m);
}

void CommandManager::handleNewChatMessage(QByteArray& data)
{
    QDataStream s(data);

    QString senderName;
    s >> senderName;
    QString msg;
    s >> msg;
    emit newChatMessageAvailable(senderName, msg);
}

void CommandManager::enQueueServerInfoRequest()
{
    QLog_Info(LOG_ID_INFO, "handleServerInfoRequest() : sending server info request to server.");
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

void CommandManager::processIncomingMessage()
{
    Message m;

    if(inQueue)
    {
        m = inQueue->getAndRemoveFirstMessage();
    }

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
        handleNewChatMessage(data);
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
    default:
        QLog_Error(LOG_ID_ERR, "processIncomingMessage() : network message type not recognized");
        break;

    }
}
