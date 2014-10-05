#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QtNetwork>

#include "networkinterface.h"

class NetworkClient : public NetworkInterface
{
    Q_OBJECT
public:
    explicit NetworkClient(MessageQueue* in,
                           QString ip,
                           int port,
                           QObject *parent = 0);

    virtual void send(const Message &m);

    void sendToServer(const Message& m);

    QTcpSocket* getSock() const;
    void setSock(QTcpSocket *value);

    quint16 getMessageSize() const;
    void setMessageSize(const quint16 &value);

    void connection(QString ip, int port);
signals:
    void clientStateChanged(QString state);
    
public slots:
    virtual void receiveData();
    void connected();
    void deconnected();
    void errorSocket(QAbstractSocket::SocketError erreur);
    
private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    QTcpSocket* sock;
    quint16 messageSize;
    QString clientState;
};

#endif // NETWORKCLIENT_H
