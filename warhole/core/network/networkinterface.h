#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <QObject>
#include <QtNetwork>
#include <QThread>
#include <QDataStream>

#include "core/message.h"
#include "core/messagequeue.h"
#include "core/warlibexception.h"
#include "Utilities/QLogger/QLogger.h"
#include "client.h"

#define NET_PORT 50885

enum NetworkEvent{
    CLIENT_IS_CONNECTED,
    CLIENT_IS_DISCONNECTED,
    CLIENT_ERROR,
    SERVER_IS_LAUNCHED,
    SERVER_ERROR
};

enum NetworkType { SERVER, CLIENT };

class NetworkInterface : public QObject
{
    Q_OBJECT
public:
    explicit NetworkInterface(MessageQueue* in, MessageQueue *out, QObject *parent = 0);

    ~NetworkInterface();

    virtual QString getState() const = 0;
    
    MessageQueue *getInQueue() const;
    void setInQueue(MessageQueue *value);

    MessageQueue *getOutQueue() const;
    void setOutQueue(MessageQueue *value);

signals:
    void stateChanged(QString state);
    void networkEvent(NetworkEvent event, QString details);
    void newPlayerConnected(Client c);
    
public slots:
    virtual void receiveData() = 0;
    virtual void send() = 0;

protected:
    MessageQueue* inQueue;
    MessageQueue* outQueue;

private:

    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;
    
};

#endif // NETWORKINTERFACE_H
