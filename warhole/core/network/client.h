#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui>
#include <QtNetwork>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    Client(QTcpSocket* s, quint16 t);
    QTcpSocket* getSocket();
    void setSocket(QTcpSocket* s);

    quint16 getMessageSize() const;
    void setMessageSize(const quint16 &value);

    bool operator=(const Client& other);

signals:
    void donnees();
    void disco();

private:
    QTcpSocket* sock;
    quint16 messageSize;
};

#endif // CLIENT_H
