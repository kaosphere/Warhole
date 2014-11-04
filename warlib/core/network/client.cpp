#include "client.h"

using namespace QLogger;

const QString Client::LOG_ID_INFO = "Client_info";
const QString Client::LOG_ID_TRACE = "Client_trace";
const QString Client::LOG_ID_WARN = "Client_warm";
const QString Client::LOG_ID_ERR = "Client_err";

Client::Client()
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    sock = new QTcpSocket(this);
    messageSize = 0;

    connect(sock, SIGNAL(bytesWritten(qint64)), this, SLOT(printBufferInfo(qint64)));
}

Client::Client(const Client &other):
    QObject(other.parent())
{
    QLoggerManager *manager = QLoggerManager::getInstance();
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_TRACE), QLogger::TraceLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_INFO), QLogger::InfoLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_ERR), QLogger::ErrorLevel);
    manager->addDestination("./logs/lastrun.log", QStringList(LOG_ID_WARN), QLogger::WarnLevel);

    sock = other.sock;
    name = other.name;

    connect(sock, SIGNAL(bytesWritten(qint64)), this, SLOT(printBufferInfo(qint64)));
}

Client::~Client()
{

}

Client::Client(QTcpSocket* s, quint16 t)
{
    sock = s;
    
    connect(sock, SIGNAL(readyRead()), this, SIGNAL(donnees()));
    connect(sock,SIGNAL(disconnected()), this, SIGNAL(disco()));
    
    messageSize = t;
}

QTcpSocket* Client::getSocket()
{
    return sock;
}

void Client::setSocket(QTcpSocket* s)
{
    sock = s;
}

quint32 Client::getMessageSize() const
{
    return messageSize;
}

void Client::setMessageSize(const quint32 &value)
{
    messageSize = value;
}

bool Client::operator =(const Client &other)
{
    if(sock == other.sock && messageSize == other.messageSize)
        return true;
    else
        return false;
}

QString Client::getName() const
{
    return name;
}

void Client::setName(const QString &value)
{
    name = value;
}

void Client::printBufferInfo(qint64 n)
{
    QLog_Info(LOG_ID_INFO, " printBufferInfo() : Socket to " + name + " : bytes written : " +
              QString::number(n) + ". Bytes to write : " + QString::number(sock->bytesToWrite()));
}
