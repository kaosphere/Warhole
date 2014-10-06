#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QtNetwork>

#include "networkinterface.h"

class NetworkClient : public NetworkInterface
{
    Q_OBJECT
public:
    explicit NetworkClient(MessageQueue* in,
                           MessageQueue* out,
                           QObject *parent = 0,
                           QString ip = "127.0.0.1",
                           int port = 50885);

    virtual QString getState() const;

    void sendToServer(const Message& m);

    QTcpSocket* getSock() const;
    void setSock(QTcpSocket *value);

    quint16 getMessageSize() const;
    void setMessageSize(const quint16 &value);

    void connection(QString ip, int port);
    void setClientState(const QString &value);

signals:
    void clientStateChanged(QString state);
    
public slots:
    virtual void send();
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
