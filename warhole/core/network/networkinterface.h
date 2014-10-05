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

#define NET_PORT 50885

class NetworkInterface : public QObject
{
    Q_OBJECT
public:
    explicit NetworkInterface(MessageQueue* in, QObject *parent = 0);

    ~NetworkInterface();

    virtual void send(const Message& m) = 0;
    
    MessageQueue *getInQueue() const;
    void setInQueue(MessageQueue *value);

    MessageQueue *getOutQueue() const;
    void setOutQueue(MessageQueue *value);

signals:
    void stateChanged(QString state);
    
public slots:
    virtual void receiveData() = 0;

protected:
    MessageQueue* inQueue;

private:

    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;
    
};

#endif // NETWORKINTERFACE_H
