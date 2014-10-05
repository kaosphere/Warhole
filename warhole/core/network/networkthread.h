#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QThread>
#include <QtCore>

#include "networkclient.h"
#include "networkserver.h"
#include "Utilities/QLogger/QLogger.h"
#include "core/messagequeue.h"

enum NetworkType { SERVER, CLIENT };

class NetworkThread : public QThread
{
    Q_OBJECT
public:
    explicit NetworkThread(NetworkType n,
                           MessageQueue *oq,
                           MessageQueue *iq,
                           QObject *parent = 0,
                           QString ip = "",
                           int port = 0);
    virtual void run();
    

signals:
    void networkStateChanged(QString state);
    
public slots:
    void logState(QString state);

private:
    static const QString LOG_ID_INFO;
    static const QString LOG_ID_TRACE;
    static const QString LOG_ID_WARN;
    static const QString LOG_ID_ERR;

    NetworkInterface* netInterface;
    MessageQueue* outQueue;
    MessageQueue* inQueue;
    
};

#endif // NETWORKTHREAD_H
