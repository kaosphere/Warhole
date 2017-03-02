#include "messagequeue.h"

MessageQueue::MessageQueue(QObject *parent) :
    QObject(parent)
{
}

QList<Message> MessageQueue::getMessageList()
{
    QMutexLocker locker(&mutex);
    return messageList;
}

void MessageQueue::setMessageList(const QList<Message> &value)
{
    QMutexLocker locker(&mutex);
    messageList = value;
}

void MessageQueue::addMessage(const Message &m)
{
    {
        // Protect the message list
        QMutexLocker locker(&mutex);

        // Add new message
        messageList.append(m);
        locker.unlock();
    }

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

Message MessageQueue::getAndRemoveFirstMessage()
{
    QMutexLocker locker(&mutex);
    Message m = messageList.first();
    messageList.removeOne(m);
    return m;
}

void MessageQueue::addMessageAsFirst(Message &m)
{
    QMutexLocker locker(&mutex);
    messageList.push_front(m);
    emit newMessageAvailable();
}

bool MessageQueue::isMessageListEmpty()
{
    QMutexLocker locker(&mutex);
    return messageList.isEmpty();
}

