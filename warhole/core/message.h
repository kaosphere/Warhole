#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QtCore>

//! MessageDestination
/*!
* This enum is used by the server only to know who to answer or
* transfer messages when he receives one.
* ALL will be transfered to every client.
* ALL_BU_ME will be transfered to every client instead of the sender.
* ME will be answered only to the sender.
*/
enum MessageDestination{
    ALL = 0,
    ALL_BUT_ME,
    ME
};

//! Message class
/*!
* The message class contains data that goes through the network
* and that is handled by clients and server. Clients and server
* receive the data, and put it in a message that will be stored
* into the message queue. The message queue will be read by the
* command manager that will update all the data structures of the
* game.
*/
class Message
{
public:
    //! Message.
    /*!
    * Constructor of Message class
    */
    Message();

    //! Message Copy Constructor.
    /*!
    * Copy constructor of Message class
    * \param copy Object to be copied.
    */
    Message(const Message &copy);

    //! sender
    /*!
    * User that sended the message
    */
    bool operator==(const Message& obj);


    QByteArray getData() const;
    void setData(const QByteArray &value);

    QString getMessageSender() const;
    void setMessageSender(const QString &value);

    MessageDestination getDest() const;
    void setDest(const MessageDestination &value);

    void setDest(const int &value);
private:
    //! data
    /*!
    * Data to be transmitted inside the message
    */
    QByteArray data;

    //! messageSender
    /*!
    * User that sended the message
    */
    QString messageSender;

    MessageDestination dest;
};

#endif // MESSAGE_H
