#include "client.h"

Client::Client()
{
    sock = new QTcpSocket(this);
    messageSize = 0;
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

quint16 Client::getMessageSize() const
{
    return messageSize;
}

void Client::setMessageSize(const quint16 &value)
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

