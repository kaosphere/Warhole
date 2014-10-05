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
    explicit NetworkServer(MessageQueue* in, QObject *parent = 0);

    virtual void send(const Message& m);

    void sendToAll(const Message& m);

    QList<Client*> getClients() const;
    void setClients(const QList<Client*> &value);
    void addClient(Client* c);
    void removeClient(Client *c);

signals:
    void serverStateChanged(QString state);
    
public slots:
    void receiveData();
    void newClientConnected();
    void deconnectionClient();

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    QList<Client*> clients;
    QString serverState;
    QTcpServer *serveur;
    
};

#endif // NETWORKSERVER_H
