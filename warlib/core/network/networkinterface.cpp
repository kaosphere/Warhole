#include "networkinterface.h"

using namespace QLogger;

const QString NetworkInterface::LOG_ID_INFO = "NetworkInterface_info";
const QString NetworkInterface::LOG_ID_TRACE = "NetworkInterface_trace";
const QString NetworkInterface::LOG_ID_WARN = "NetworkInterface_warm";
const QString NetworkInterface::LOG_ID_ERR = "NetworkInterface_err";

NetworkInterface::NetworkInterface(MessageQueue *in, MessageQueue *out, QObject *parent) :
    QObject(parent)
{
    // TODO see for out and inqueues init
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);
    try
    {
        if(!in)
        {
            throw(WarlibException(EXCEPTION_CRITICAL,
                                  "Received MessageQueue pointer is NULL."), 0);
        }
        else
        {
            inQueue = in;
        }
    }
    catch(const WarlibException& e)
    {
        QLog_Error(LOG_ID_ERR, "NetworkInterface() :" + QString::fromStdString(e.what()));
    }
}

NetworkInterface::~NetworkInterface()
{
    if(inQueue) delete inQueue;
    if(outQueue) delete outQueue;
}

MessageQueue *NetworkInterface::getInQueue() const
{
    return inQueue;
}

void NetworkInterface::setInQueue(MessageQueue *value)
{
    inQueue = value;
}

MessageQueue *NetworkInterface::getOutQueue() const
{
    return outQueue;
}

void NetworkInterface::setOutQueue(MessageQueue *value)
{
    outQueue = value;
}
