#include "commandmanager.h"

CommandManager::CommandManager(MessageQueue *iq, MessageQueue *oq, Game *g, QObject *parent) :
    QObject(parent)
{
    outQueue = oq;
    inQueue = iq;
    game = g;

    if(inQueue)
    {
        connect(inQueue, SIGNAL(newMessageAvailable()), this, SLOT(processIncomingMessage()));
    }
}

void CommandManager::enQueueChatMessage(QString player, QString message)
{
    Message m;
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);

    stream << CHAT_MESSAGE
           << player
           << message;

    m.setData(data);

    if(outQueue)
    {
        outQueue->addMessage(m);
    }
}

void CommandManager::processIncomingMessage()
{
    Message m;
    QString senderName;

    if(inQueue)
    {
        m = inQueue->getAndRemoveFirstMessage();
    }

    QByteArray data = m.getData();
    QDataStream stream(data);

    // Get command type
    int command;
    stream >> command;

    switch(command)
    {
    case CHAT_MESSAGE:
        stream >> senderName;
        QString msg;
        stream >> msg;
        emit newChatMessageAvailable(senderName, msg);
        break;
    }



}
