#include "networkthread.h"

using namespace QLogger;

const QString NetworkThread::LOG_ID_INFO = "NetworkThread_info";
const QString NetworkThread::LOG_ID_TRACE = "NetworkThread_trace";
const QString NetworkThread::LOG_ID_WARN = "NetworkThread_warm";
const QString NetworkThread::LOG_ID_ERR = "NetworkThread_err";

NetworkThread::NetworkThread(NetworkType n,
                             MessageQueue* oq,
                             MessageQueue *iq,
                             QObject *parent,
                             QString ip,
                             int port) :
    QThread(parent)
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    // Assign outQueue pointer
    try
    {
        if(!oq || !iq)
        {
            throw(WarlibException(EXCEPTION_CRITICAL,
                                  "Received MessageQueue pointer is NULL."), 0);
        }
        else
        {
            outQueue = oq;
            inQueue = iq;


            switch(n)
            {
            case SERVER:
                netInterface = new NetworkServer(inQueue, this);
                break;
            case CLIENT:
                netInterface = new NetworkClient(inQueue, ip, port, this);
                QLog_Info(LOG_ID_INFO, "Connecting Client with ip : " + ip);
                break;
            default:
                // TODO make another error handling
                QLog_Error(LOG_ID_ERR, "Error creating NetworkThred : Network type unknown.");
                netInterface = NULL;
                break;
            }
            connect(netInterface, SIGNAL(stateChanged(QString)), this, SLOT(logState(QString)));
        }
    }
    catch(const WarlibException& e)
    {
        QLog_Error(LOG_ID_ERR, "NetworkThread() :" + QString::fromStdString(e.what()));
    }
}

void NetworkThread::logState(QString state)
{
    QLog_Info(LOG_ID_INFO, state);
}

void NetworkThread::run()
{
    while(1)
    {
        try
        {
            if(!outQueue)
            {
                throw(WarlibException(EXCEPTION_CRITICAL,
                                      "OutQueue pointer is NULL."), 0);
            }
            else
            {
                if(!outQueue->getMessageList().isEmpty())
                {
                    netInterface->send(outQueue->getAndRemoveFirstMessage());
                }
            }
        }
        catch(const WarlibException& e)
        {
            QLog_Error(LOG_ID_ERR, "Run() :" + QString::fromStdString(e.what()));
        }
    }
}


