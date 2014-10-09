#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QTcpSocket>
#include <QtCore>

#include "networkinterface.h"
#include "client.h"


class NetworkServer : public NetworkInterface
{
    Q_OBJECT
public:
    explicit NetworkServer(MessageQueue* in, MessageQueue *out, QObject *parent = 0);
    virtual ~NetworkServer();

    void sendToAll(const QByteArray& m);

    virtual void disconnection();

    QList<Client*> getClients() const;
    void setClients(const QList<Client*> &value);
    void addClient(Client* c);
    void removeClient(Client *c);

    virtual QString getState() const;
    void setServerState(const QString &value);

    void sendBackToSender(const QByteArray &m, QString sender);
signals:
    void serverStateChanged(QString state);
    
public slots:
    void receiveData();
    void newClientConnected();
    void deconnectionClient();
    virtual void send();

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    QList<Client*> clients;
    QString serverState;
    QTcpServer *serveur;
    
    QByteArray fillPacketWithMessage(const Message &m);
};

#endif // NETWORKSERVER_H
