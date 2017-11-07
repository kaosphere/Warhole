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

    void sendBackToSender(const QByteArray &m, QString sender);
    void sendToAllButMe(const QByteArray &m, QString sender);

signals:
    void socketBytesWritten(quint64 n);
    
public slots:
    void receiveData();
    void newClientConnected();
    void deconnectionClient();
    virtual void send();
    void changeClientName(QString n1, QString n2);

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    QList<Client*> clients;
    QTcpServer *serveur;
    
    QByteArray fillPacketWithMessage(const Message &m);
};

#endif // NETWORKSERVER_H
