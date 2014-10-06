#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <QObject>
#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include "message.h"

//! MessageQueue class
/*!
* The MessageQueue class contains all the messages received
* over the network and is kind of a buffer structure which stores
* the data to be processed by the command manager, and the network
* interfaced. The newMessageAvailable() signal is emitted when a new
* message is added to the list. A mutex protects the message list
* from being modified by different threads at the same time.
*/
class MessageQueue : public QObject
{
    Q_OBJECT
public:
    //! MessageQueue.
    /*!
    * Constructor of MessageQueue class
    */
    explicit MessageQueue(QObject *parent = 0);

    QList<Message> getMessageList();
    void setMessageList(const QList<Message> &value);
    void addMessage(const Message &m);
    void removeMessage(Message &m);
    void clearMessages();
    Message getAndRemoveFirstMessage();

    bool isMessageListEmpty();
signals:
    //! newMessageAvailable
    /*!
    * Signal sent when a new message is added to the message list.
    */
    void newMessageAvailable();

private:
    //! messageList
    /*!
    * List of all the messages to be processed.
    * when a message is processed, it will be removed from the list.
    * Thus, all the message in the list are to be processed.
    */
    QList<Message> messageList;

    //! mutex
    /*!
    * Mutex that make the message queue thread safe.
    */
    QMutex mutex;

};

#endif // MESSAGEQUEUE_H
