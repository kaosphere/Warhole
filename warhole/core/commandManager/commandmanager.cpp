#include "commandmanager.h"

CommandManager::CommandManager(MessageQueue *iq, MessageQueue *oq, QObject *parent) :
    QObject(parent)
{
    outQueue = oq;
    inQueue = iq;
}

void CommandManager::processIncomingMessage()
{

}
