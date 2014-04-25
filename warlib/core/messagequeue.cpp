#include "messagequeue.h"

MessageQueue::MessageQueue(QObject *parent) :
    QObject(parent)
{
}

QList<Message> MessageQueue::getMessageList() const
{
    QMutexLocker locker(&mutex);
    return messageList;
}

void MessageQueue::setMessageList(const QList<Message> &value)
{
    QMutexLocker locker(&mutex);
    messageList = value;
}

void MessageQueue::addMessage(Message &m)
{
    // Protect the message list
    QMutexLocker locker(&mutex);

    // Add new message
    messageList.append(m);

    // Emit signal so that the new message can be processed
    emit newMessageAvailable();
}

void MessageQueue::removeMessage(Message &m)
{
    QMutexLocker locker(&mutex);
    messageList.removeOne(m);
}

void MessageQueue::clearMessages()
{
    QMutexLocker locker(&mutex);
    messageList.clear();
}

