#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QtCore>

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
};

#endif // MESSAGE_H
