#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <QObject>

#include "core/messagequeue.h"

class CommandManager : public QObject
{
    Q_OBJECT
public:
    explicit CommandManager(MessageQueue* iq, MessageQueue* oq, QObject *parent = 0);
    
signals:
    
public slots:
    void processIncomingMessage();

private:
    MessageQueue* outQueue;
    MessageQueue* inQueue;
    
};

#endif // COMMANDMANAGER_H
